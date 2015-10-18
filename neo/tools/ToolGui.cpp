#include "../imgui/BFGimgui.h"
#include "../idlib/CmdArgs.h"

#include "editors/LightEditor.h"

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

// TODO: these static variables should probably go in a class or struct
// or they should possibly be replaced by com_editors or whatever it was
static bool showParticlesEditor = false;

} //anon namespace

void ToolSelectionWindow()
{
	if( !showToolSelWin ) return;
	
	ImGui::Begin( "Show Ingame Editors", &showToolSelWin, 0 );
	
	ImGui::Checkbox( "Light", &LightEditor::showIt );
	ImGui::SameLine();
	ImGui::Checkbox( "Particle", &showParticlesEditor );
	
	if( LightEditor::showIt )
	{
		LightEditor::Draw();
	}
	
	// TODO: other editor windows..
	ImGui::End();
}

void LightEditorInit( const idDict* dict, idEntity* ent )
{
	if( dict == NULL || ent == NULL ) return;
	
	// NOTE: we can't access idEntity (it's just a declaration), because it should
	// be game/mod specific. but we can at least check the spawnclass from the dict.
	idassert( idStr::Icmp( dict->GetString( "spawnclass" ), "idLight" ) == 0
			  && "LightEditorInit() must only be called with light entities or NULL!" );
			  
			  
	LightEditor::showIt = true;
	showToolSelWin = true;
	
	LightEditor::ReInit( dict, ent );
}

} //namespace Tools
} //namespace BFG
