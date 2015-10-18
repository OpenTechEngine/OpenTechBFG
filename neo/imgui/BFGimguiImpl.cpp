/*
 * ImGui integration into Doom3BFG/OpenTechEngine.
 * Based on ImGui SDL and OpenGL3 examples.
 *  Copyright (c) 2014-2015 Omar Cornut and ImGui contributors
 *
 * Doom3-specific Code (and ImGui::DragXYZ(), based on ImGui::DragFloatN())
 *  Copyright (C) 2015 Daniel Gibson
 *
 * This file is under MIT License, like the original code from ImGui.
 */

#include "BFGimgui.h"
#include "../idlib/Str.h"

// our custom ImGui functions from BFGimgui.h

// like DragFloat3(), but with "X: ", "Y: " or "Z: " prepended to each display_format, for vectors
// if !ignoreLabelWidth, it makes sure the label also fits into the current item width.
//    note that this screws up alignment with consecutive "value+label widgets" (like Drag* or ColorEdit*)
bool ImGui::DragVec3( const char* label, BFG::idVec3& v, float v_speed,
					  float v_min, float v_max, const char* display_format, float power, bool ignoreLabelWidth )
{
	bool value_changed = false;
	ImGui::BeginGroup();
	ImGui::PushID( label );
	
	ImGuiStyle& style = ImGui::GetStyle();
	float wholeWidth = ImGui::CalcItemWidth() - 2.0f * style.ItemSpacing.x;
	float spacing = style.ItemInnerSpacing.x;
	float labelWidth = ignoreLabelWidth ? 0.0f : ( ImGui::CalcTextSize( label, NULL, true ).x + spacing );
	float coordWidth = ( wholeWidth - labelWidth - 2.0f * spacing ) * ( 1.0f / 3.0f ); // width of one x/y/z dragfloat
	
	ImGui::PushItemWidth( coordWidth );
	for( int i = 0; i < 3; i++ )
	{
		ImGui::PushID( i );
		char format[64];
		BFG::idStr::snPrintf( format, sizeof( format ), "%c: %s", "XYZ"[i], display_format );
		value_changed |= ImGui::DragFloat( "##v", &v[i], v_speed, v_min, v_max, format, power );
		
		ImGui::PopID();
		ImGui::SameLine( 0.0f, spacing );
	}
	ImGui::PopItemWidth();
	ImGui::PopID();
	
	const char* labelEnd = strstr( label, "##" );
	ImGui::TextUnformatted( label, labelEnd );
	
	ImGui::EndGroup();
	
	return value_changed;
}

// shortcut for DragXYZ with ignorLabelWidth = false
// very similar, but adjusts width to width of label to make sure it's not cut off
// sometimes useful, but might not align with consecutive "value+label widgets" (like Drag* or ColorEdit*)
bool ImGui::DragVec3fitLabel( const char* label, BFG::idVec3& v, float v_speed,
							  float v_min, float v_max, const char* display_format, float power )
{
	return ImGui::DragVec3( label, v, v_speed, v_min, v_max, display_format, power, false );
}

// the ImGui hooks to integrate it into the engine

#include "ImGui_Hooks.h"
#include <GL/glew.h> // for gl* in the rendering code

#include "../tools/Tools.h" // FIXME: HACKY!
#include "../framework/KeyInput.h"
#include "../framework/UsercmdGen.h"
#include "../sys/sys_public.h"
#include "../idlib/Heap.h"

using namespace BFG; // don't wanna prepend BFG:: to the d3bfg types

namespace BFG
{
namespace ImGuiHook
{

namespace
{

bool	g_IsInit = false;
double	g_Time = 0.0f;
bool	g_MousePressed[5] = { false, false, false, false, false };
float	g_MouseWheel = 0.0f;
ImVec2	g_MousePos = ImVec2( -1.0f, -1.0f ); //{-1.0f, -1.0f};
ImVec2	g_DisplaySize = ImVec2( 0.0f, 0.0f ); //{0.0f, 0.0f};
// the following are for the opengl rendering code
GLuint       g_FontTexture = 0;
int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;

bool g_haveNewFrame = false;

bool HandleKeyEvent( const sysEvent_t& keyEvent )
{
	assert( keyEvent.evType == SE_KEY );
	
	keyNum_t keyNum = static_cast<keyNum_t>( keyEvent.evValue );
	bool pressed = keyEvent.evValue2;
	
	ImGuiIO& io = ImGui::GetIO();
	
	if( keyNum < K_JOY1 )
	{
		// keyboard input as direct input scancodes
		int dInputKey =  keyEvent.evValue;
		
		io.KeysDown[dInputKey] = pressed;
		
		io.KeyAlt = usercmdGen->KeyState( K_LALT ) == 1 || usercmdGen->KeyState( K_RALT ) == 1;
		io.KeyCtrl = usercmdGen->KeyState( K_LCTRL ) == 1 || usercmdGen->KeyState( K_RCTRL ) == 1;
		io.KeyShift = usercmdGen->KeyState( K_LSHIFT ) == 1 || usercmdGen->KeyState( K_RSHIFT ) == 1;
		
		return true;
	}
	else if( pressed && keyNum >= K_MOUSE1 && keyNum <= K_MOUSE5 )
	{
		// K_MOUSE* are contiguous, so they can be used as indexes into imgui's
		// g_MousePressed[] - imgui even uses the same order (left, right, middle, X1, X2)
		int buttonIdx = keyNum - K_MOUSE1;
		g_MousePressed[buttonIdx] = true;
		return true;
	}
	
	return false;
}

// Gross hack. I'm sorry.
// sets the kb-layout specific keys in the keymap
void FillCharKeys( int* keyMap )
{
	// set scancodes as default values in case the real keys aren't found below
	keyMap[ImGuiKey_A] = K_A;
	keyMap[ImGuiKey_C] = K_C;
	keyMap[ImGuiKey_V] = K_V;
	keyMap[ImGuiKey_X] = K_X;
	keyMap[ImGuiKey_Y] = K_Y;
	keyMap[ImGuiKey_Z] = K_Z;
	
	// try all probable keys for whether they're ImGuiKey_A/C/V/X/Y/Z
	for( int k = K_1; k < K_RSHIFT; ++k )
	{
		const char* kn = idKeyInput::LocalizedKeyName( ( keyNum_t )k );
		if( kn[0] == '\0' || kn[1] != '\0' || kn[0] == '?' )
		{
			// if the key wasn't found or the name has more than one char,
			// it's not what we're looking for.
			continue;
		}
		switch( kn[0] )
		{
			case 'a': // fall-through
			case 'A':
				keyMap [ImGuiKey_A] = k;
				break;
			case 'c': // fall-through
			case 'C':
				keyMap [ImGuiKey_C] = k;
				break;
				
			case 'v': // fall-through
			case 'V':
				keyMap [ImGuiKey_V] = k;
				break;
				
			case 'x': // fall-through
			case 'X':
				keyMap [ImGuiKey_X] = k;
				break;
				
			case 'y': // fall-through
			case 'Y':
				keyMap [ImGuiKey_Y] = k;
				break;
				
			case 'z': // fall-through
			case 'Z':
				keyMap [ImGuiKey_Z] = k;
				break;
		}
	}
}

// Sys_GetClipboardData() expects that you Mem_Free() its returned data
// ImGui can't do that, of course, so copy it into a static buffer here,
// Mem_Free() and return the copy
const char* GetClipboardWrapper()
{
	char* txt = Sys_GetClipboardData();
	if( txt == NULL ) return NULL;
	
	static idStr clipboardBuf;
	clipboardBuf = txt;
	
	Mem_Free( txt );
	
	return clipboardBuf.c_str();
}

// from ImGui_ImplGlfwGL3_CreateDeviceObjects() from the imgui opengl3 example
bool CreateDeviceObjects()
{
	const GLchar* vertex_shader =
		"#version 330\n"
		"uniform mat4 ProjMtx;\n"
		"in vec2 Position;\n"
		"in vec2 UV;\n"
		"in vec4 Color;\n"
		"out vec2 Frag_UV;\n"
		"out vec4 Frag_Color;\n"
		"void main()\n"
		"{\n"
		"	Frag_UV = UV;\n"
		"	Frag_Color = Color;\n"
		"	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
		"}\n";
		
	const GLchar* fragment_shader =
		"#version 330\n"
		"uniform sampler2D Texture;\n"
		"in vec2 Frag_UV;\n"
		"in vec4 Frag_Color;\n"
		"out vec4 Out_Color;\n"
		"void main()\n"
		"{\n"
		"	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
		"}\n";
		
	g_ShaderHandle = glCreateProgram();
	g_VertHandle = glCreateShader( GL_VERTEX_SHADER );
	g_FragHandle = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( g_VertHandle, 1, &vertex_shader, 0 );
	glShaderSource( g_FragHandle, 1, &fragment_shader, 0 );
	glCompileShader( g_VertHandle );
	glCompileShader( g_FragHandle );
	glAttachShader( g_ShaderHandle, g_VertHandle );
	glAttachShader( g_ShaderHandle, g_FragHandle );
	glLinkProgram( g_ShaderHandle );
	
	g_AttribLocationTex = glGetUniformLocation( g_ShaderHandle, "Texture" );
	g_AttribLocationProjMtx = glGetUniformLocation( g_ShaderHandle, "ProjMtx" );
	g_AttribLocationPosition = glGetAttribLocation( g_ShaderHandle, "Position" );
	g_AttribLocationUV = glGetAttribLocation( g_ShaderHandle, "UV" );
	g_AttribLocationColor = glGetAttribLocation( g_ShaderHandle, "Color" );
	
	glGenBuffers( 1, &g_VboHandle );
	glGenBuffers( 1, &g_ElementsHandle );
	
	glGenVertexArrays( 1, &g_VaoHandle );
	glBindVertexArray( g_VaoHandle );
	glBindBuffer( GL_ARRAY_BUFFER, g_VboHandle );
	glEnableVertexAttribArray( g_AttribLocationPosition );
	glEnableVertexAttribArray( g_AttribLocationUV );
	glEnableVertexAttribArray( g_AttribLocationColor );
	
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	glVertexAttribPointer( g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof( ImDrawVert ), ( GLvoid* )OFFSETOF( ImDrawVert, pos ) );
	glVertexAttribPointer( g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof( ImDrawVert ), ( GLvoid* )OFFSETOF( ImDrawVert, uv ) );
	glVertexAttribPointer( g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( ImDrawVert ), ( GLvoid* )OFFSETOF( ImDrawVert, col ) );
#undef OFFSETOF
	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	
	// create the fonts texture - from ImGui_ImplGlfwGL3_CreateFontsTexture()
	ImGuiIO& io = ImGui::GetIO();
	
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32( &pixels, &width, &height ); // Load as RGBA 32-bits for OpenGL3 demo because it is more likely to be compatible with user's existing shader.
	
	glGenTextures( 1, &g_FontTexture );
	glBindTexture( GL_TEXTURE_2D, g_FontTexture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
	
	// Store our identifier
	io.Fonts->TexID = ( void* )( intptr_t )g_FontTexture;
	
	// Cleanup (don't clear the input data if you want to append new fonts later)
	io.Fonts->ClearInputData();
	io.Fonts->ClearTexData();
	
	return true;
}

// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
// If text or lines are blurry when integrating ImGui in your engine:
// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
void RenderDrawLists( ImDrawData* draw_data )
{
	// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
	GLint last_program, last_texture;
	glGetIntegerv( GL_CURRENT_PROGRAM, &last_program );
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &last_texture );
	glEnable( GL_BLEND );
	glBlendEquation( GL_FUNC_ADD );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_CULL_FACE );
	glDisable( GL_DEPTH_TEST );
	glEnable( GL_SCISSOR_TEST );
	glActiveTexture( GL_TEXTURE0 );
	
	// Setup orthographic projection matrix
	const float width = ImGui::GetIO().DisplaySize.x;
	const float height = ImGui::GetIO().DisplaySize.y;
	const float ortho_projection[4][4] =
	{
		{ 2.0f / width,	0.0f,			0.0f,		0.0f },
		{ 0.0f,			2.0f / -height,	0.0f,		0.0f },
		{ 0.0f,			0.0f,			-1.0f,		0.0f },
		{ -1.0f,		1.0f,			0.0f,		1.0f },
	};
	glUseProgram( g_ShaderHandle );
	glUniform1i( g_AttribLocationTex, 0 );
	glUniformMatrix4fv( g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0] );
	glBindVertexArray( g_VaoHandle );
	
	for( int n = 0; n < draw_data->CmdListsCount; n++ )
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		const ImDrawIdx* idx_buffer_offset = 0;
		
		glBindBuffer( GL_ARRAY_BUFFER, g_VboHandle );
		glBufferData( GL_ARRAY_BUFFER, ( GLsizeiptr )cmd_list->VtxBuffer.size() * sizeof( ImDrawVert ), ( GLvoid* )&cmd_list->VtxBuffer.front(), GL_STREAM_DRAW );
		
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, ( GLsizeiptr )cmd_list->IdxBuffer.size() * sizeof( ImDrawIdx ), ( GLvoid* )&cmd_list->IdxBuffer.front(), GL_STREAM_DRAW );
		
		for( const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++ )
		{
			if( pcmd->UserCallback )
			{
				pcmd->UserCallback( cmd_list, pcmd );
			}
			else
			{
				glBindTexture( GL_TEXTURE_2D, ( GLuint )( intptr_t )pcmd->TextureId );
				glScissor( ( int )pcmd->ClipRect.x, ( int )( height - pcmd->ClipRect.w ), ( int )( pcmd->ClipRect.z - pcmd->ClipRect.x ), ( int )( pcmd->ClipRect.w - pcmd->ClipRect.y ) );
				glDrawElements( GL_TRIANGLES, ( GLsizei )pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer_offset );
			}
			idx_buffer_offset += pcmd->ElemCount;
		}
	}
	
	// Restore modified state
	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glUseProgram( last_program );
	glDisable( GL_SCISSOR_TEST );
	glBindTexture( GL_TEXTURE_2D, last_texture );
}

} //anon namespace

bool Init( int windowWidth, int windowHeight )
{
	if( IsInitialized() )
	{
		Destroy();
	}
	
	ImGuiIO& io = ImGui::GetIO();
	// Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
	io.KeyMap[ImGuiKey_Tab] = K_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = K_LEFTARROW;
	io.KeyMap[ImGuiKey_RightArrow] = K_RIGHTARROW;
	io.KeyMap[ImGuiKey_UpArrow] = K_UPARROW;
	io.KeyMap[ImGuiKey_DownArrow] = K_DOWNARROW;
	io.KeyMap[ImGuiKey_PageUp] = K_PGUP;
	io.KeyMap[ImGuiKey_PageDown] = K_PGDN;
	io.KeyMap[ImGuiKey_Home] = K_HOME;
	io.KeyMap[ImGuiKey_End] = K_END;
	io.KeyMap[ImGuiKey_Delete] = K_DEL;
	io.KeyMap[ImGuiKey_Backspace] = K_BACKSPACE;
	io.KeyMap[ImGuiKey_Enter] = K_ENTER;
	io.KeyMap[ImGuiKey_Escape] = K_ESCAPE;
	
	FillCharKeys( io.KeyMap );
	
	g_DisplaySize.x = windowWidth;
	g_DisplaySize.y = windowHeight;
	io.DisplaySize = g_DisplaySize;
	
	io.RenderDrawListsFn = RenderDrawLists;
	io.SetClipboardTextFn = Sys_SetClipboardData;
	io.GetClipboardTextFn = GetClipboardWrapper;
	
	// make it a bit prettier with rounded edges
	ImGuiStyle& style = ImGui::GetStyle();
	style.ChildWindowRounding = 9.0f;
	style.FrameRounding = 4.0f;
	style.ScrollbarRounding = 4.0f;
	style.GrabRounding = 4.0f;
	
	g_IsInit = true;
	
	return true;
}

void NotifyDisplaySizeChanged( int width, int height )
{
	if( IsInitialized() )
	{
		g_DisplaySize = ImVec2( ( float )width, ( float )height );
	}
}

// inject a sys event
bool InjectSysEvent( const sysEvent_t* event )
{
	if( IsInitialized() )
	{
		if( event == NULL )
		{
			assert( 0 ); // I think this shouldn't happen
			return false;
		}
		
		const sysEvent_t& ev = *event;
		
		switch( ev.evType )
		{
			case SE_KEY:
				return HandleKeyEvent( ev );
				
			case SE_MOUSE_ABSOLUTE:
				g_MousePos.x = ev.evValue;
				g_MousePos.y = ev.evValue2;
				return true;
				
			case SE_CHAR:
				if( ev.evValue < 0x10000 )
				{
					ImGui::GetIO().AddInputCharacter( ev.evValue );
					return true;
				}
				break;
				
			case SE_MOUSE_LEAVE:
				g_MousePos = ImVec2( -1.0f, -1.0f );
				return true;
				
			default:
				break;
		}
	}
	return false;
}

bool InjectMouseWheel( int delta )
{
	if( IsInitialized() && delta != 0 )
	{
		g_MouseWheel = ( delta > 0 ) ? 1 : -1;
		return true;
	}
	return false;
}

void NewFrame()
{
	if( !g_FontTexture ) CreateDeviceObjects();
	
	ImGuiIO& io = ImGui::GetIO();
	
	// Setup display size (every frame to accommodate for window resizing)
	io.DisplaySize = g_DisplaySize;
	
	// Setup time step
	int	time = Sys_Milliseconds();
	double current_time = time * 0.001;
	io.DeltaTime = g_Time > 0.0 ? ( float )( current_time - g_Time ) : ( float )( 1.0f / 60.0f );
	g_Time = current_time;
	
	// Setup inputs
	io.MousePos = g_MousePos;
	
	// If a mouse press event came, always pass it as "mouse held this frame",
	// so we don't miss click-release events that are shorter than 1 frame.
	for( int i = 0; i < 5; ++i )
	{
		io.MouseDown[i] = g_MousePressed[i] || usercmdGen->KeyState( K_MOUSE1 + i ) == 1;
		g_MousePressed[i] = false;
	}
	
	io.MouseWheel = g_MouseWheel;
	g_MouseWheel = 0.0f;
	
	// Hide OS mouse cursor if ImGui is drawing it TODO: hide mousecursor?
	// ShowCursor(io.MouseDrawCursor ? 0 : 1);
	
	// Start the frame
	ImGui::NewFrame();
	g_haveNewFrame = true;
}

void Render()
{
	if( IsInitialized() )
	{
		if( !g_haveNewFrame )
		{
			// for screenshots etc, where we didn't go through idCommonLocal::Frame()
			// before idRenderSystemLocal::SwapCommandBuffers_FinishRendering()
			NewFrame();
		}
		
		// FIXME: hacky!
		Tools::ToolSelectionWindow();
		
		ImGui::Render();
		g_haveNewFrame = false;
	}
}

void Destroy()
{
	if( IsInitialized() )
	{
		if( g_VaoHandle ) glDeleteVertexArrays( 1, &g_VaoHandle );
		if( g_VboHandle ) glDeleteBuffers( 1, &g_VboHandle );
		if( g_ElementsHandle ) glDeleteBuffers( 1, &g_ElementsHandle );
		g_VaoHandle = g_VboHandle = g_ElementsHandle = 0;
		
		glDetachShader( g_ShaderHandle, g_VertHandle );
		glDeleteShader( g_VertHandle );
		g_VertHandle = 0;
		
		glDetachShader( g_ShaderHandle, g_FragHandle );
		glDeleteShader( g_FragHandle );
		g_FragHandle = 0;
		
		glDeleteProgram( g_ShaderHandle );
		g_ShaderHandle = 0;
		
		if( g_FontTexture )
		{
			glDeleteTextures( 1, &g_FontTexture );
			ImGui::GetIO().Fonts->TexID = 0;
			g_FontTexture = 0;
		}
		
		ImGui::Shutdown();
		g_IsInit = false;
	}
}

bool IsInitialized()
{
	// checks if cegui is up and running
	return g_IsInit;
}

} //namespace ImGuiHook
} //namespace BFG
