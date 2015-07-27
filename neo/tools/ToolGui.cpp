#include "../imgui/BFGimgui.h"
#include "../idlib/CmdArgs.h"

namespace BFG
{

static bool showToolSelWin = false;

void ShowEditors_f( const idCmdArgs& args )
{
	showToolSelWin = true;
}

namespace Tools
{

namespace
{

void ShowLightEditor( bool* showIt )
{
	ImGui::Begin( "Light Editor", showIt, ImGuiWindowFlags_ShowBorders );
	
	static int lightSelectionRadio = 0;
	static bool equilRadius = true;
	static bool castShadows = true;
	static bool castDiffuse = true;
	static bool castSpecular = true;
	static float color[3] = {0.0f, 0.0f, 0.0f};
	
	ImGui::Checkbox( "Cast Shadows", &castShadows );
	ImGui::SameLine();
	ImGui::Checkbox( "Cast Diffuse", &castDiffuse );
	ImGui::Checkbox( "Cast Specular", &castSpecular );
	
	ImGui::Spacing();
	
	ImGui::ColorEdit3( "Color", color );
	
	// TODO: texture
	
	ImGui::Spacing();
	
	ImGui::RadioButton( "Point Light", &lightSelectionRadio, 0 );
	ImGui::SameLine();
	ImGui::RadioButton( "Projected Light", &lightSelectionRadio, 1 );
	
	ImGui::Indent();
	
	ImGui::Spacing();
	
	if( lightSelectionRadio == 0 )
	{
		static float radius[3] = { 300.0f, 300.0f, 300.0f };
		static int fallOffRadio = 2;
		static bool parallel = false;
		static bool centered = false;
		static float center[3] = { 0.0f, 0.0f, 0.0f };
		
		ImGui::PushItemWidth( -1.0f ); // align end of Drag* with right window border
		
		ImGui::Checkbox( "Equilateral Radius", &equilRadius );
		ImGui::Text( "Radius:" );
		ImGui::Indent();
		if( equilRadius )
		{
			if( ImGui::DragFloat( "(in all dirs)##radEquil", &radius[0], 1.0f, 0.0f, 10000.0f, "%.1f" ) )
			{
				radius[2] = radius[1] = radius[0];
			}
		}
		else
		{
			ImGui::DragXYZ( "##radXYZ", radius );
		}
		ImGui::Unindent();
		
		ImGui::Spacing();
		
		// TODO: this could as well be a slider or something, if 0/0.5/1 is too restricting
		ImGui::Text( "Fall-off:" );
		ImGui::SameLine();
		ImGui::RadioButton( "0.0", &fallOffRadio, 0 );
		ImGui::SameLine();
		ImGui::RadioButton( "0.5", &fallOffRadio, 1 );
		ImGui::SameLine();
		ImGui::RadioButton( "1.0", &fallOffRadio, 2 );
		
		ImGui::Spacing();
		
		ImGui::Checkbox( "Parallel", &parallel );
		
		ImGui::Spacing();
		
		ImGui::Checkbox( "Center", &centered );
		if( centered )
		{
			ImGui::Indent();
			ImGui::DragXYZ( "##centerXYZ", center, 1.0f, 0.0f, 10000.0f, "%.1f" );
			ImGui::Unindent();
		}
		ImGui::PopItemWidth(); // back to default alignment on right side
	}
	else if( lightSelectionRadio == 1 )
	{
		static float target[3] = {0.0f, 0.0f, 0.0f};
		static float right[3] = {0.0f, 0.0f, 0.0f};
		static float up[3] = {0.0f, 0.0f, 0.0f};
		static bool explicitStartEnd = false;
		static float start[3] = {0.0f, 0.0f, 0.0f};
		static float end[3] = {0.0f, 0.0f, 0.0f};
		
		ImGui::DragXYZ( "Target", target, 1.0f, 0.0f, 0.0f, "%.1f" );
		ImGui::DragXYZ( "Right", right, 1.0f, 0.0f, 0.0f, "%.1f" );
		ImGui::DragXYZ( "Up", up, 1.0f, 0.0f, 0.0f, "%.1f" );
		
		ImGui::Spacing();
		
		ImGui::Checkbox( "Explicit start/end points", &explicitStartEnd );
		
		ImGui::Spacing();
		if( explicitStartEnd )
		{
			ImGui::DragXYZ( "Start", start, 1.0f, 0.0f, 0.0f, "%.1f" );
			ImGui::DragXYZ( "End", end, 1.0f, 0.0f, 0.0f, "%.1f" );
		}
	}
	
	ImGui::Unindent();
	
	ImGui::End();
}

} //anon namespace

void ToolSelectionWindow()
{
	if( !showToolSelWin ) return;
	
	// TODO: these static variables should probably go in a class or struct
	static bool showLightEditor = true;
	static bool showParticlesEditor = false;
	
	ImGui::Begin( "Show Ingame Editors", &showToolSelWin, 0 );
	
	ImGui::Checkbox( "Light", &showLightEditor );
	ImGui::SameLine();
	ImGui::Checkbox( "Particle", &showParticlesEditor );
	
	if( showLightEditor )
	{
		ShowLightEditor( &showLightEditor );
	}
	
	// TODO: other editor windows..
	ImGui::End();
}

} //namespace Tools
} //namespace BFG
