/*
 * CameraExplorer.cpp
 * this file is GPLv3
 *
 *  Created on: 31 de jul. 2018
 *      Author: Biel Bestué de Luna
 */

#include "../cameraExplorer/cameraExplorer.h"
#include "../../../imgui/BFGimgui.h"

#include "../../../renderer/RenderSystem.h"
#include "../../../d3xp/gamesys/SysCvar.h"

namespace BFG
{
namespace Tools
{

CameraInfo::CameraInfo(){
	//GatherCurrent();
	Defaults();
}

void CameraInfo::Defaults() {
	useLens = true;
	lens_k	= -0.12f;
	lens_kcube = 0.1f;
	lens_chromatic = 1.12f;
	fov	= 90;
	/*
	useMotionBlur = true;
		bool	useHDR_MotionBlur;
		float	MotionBlur_quality;
		float	MotionBlur_angle;
		//dof
		//exposure

		//imager
		bool	useHDR;
		float	gamma;
	*/
}
void CameraInfo::GatherCurrent() {

	useLens = r_useLens.GetBool();
	lens_k = r_lens_k.GetFloat();
	lens_kcube = r_lens_kcube.GetFloat();
	lens_chromatic = r_lens_chromatic.GetFloat();
	fov = g_fov.GetInteger();

}

blCameraExplorer blCameraExplorer::TheCameraExplorer;
bool blCameraExplorer::ShowWindow = false;

void blCameraExplorer::Init() {
	Clear();
	org.GatherCurrent();
}

void blCameraExplorer::Clear() {
	cur.GatherCurrent();
	changes = false;
	pause_changes = false;
}

void blCameraExplorer::OpenWindow() {
	if( !ShowWindow ) {
		common->Printf( "Camera Explorer initiated!\n" );
		TheCameraExplorer.Init();
		ShowWindow = true;
	} else {
		ShowWindow = false;
	}
}

void blCameraExplorer::CloseWindow() {
	Clear();
	common->Printf( "Camera Explorer closed!\n" );
	impl::SetReleaseToolMouse( false );
}
void blCameraExplorer::Update() {
	TheCameraExplorer.Draw();
}

void blCameraExplorer::ApplyChanges( CameraInfo camInfo ) {

	g_fov.SetInteger( camInfo.fov );
	r_useLens.SetBool( camInfo.useLens );
	r_lens_k.SetFloat( camInfo.lens_k );
	r_lens_kcube.SetFloat( camInfo.lens_kcube );
	r_lens_chromatic.SetFloat( camInfo.lens_chromatic );
}
void blCameraExplorer::Draw() {
	bool ShowingWindow = ShowWindow;
	CameraInfo endInfo;
	if( ImGui::Begin( "Camera Explorer Window", &ShowingWindow, ImGuiWindowFlags_ShowBorders ) ) {

		changes |= ImGui::SliderInt("Focal Of View", &cur.fov, 1, 180, "%.0f degrees");
		ImGui::Spacing();
		ImGui::Text( "LENS DISTORTION EFFECT" );
		ImGui::Spacing();
		changes |= ImGui::Checkbox( "lens distort", &cur.useLens);
		ImGui::Spacing();
		ImGui::Text( "parameters:" );
		ImGui::Spacing();
		changes |= ImGui::SliderFloat( "k", &cur.lens_k, -15.0f, 5.0f, "%.2f", 2.0f );
		ImGui::Spacing();
		changes |= ImGui::SliderFloat( "kcube", &cur.lens_kcube, -15.0f, 10.0f, "%.2f", 2.0f );
		ImGui::Spacing();
		changes |= ImGui::SliderFloat( "Chromatic aberration", &cur.lens_chromatic, -5.0f, 5.0f, "%.2f", 2.0f );
		ImGui::Spacing();
		ImGui::Text( "you can test several effects at once by pausing the changes,\nalso, you can discard the changes and go back to the initial values." );
		ImGui::Spacing();
		if( ImGui::Button( "Apply" ) ) {
			pause_changes = false; // so the last changes eventually get applied
			ShowingWindow = false;

		}
		ImGui::SameLine();
		if( ImGui::Button( "Discard" ) ) {
			pause_changes = false; //force that last change
			ShowingWindow = false;
			endInfo = org;
		} else {
			if( changes ) {
				endInfo = cur;
			}
		}
		ImGui::SameLine();
		idStr changeButton;
		if( !pause_changes  ) {
			changeButton = "pause changes";
		} else {
			changeButton = "un-pause changes";
		}
		if( ImGui::Button( changeButton ) ) {
			if( !pause_changes  ) {
				pause_changes = true;
			} else {
				pause_changes = false;
			}
		}

		if( changes  && !pause_changes ) {
			ApplyChanges( endInfo );
		}

	}
	ImGui::End();

	if( ShowWindow && !ShowingWindow )
		{
			// TODO: do the same as when pressing cancel?
			ShowWindow = ShowingWindow;
			CloseWindow();
		}
}

} //namespace Tools
} //namespace BFG
