
#ifndef NEO_TOOLS_TOOLS_H_
#define NEO_TOOLS_TOOLS_H_
#include "../idlib/CmdArgs.h"
#include "compilers/compiler_public.h"
#include <idlib/Dict.h>

// in moddable doom3 Game.h was in framework/ and not to be modified by mods
// we need it for GameEdit definition and idEntity declaration
#include <d3xp/Game.h>

namespace BFG
{

void ShowEditors_f( const idCmdArgs& args );

namespace Tools
{

void ToolSelectionWindow();

void LightEditorInit( const idDict* dict, idEntity* entity );

}

}//namespace BFG

#endif /* NEO_TOOLS_TOOLS_H_ */
