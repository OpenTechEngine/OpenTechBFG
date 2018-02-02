/*
 * fontdecomp.cpp
 *
 *  Created on: 01 de feb. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#include "../tools/compilers/compiler_public.h"
#include "../tools/compilers/fontcodec/fontcodec.h"
#include "../framework/Common.h"

namespace BFG
{

/*
============
fontDecomp
============
*/
void FontDecomp( const idCmdArgs& args )
{
	//stub //TODO
}

/*
============
fontDecomp_f
============
*/
void FontDecomp_f( const idCmdArgs& args )
{

	//common->ClearWarnings( "running dmap" );

	// refresh the screen each time we print so it doesn't look
	// like it is hung
	//common->SetRefreshOnPrint( true );
	FontDecomp( args );
	//common->SetRefreshOnPrint( false );

	//common->PrintWarnings();
}

}
