/*
 * FontTool.cxx
 *
 *  Created on: 26 de gen. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */


#include "../framework/Common.h"
#include "../tools/compilers/compiler_public.h"

#include "../tools/compilers/fontcodec/blFontCodec.h"

namespace BFG
{

/*
============
FontCodec_f
============
*/

void FontCodec_f( const idCmdArgs& args ) {
	common->ClearWarnings( "running the font compiler / decompiler" );

	blFontCodec FontCodec;
	FontCodec = new blFontCodec;
	// refresh the screen each time we print so it doesn't look
	// like it is hung
	common->SetRefreshOnPrint( true );

	FontCodec.FontCodec( args );

	common->SetRefreshOnPrint( false );
	common->PrintWarnings();
}

} // namespace BFG
