#include "editors/cameraExplorer/cameraExplorer.h"
#include "../imgui/BFGimgui.h"
#include "../idlib/CmdArgs.h"

#include "editors/LightEditor.h"

namespace BFG
{

extern idCVar g_editEntityMode;

static bool releaseMouse = false;
#if 0 // currently this doesn't make too much sense
void ShowEditors_f( const idCmdArgs& args )
{
	showToolWindows = true;
}
#endif // 0

void CameraExplorer_f( const idCmdArgs& args ) {
	Tools::CameraExplorerInit();
}

namespace Tools
{

// things in impl need to be used in at least one other file, but should generally not be touched
namespace impl
{

void SetReleaseToolMouse( bool doRelease )
{
	releaseMouse = doRelease;
}

} //namespace impl

bool AreEditorsActive()
{
	// FIXME: this is not exactly clean and must be changed if we ever support game dlls
	//return g_editEntityMode.GetInteger() > 0;
	return true;

}

bool ReleaseMouseForTools()
{
	return AreEditorsActive() && releaseMouse;
}

void DrawToolWindows()
{
#if 0
	ImGui::Begin( "Show Ingame Editors", &showToolWindows, 0 );
	
	ImGui::Checkbox( "Light", &LightEdicameraExp.tor::showIt );
	ImGui::SameLine();
	ImGui::Checkbox( "Particle", &showParticlesEditor );
#endif // 0

	if( LightEditor::showIt )
	{
		LightEditor::Draw();
	}
	if( blCameraExplorer::ShowWindow )
	{
		blCameraExplorer::Update();
	}
	
	// TODO: other editor windows..
	//ImGui::End();
}
void CameraExplorerInit() {
	impl::SetReleaseToolMouse( true );
	blCameraExplorer::OpenWindow();
}

void LightEditorInit( const idDict* dict, idEntity* ent )
{
	if( dict == NULL || ent == NULL ) return;
	
	// NOTE: we can't access idEntity (it's just a declaration), because it should
	// be game/mod specific. but we can at least check the spawnclass from the dict.
	idassert( idStr::Icmp( dict->GetString( "spawnclass" ), "idLight" ) == 0
			  && "LightEditorInit() must only be called with light entities or NULL!" );
			  
			  
	LightEditor::showIt = true;
	impl::SetReleaseToolMouse( true );
	
	LightEditor::ReInit( dict, ent );
}
} //namespace Tools
} //namespace BFG
