/*
 * fontcodec.cpp
 *
 *  Created on: 26 de gen. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#pragma hdrstop

#include "../tools/compilers/compiler_public.h"
#include "../tools/compilers/fontcodec/fontcodec.h"

#include "../framework/Common.h"

namespace BFG
{

fontCodecGlobals_t CompilerGlobals;

/*******************************************************************************
	Compile process
*******************************************************************************/

/*
============
SetDefaultGlobals
============
*/
void SetDefaultGlobals() {
	CompilerGlobals.verbose = false;
	CompilerGlobals.outputFilename = "48.dat";
}

/*
============
FontCompHelp
============
*/
void FontCompHelp() {
/*
    Usage:
		BFGFontTool create-bfg --help
		BFGFontTool decompose-d3 --help

		BFGFontTool create-bfg options...
			converts AngelCode BMFont's .fnt plain-text font descriptor into Doom 3 BFG Edition .dat font file
			-h, --help                 		show this message and exit
			  --bm, --bmfont=VALUE   		file name of the input BMFont (i.e. bm=ArialNarrow.fnt)
			  --bfg, --bfgfont=VALUE		file name of the output BFG font (default: bfg=48.dat)

		BFGFontTool decompose-d3 options...
			decomposes Doom 3's .dat font into BMFont's character descriptions
			-h, --help                 		show this message and exit
			  --d3, --d3font=VALUE   		file name of the input Doom 3 .dat font (i.e. d3=fontimage_48.dat)
			  --d3texs=VALUE         		directory containing font's textures (files like: arial_0_48.dds)
			  --bmfc, --bmfconfig=VALUE	file to which to append character descriptions (in BMFont's configuration file format) (default: myConf.bmfc)
			  --imgout[=VALUE]       		directory to which to write character images (default: bmfc file's directory)
			  --lang, --language,    		comma separated list of The Dark Mod's languages to use during font's conversion (default: all except russian)
											available langs: czech,danish,dutch,english,french,german,hungarian,italian,polish,portuguese,slovak,spanish,russian
			  --remap, --remapdir=VALUE	directory in which The Dark Mod's remap tables are (like: polish.map)
 */

	common->Printf(

		"Usage: fontComp [options] input_font_file_name\n"
		"Options:\n"
		"-h, --help						Show this help message and exit."
		"-v								Verbose"
		//"	 --output=VALUE			File name of the output name different than the default '48.dat' name."
		/*
		"Options:\n"
		"noCurves          = don't process curves\n"
		"noCM              = don't create collision map\n"
		"noAAS             = don't create AAS files\n"
		*/

	);
}


/*
============
fontComp
============
*/
void FontComp( const idCmdArgs& args ) {
	int			i;
	idStr		passedName;

	if( args.Argc() < 2 ) {
		FontCompHelp();
		return;
	}

	common->Printf( "---- compiling font ----\n" );

	SetDefaultGlobals();

	for( i = 1 ; i < args.Argc() ; i++ )
	{
		const char* s;

		s = args.Argv( i );
		if( s[0] == '-' )
		{
			s++;
			if( s[0] == '\0' )
			{
				continue;
			}
		}

		if( !idStr::Icmp( s, "h" ) )
		{
			FontCompHelp();
			return;
		}
		else if( !idStr::Icmp( s, "help" ) )
		{
			FontCompHelp();
			return;
		}
		else if( !idStr::Icmp( s, "v" ) )
		{
			common->Printf( "verbose = true\n" );
			CompilerGlobals.verbose = true;
		}
		/*else if( !idStr::Icmp( s, "output" ) )
		{
			common->Printf( "drawflag = true\n" );
			dmapGlobals.drawflag = true;
		}*/
		else
		{
			break;
		}
	}

	if( i >= args.Argc() )
	{
		common->Error( "Usage: fontComp [options] input_font_file_name\n" );
	}

	passedName = args.Argv( i );		// may have an extension
	passedName.BackSlashesToSlashes();
	if( passedName.Icmpn( "fonts/", 4 ) != 0 )
	{
		passedName = "fonts/" + passedName;
	}

	idStr stripped = passedName;
	stripped.StripFileExtension();
}

/*
============
fontComp_f
============
*/
void FontComp_f( const idCmdArgs& args ) {

	//common->ClearWarnings( "running dmap" );

	// refresh the screen each time we print so it doesn't look
	// like it is hung
	//common->SetRefreshOnPrint( true );
	FontComp( args );
	//common->SetRefreshOnPrint( false );

	//common->PrintWarnings();
}

/*******************************************************************************
	Decompile process
*******************************************************************************/

/*
============
fontDecomp
============
*/
void FontDecomp( const idCmdArgs& args ) {
	//stub //TODO
}

/*
============
fontDecomp_f
============
*/
void FontDecomp_f( const idCmdArgs& args ) {

	//common->ClearWarnings( "running dmap" );

	// refresh the screen each time we print so it doesn't look
	// like it is hung
	//common->SetRefreshOnPrint( true );
	FontDecomp( args );
	//common->SetRefreshOnPrint( false );

	//common->PrintWarnings();
}

} // namespace BFG
