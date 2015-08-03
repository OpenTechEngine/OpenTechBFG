
#ifndef NEO_TOOLS_TOOLS_H_
#define NEO_TOOLS_TOOLS_H_
#include "../idlib/CmdArgs.h"
#include "compilers/compiler_public.h"
#include <idlib/Dict.h>

namespace BFG
{

void ShowEditors_f( const idCmdArgs& args );

namespace Tools
{

void ToolSelectionWindow();

void LightEditorInit( const idDict* dict, void* entity );

}

}//namespace BFG

#endif /* NEO_TOOLS_TOOLS_H_ */
