/*
 * fontcodec.h
 *
 *  Created on: 26 de gen. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

//#include <rapidxml>
#include "../../libs/rapidxml/rapidxml-1.13/rapidxml.hpp"

#include "../idlib/Str.h"
#include "../idlib/containers/List.h"

#include "../tools/compilers/fontcodec/BMfont.h"
#include "../tools/compilers/fontcodec/BFGfont.h"


namespace BFG
{

typedef struct
{
	bool	verbose;
	idStr	outputFilename;
} fontCodecGlobals_t;

/*******************************************************************************
	Compile process
*******************************************************************************/

void SetDefaultGlobals();
void FontCompHelp();
void FontComp( const idCmdArgs& args );
void FontComp_f( const idCmdArgs& args );

/*******************************************************************************
	Decompile process
*******************************************************************************/

void FontDecomp( const idCmdArgs& args );
void FontDecomp_f( const idCmdArgs& args );

} // namespace BFG
