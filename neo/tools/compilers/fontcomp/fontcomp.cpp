/*
 * fontcomp.cpp
 *
 *  Created on: 26 de gen. 2018
 *      Author: biel
 */

#include "../tools/compilers/fontcomp/fontcomp.h"

#include "../tools/compilers/compiler_public.h"

namespace BFG
{

/*
============
fontComp
============
*/
void FontComp( const idCmdArgs& args )
{
	//stub
}

/*
============
fontComp_f
============
*/
void FontComp_f( const idCmdArgs& args )
{

	//common->ClearWarnings( "running dmap" );

	// refresh the screen each time we print so it doesn't look
	// like it is hung
	//common->SetRefreshOnPrint( true );
	FontComp( args );
	//common->SetRefreshOnPrint( false );

	//common->PrintWarnings();
}

} // namespace BFG
