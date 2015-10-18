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

// a GUI light editor, based loosely on the one from original Doom3 (neo/tools/radiant/LightDlg.*)
// LightInfo was CLightInfo, the LightEditor itself was written from scratch.

#ifndef NEO_TOOLS_EDITORS_LIGHTEDITOR_H_
#define NEO_TOOLS_EDITORS_LIGHTEDITOR_H_

#include <idlib/Dict.h>
#include "../Tools.h"

namespace BFG
{
namespace Tools
{

class LightInfo
{
public:
	bool		pointLight;
	float		fallOff;
	idStr		strTexture;
	bool		equalRadius;
	bool		explicitStartEnd;
	idVec3		lightStart;
	idVec3		lightEnd;
	idVec3		lightUp;
	idVec3		lightRight;
	idVec3		lightTarget;
	idVec3		lightCenter;
	idVec3		color;
	bool		fog;
	idVec4		fogDensity;
	
	bool		strobe;
	float		strobeSpeed;
	bool		rotate;
	float		rotateSpeed;
	
	idVec3		lightRadius;
	bool		castShadows;
	bool		castSpecular;
	bool		castDiffuse;
	bool		hasCenter;
	bool		isParallel;
	
	LightInfo();
	
	void		Defaults();
	void		DefaultProjected();
	void		DefaultPoint();
	void		FromDict( const idDict* e );
	void		ToDict( idDict* e );
	void		ToDictFromDifferences( idDict* e, const idDict* differences );
	void		ToDictWriteAllInfo( idDict* e );
};

class LightEditor
{
	idStr name;
	LightInfo original;
	LightInfo cur; // current status of the light
	
	idEntity* lightEntity;
	
	void Init( const idDict* dict, idEntity* light );
	void Reset();
	
	void DrawWindow();
	
	void TempApplyChanges();
	void SaveChanges();
	void CancelChanges();
	
	LightEditor()
	{
		Reset();
	}
	
	static LightEditor TheLightEditor; // FIXME: maybe at some point we could allow more than one..
	
public:
	static void ReInit( const idDict* dict, idEntity* light );
	
	static void Draw();
	
	static bool showIt;
};

} //namespace Tools
} //namespace BFG

#endif /* NEO_TOOLS_EDITORS_LIGHTEDITOR_H_ */
