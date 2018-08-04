/*
 * CameraExplorer.h
 * this file is GPLv3
 *
 *  Created on: 31 de jul. 2018
 *      Author: Biel Bestué de Luna
 */

#ifndef NEO_TOOLS_EDITORS_CAMERAEXPLORER_CAMERAEXPLORER_H_
#define NEO_TOOLS_EDITORS_CAMERAEXPLORER_CAMERAEXPLORER_H_

#include "../../Tools.h"

namespace BFG
{
namespace Tools
{
void CameraExplorer_f();

class CameraInfo
{
public:
	//lens
	bool 	useLens;
	float 	lens_k;
	float 	lens_kcube;
	float 	lens_chromatic;
	int		fov;

	//obturation
	bool 	useMotionBlur;
	bool	useHDR_MotionBlur;
	float	MotionBlur_quality;
	float	MotionBlur_angle;
	//dof
	//exposure

	//imager
	bool	useHDR;
	float	gamma;

	CameraInfo();
	void	Defaults();
	void	GatherCurrent();
};

class blCameraExplorer {
public:
	static void OpenWindow();
	static void Update();
	static bool ShowWindow;
private:
	bool changes;
	bool pause_changes;
	void Init();
	void Clear();
	void Draw();
	void ApplyChanges( CameraInfo camInfo );
	void CloseWindow();

	CameraInfo cur;
	CameraInfo org;
	static blCameraExplorer TheCameraExplorer;
};

} //namespace Tools
} //namespace BFG

#endif /* NEO_TOOLS_EDITORS_CAMERAEXPLORER_CAMERAEXPLORER_H_ */
