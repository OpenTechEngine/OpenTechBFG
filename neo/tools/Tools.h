/*
 * this file is GPLv3
 */

#ifndef NEO_TOOLS_TOOLS_H_
#define NEO_TOOLS_TOOLS_H_
#include "../idlib/CmdArgs.h"
#include "../tools/compilers/compiler_public.h"
#include "../tools/editors/editors_public.h"
#include <idlib/Dict.h>

// in moddable doom3 Game.h was in framework/ and not to be modified by mods
// we need it for GameEdit definition and idEntity declaration
#include <d3xp/Game.h>

namespace BFG
{

void ShowEditors_f( const idCmdArgs& args );

namespace Tools
{

// things in impl need to be used in at least one other file, but should generally not be touched
namespace impl
{

void SetReleaseToolMouse( bool doRelease );

} //namespace impl

bool ReleaseMouseForTools();

bool AreEditorsActive();

void DrawToolWindows();

void CameraExplorerInit();

void LightEditorInit( const idDict* dict, idEntity* entity );

}//namespace tools

}//namespace BFG

#endif /* NEO_TOOLS_TOOLS_H_ */
