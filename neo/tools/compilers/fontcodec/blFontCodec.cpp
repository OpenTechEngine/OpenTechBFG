/*
 * blFontCodec.cpp
 *
 *  Created on: 4 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#include "blFontCodec.h"
#include "../tools/compilers/fontcodec/BMfont.h"
#include "../tools/compilers/fontcodec/BFGfont.h"

namespace BFG {

blFontCodec::blFontCodec() {
	clear();
}

blFontCodec::~blFontCodec() {
	// TODO Auto-generated destructor stub
}

void blFontCodec::clear() {
	BM_font = NULL;
	BFG_font = NULL;

	fontCodecGlobals.verbose = false;
	fontCodecGlobals.inputFilename = "";
	fontCodecGlobals.outputFilename = "48.dat";
	fontCodecGlobals.inputDirectory = "";
	fontCodecGlobals.decompile = false;
}
/*
============
blFontCodec::FontCompHelp
============
*/

void blFontCodec::FontCompHelp() {
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
		"Usage: fontCodec [options] filename\n"
		"Options:\n"
		"-h, --help						Show this help message and exit.\n"
		"-d, --decompile				Decompile instead of compiling\n"
		"-v								Verbose\n"
		"\n in case of compilations the input folder will be 'fonts', in decompilations 'newfonts'\n"
		//"	 --output=VALUE			File name of the output name different than the default '48.dat' name."
	);
}

/*
============
blFontCodec::GatherComandArgs
============
*/

idStr blFontCodec::GatherComandArgs( const idCmdArgs& args ) {
	int			i;

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
			return '\0';
		}
		else if( !idStr::Icmp( s, "help" ) )
		{
			FontCompHelp();
			return '\0';
		}
		else if( !idStr::Icmp( s, "d" ) )
		{
			fontCodecGlobals.decompile = true;
		}
		else if( !idStr::Icmp( s, "decompile" ) )
		{
			fontCodecGlobals.decompile = true;
		}
		else if( !idStr::Icmp( s, "v" ) )
		{
			common->Printf( "verbose = true\n" );
			fontCodecGlobals.verbose = true;
		}
		/*
		else if( !idStr::Icmp( s, "output" ) )
		{
			common->Printf( "drawflag = true\n" );
			dmapGlobals.drawflag = true;
		}
		*/
		else
		{
			break;
		}
	}

	if( i >= args.Argc() )
	{
		common->Error( "Usage: fontCodec [options] filename\n" );
	}

	return args.Argv( i );
}

/*
============;
blFontCodec::fontCodec
============
*/

void blFontCodec::FontCodec( const idCmdArgs& args ){
	int			i;
	idStr		q_path_to_file;
	idStr		filename;

	if( args.Argc() < 2 ) {
		FontCompHelp();
		return;
	}

	q_path_to_file = blFontCodec::GatherComandArgs( args );		// may have an extension
	if( q_path_to_file.c_str() == '\0' ) {
					return;
	}

	if( fontCodecGlobals.decompile ) {
		fontCodecGlobals.inputDirectory = "newfonts";
		i = 8; // 'newfonts/' --> 8 characters
	} else {
		fontCodecGlobals.inputDirectory = "fonts";
		i = 5;
	}

	q_path_to_file.BackSlashesToSlashes();

	if( q_path_to_file.Icmpn( fontCodecGlobals.inputDirectory + "/", i ) != 0 )
	{
		filename = q_path_to_file;
		q_path_to_file = fontCodecGlobals.inputDirectory + "/" + q_path_to_file;
	}

	q_path_to_file.StripFileExtension();
	filename.StripFileExtension();

	if( fontCodecGlobals.decompile ) {
		filename += ".fnt"
		fontCodecGlobals.outputFilename = filename; // we only do this in decompile because the default accounts for the compile.
		q_path_to_file += ".dat"
		common->Printf( "---- decompiling font ----\n" );
	} else {
		q_path_to_file += ".fnt"
		common->Printf( "---- compiling font ----\n" );
	}
	fontCodecGlobals.inputFilename = q_path_to_file;

	BM_font = new BMfont( this );
	if( BM_font.Load() ) {
		BFG_font = new BFGfont( this );
	}
}

} /* namespace BFG */
