/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company.
Copyright (C) 2015 Daniel Gibson

This file is part of the Doom 3 GPL Source Code ("Doom 3 Source Code").

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#include "../Tools.h"
#include "LightEditor.h"

#include "../imgui/BFGimgui.h"

namespace BFG
{
namespace Tools
{

void LightInfo::Defaults()
{
	pointLight = true;
	fallOff = 1.0f;
	strTexture = "";
	equalRadius = true;
	explicitStartEnd = false;
	lightStart.Zero();
	lightEnd.Zero();
	lightUp.Zero();
	lightRight.Zero();
	lightTarget.Zero();
	lightCenter.Zero();
	color[0] = color[1] = color[2] = 1.0f;
	fog = false;
	fogDensity.Zero();
	
	strobe = false;
	strobeSpeed = 0.0f;
	rotate = false;
	rotateSpeed = 0.0f;
	
	lightRadius.Zero();
	castShadows = true;
	castSpecular = true;
	castDiffuse = true;
	hasCenter = false;
	isParallel = false;
}


void LightInfo::DefaultPoint()
{
	idVec3 oldColor = color;
	Defaults();
	color = oldColor;
	pointLight = true;
}

void LightInfo::DefaultProjected()
{
	idVec3 oldColor = color;
	Defaults();
	color = oldColor;
	pointLight = false;
	lightTarget[2] = -256;
	lightUp[1] = -128;
	lightRight[0] = -128;
}

void LightInfo::FromDict( const idDict* e )
{

	lightRadius.Zero();
	lightTarget.Zero();
	lightRight.Zero();
	lightUp.Zero();
	lightStart.Zero();
	lightEnd.Zero();
	lightCenter.Zero();
	
	castShadows = !e->GetBool( "noshadows" );
	castSpecular = !e->GetBool( "nospecular" );
	castDiffuse = !e->GetBool( "nodiffuse" );
	fallOff = e->GetFloat( "falloff" );
	strTexture = e->GetString( "texture" );
	
	isParallel = e->GetBool( "parallel" );
	
	if( !e->GetVector( "_color", "", color ) )
	{
		color[0] = color[1] = color[2] = 1.0f;
		// NOTE: like the game, imgui uses color values between 0.0 and 1.0
		//       even though it displays them as 0 to 255
	}
	
	if( e->GetVec4( "fog", "", fogDensity ) )
	{
		fog = true;
	}
	else
	{
		fog = false;
	}
	
	if( e->GetVector( "light_right", "", lightRight ) )
	{
		// projected light
		pointLight = false;
		e->GetVector( "light_target", "", lightTarget );
		e->GetVector( "light_up", "", lightUp );
		if( e->GetVector( "light_start", "", lightStart ) )
		{
			// explicit start and end points
			explicitStartEnd = true;
			if( !e->GetVector( "light_end", "", lightEnd ) )
			{
				// no end, use target
				lightEnd = lightTarget;
			}
		}
		else
		{
			explicitStartEnd = false;
			// create a start a quarter of the way to the target
			lightStart = lightTarget * 0.25;
			lightEnd = lightTarget;
		}
	}
	else
	{
		pointLight = true;
		if( e->GetVector( "light_radius", "", lightRadius ) )
		{
			equalRadius = false;
		}
		else
		{
			float radius = e->GetFloat( "light" );
			if( radius == 0 )
			{
				radius = 300;
			}
			lightRadius[0] = lightRadius[1] = lightRadius[2] = radius;
			equalRadius = true;
		}
		if( e->GetVector( "light_center", "", lightCenter ) )
		{
			hasCenter = true;
		}
	}
}

void LightInfo::ToDictFromDifferences( idDict* e, const idDict* differences )
{
	for( int i = 0 ; i < differences->GetNumKeyVals() ; i ++ )
	{
		const idKeyValue* kv = differences->GetKeyVal( i );
		
		if( kv->GetValue().Length() > 0 )
		{
			e->Set( kv->GetKey() , kv->GetValue() );
		}
		else
		{
			e->Delete( kv->GetKey() );
		}
		
		common->Printf( "Applied difference: %s %s\n" , kv->GetKey().c_str() , kv->GetValue().c_str() );
	}
}

//write all info to a dict, regardless of light type
void LightInfo::ToDictWriteAllInfo( idDict* e )
{
	e->Set( "noshadows", ( !castShadows ) ? "1" : "0" );
	e->Set( "nospecular", ( !castSpecular ) ? "1" : "0" );
	e->Set( "nodiffuse", ( !castDiffuse ) ? "1" : "0" );
	
	e->SetFloat( "falloff", fallOff );
	
	if( strTexture.Length() > 0 )
	{
		e->Set( "texture", strTexture );
	}
	
	e->SetVector( "_color", color );
	
	if( !equalRadius )
	{
		e->SetVector( "light_radius", lightRadius );
	}
	else
	{
		idVec3 tmp( lightRadius[0] ); // x, y and z have the same value
		e->SetVector( "light_radius", tmp );
	}
	
	e->SetVector( "light_center", lightCenter );
	e->Set( "parallel", isParallel ? "1" : "0" );
	
	e->SetVector( "light_target", lightTarget );
	e->SetVector( "light_up", lightUp );
	e->SetVector( "light_right", lightRight );
	e->SetVector( "light_start", lightStart );
	e->SetVector( "light_end", lightEnd );
}

void LightInfo::ToDict( idDict* e )
{

	e->Delete( "noshadows" );
	e->Delete( "nospecular" );
	e->Delete( "nodiffuse" );
	e->Delete( "falloff" );
	e->Delete( "parallel" );
	e->Delete( "texture" );
	e->Delete( "_color" );
	e->Delete( "fog" );
	e->Delete( "light_target" );
	e->Delete( "light_right" );
	e->Delete( "light_up" );
	e->Delete( "light_start" );
	e->Delete( "light_end" );
	e->Delete( "light_radius" );
	e->Delete( "light_center" );
	e->Delete( "light" );
	
	e->Set( "noshadows", ( !castShadows ) ? "1" : "0" );
	e->Set( "nospecular", ( !castSpecular ) ? "1" : "0" );
	e->Set( "nodiffuse", ( !castDiffuse ) ? "1" : "0" );
	
	e->SetFloat( "falloff", fallOff );
	
	if( strTexture.Length() > 0 )
	{
		e->Set( "texture", strTexture );
	}
	
	e->SetVector( "_color", color );
	
	if( fog )
	{
		idVec4 tmp( fogDensity );
		tmp *= 1.0f / 255.0f; // TODO: why not just make fogdensity values between 0 and 1 to start with?
		e->SetVec4( "fog", tmp );
	}
	
	if( pointLight )
	{
		if( !equalRadius )
		{
			e->SetVector( "light_radius", lightRadius );
		}
		else
		{
			idVec3 tmp( lightRadius[0] ); // x, y and z have the same value
			e->SetVector( "light_radius", tmp );
		}
		
		if( hasCenter )
		{
			e->SetVector( "light_center", lightCenter );
		}
		
		if( isParallel )
		{
			e->Set( "parallel", "1" );
		}
	}
	else
	{
		e->SetVector( "light_target", lightTarget );
		e->SetVector( "light_up", lightUp );
		e->SetVector( "light_right", lightRight );
		if( explicitStartEnd )
		{
			e->SetVector( "light_start", lightStart );
			e->SetVector( "light_end", lightEnd );
		}
	}
}

LightInfo::LightInfo()
{
	Defaults();
}


// ########### LightEditor #############

// static
LightEditor LightEditor::TheLightEditor;

// static
bool LightEditor::showIt = false;

// static
void LightEditor::ReInit( const idDict* dict, idLight* light )
{
	// TODO: if the lighteditor is currently shown, show a warning first about saving current changes to the last light?
	TheLightEditor.Init( dict, light );
}

// static
void LightEditor::Draw()
{
	TheLightEditor.DrawWindow();
}

void LightEditor::Init( const idDict* dict, idLight* light )
{
	Reset();
	if( dict )
	{
		original.FromDict( dict );
		//current = original;
		cur.FromDict( dict );
		
		name = dict->GetString( "name", "" );
	}
	this->light = light;
}

void LightEditor::Reset()
{
	name.Clear();
	original.Defaults();
	cur.Defaults();
	light = NULL;
}

void LightEditor::TempApplyChanges()
{
	if( light != NULL )
	{
		idDict d;
		cur.ToDict( &d );
		gameEdit->EntityChangeSpawnArgs( light, &d );
		gameEdit->EntityUpdateChangeableSpawnArgs( light, NULL );
	}
}

void LightEditor::SaveChanges()
{
	TempApplyChanges();
	gameEdit->MapSave();
}

void LightEditor::CancelChanges()
{
	if( light != NULL )
	{
		idDict d;
		original.ToDict( &d );
		gameEdit->EntityChangeSpawnArgs( light, &d );
		gameEdit->EntityUpdateChangeableSpawnArgs( light, NULL );
	}
}

// a kinda ugly hack to get a float* (as used by imgui) from idVec3
static float* vecToArr( idVec3& v )
{
	return &v.x;
}

void LightEditor::DrawWindow()
{
	idStr title( "Light Editor: " );
	if( name.Length() == 0 )
	{
		title += "no Light selected!";
	}
	else
	{
		title += name;
	}
	
	ImGui::Begin( title, &showIt, ImGuiWindowFlags_ShowBorders );
	
	bool changes = false;
	
	changes |= ImGui::Checkbox( "Cast Shadows", &cur.castShadows );
	ImGui::SameLine();
	changes |= ImGui::Checkbox( "Cast Diffuse", &cur.castDiffuse );
	changes |= ImGui::Checkbox( "Cast Specular", &cur.castSpecular );
	
	
	ImGui::Spacing();
	
	changes |= ImGui::ColorEdit3( "Color", vecToArr( cur.color ) );
	
	// TODO: texture
	// TODO: fog, fogDensity
	
	ImGui::Spacing();
	
	int lightSelectionRadioBtn = cur.pointLight ? 0 : 1;
	
	changes |= ImGui::RadioButton( "Point Light", &lightSelectionRadioBtn, 0 );
	ImGui::SameLine();
	changes |= ImGui::RadioButton( "Projected Light", &lightSelectionRadioBtn, 1 );
	
	cur.pointLight = ( lightSelectionRadioBtn == 0 );
	
	ImGui::Indent();
	
	ImGui::Spacing();
	
	if( lightSelectionRadioBtn == 0 )
	{
		ImGui::PushItemWidth( -1.0f ); // align end of Drag* with right window border
		
		changes |= ImGui::Checkbox( "Equilateral Radius", &cur.equalRadius );
		ImGui::Text( "Radius:" );
		ImGui::Indent();
		if( cur.equalRadius )
		{
			if( ImGui::DragFloat( "(in all dirs)##radEquil", &cur.lightRadius.x, 1.0f, 0.0f, 10000.0f, "%.1f" ) )
			{
				cur.lightRadius.z = cur.lightRadius.y = cur.lightRadius.x;
				changes = true;
			}
		}
		else
		{
			changes |= ImGui::DragVec3( "##radXYZ", cur.lightRadius );
		}
		ImGui::Unindent();
		
		ImGui::Spacing();
		
		// TODO: this could as well be a slider or something, if 0/0.5/1 is too restricting
		
		ImGui::Text( "Fall-off:" );
		ImGui::SameLine();
#if 0
		ImGui::RadioButton( "0.0", &fallOffRadio, 0 );
		ImGui::SameLine();
		ImGui::RadioButton( "0.5", &fallOffRadio, 1 );
		ImGui::SameLine();
		ImGui::RadioButton( "1.0", &fallOffRadio, 2 );
#endif // 0
		
		// a slider is easier than radiobuttons.. does it really have to be radiobuttons?
		changes |= ImGui::SliderFloat( "Fall-off", &cur.fallOff, 0.0f, 1.0f, "%.1f" );
		
		ImGui::Spacing();
		
		changes |= ImGui::Checkbox( "Parallel", &cur.isParallel );
		
		ImGui::Spacing();
		
		changes |= ImGui::Checkbox( "Center", &cur.hasCenter );
		if( cur.hasCenter )
		{
			ImGui::Indent();
			changes |= ImGui::DragVec3( "##centerXYZ", cur.lightCenter, 1.0f, 0.0f, 10000.0f, "%.1f" );
			ImGui::Unindent();
		}
		ImGui::PopItemWidth(); // back to default alignment on right side
	}
	else if( lightSelectionRadioBtn == 1 )
	{
		changes |= ImGui::DragVec3( "Target", cur.lightTarget, 1.0f, 0.0f, 0.0f, "%.1f" );
		changes |= ImGui::DragVec3( "Right", cur.lightRight, 1.0f, 0.0f, 0.0f, "%.1f" );
		changes |= ImGui::DragVec3( "Up", cur.lightUp, 1.0f, 0.0f, 0.0f, "%.1f" );
		
		ImGui::Spacing();
		
		changes |= ImGui::Checkbox( "Explicit start/end points", &cur.explicitStartEnd );
		
		ImGui::Spacing();
		if( cur.explicitStartEnd )
		{
			changes |= ImGui::DragVec3( "Start", cur.lightStart, 1.0f, 0.0f, 0.0f, "%.1f" );
			changes |= ImGui::DragVec3( "End", cur.lightEnd, 1.0f, 0.0f, 0.0f, "%.1f" );
		}
	}
	
	ImGui::Unindent();
	
	// TODO: "Save to map" / "Cancel" buttons
	
	ImGui::End();
	
	if( changes )
	{
		TempApplyChanges();
		printf( "## applying changes!\n" );
	}
}

} //namespace Tools
} //namespace BFG
