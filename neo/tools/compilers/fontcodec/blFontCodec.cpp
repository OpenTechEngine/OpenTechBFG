/*
 * blFontCodec.cpp
 *
 *  Created on: 4 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#include "blFontCodec.h"

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
	fontCodecGlobals.outputDirectory = "";
	fontCodecGlobals.fontName = "";
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
	  //"123456789012345678901234567890123456789012345678" <--48 chars
		"\nUsage: fontCodec [options] filename\n\n"
		"Options:\n"
		"-h, --help           Show this help and exit.\n"
		"-d, --decompile      Decompile instead of compiling\n"
	    //"    --output=VALUE   File name of the output name different than the default '48.dat' name."
		"-v                   Verbose\n"
		"\nin case of compilations into BFG the input folder will be 'fonts',\n in decompilations from BFG 'newfonts'\n"

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
		/*
		else if( !idStr::Icmp( s, "help" ) )
		{
			FontCompHelp();
			return '\0';
		}
		*/
		else if( !idStr::Icmp( s, "d" ) )
		{
			fontCodecGlobals.decompile = true;
		}
		/*
		else if( !idStr::Icmp( s, "decompile" ) )
		{
			fontCodecGlobals.decompile = true;
		}
		*/
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
	int			i, o;
	idStr		q_path_to_inputfile, q_path_to_outputfile, workingFontDirectory;
	idStr		inputFilename, outputFilename;

	/*
	 * the system should be: "fonts" | "newfonts"/"workingFontDirectory"/"inputFilename" | "outputFilename"
	 */

	if( args.Argc() < 2 ) {
		FontCompHelp();
		return;
	}

	q_path_to_inputfile = GatherComandArgs( args );		// may have an extension
	/*
	if( q_path_to_inputfile.Icmp( '\0') == 0 ){   		<-- FIXME this conditional makes the program fail
		return;
	}
	*/

	q_path_to_outputfile = q_path_to_inputfile; //FIXME in compilation it should be 48.dat and in decompilation should be the name of the directory the font is in!

	if( fontCodecGlobals.decompile ) {
		fontCodecGlobals.inputDirectory = "newfonts";
		fontCodecGlobals.outputDirectory = "fonts";
		i = 8; // 'newfonts/' --> 8 characters starting from 0
		o = 5;
	} else {
		fontCodecGlobals.inputDirectory = "fonts";
		fontCodecGlobals.outputDirectory = "newfonts";
		i = 5;
		o = 8;
	}

	q_path_to_inputfile.BackSlashesToSlashes();
	q_path_to_outputfile.BackSlashesToSlashes();

	if( q_path_to_inputfile.Icmpn( fontCodecGlobals.inputDirectory + "/", i ) != 0 )
	{
		inputFilename = q_path_to_inputfile;
		q_path_to_inputfile = fontCodecGlobals.inputDirectory + "/" + q_path_to_inputfile;
	}

	if( q_path_to_outputfile.Icmpn( fontCodecGlobals.outputDirectory + "/", o ) != 0 )
	{
		outputFilename = q_path_to_outputfile;
		q_path_to_outputfile = fontCodecGlobals.outputDirectory + "/" + q_path_to_outputfile;
	}

	q_path_to_inputfile.StripFileExtension();
	q_path_to_outputfile.StripFileExtension();
	inputFilename.StripFileExtension();
	outputFilename.StripFileExtension();

	if( fontCodecGlobals.decompile ) {
		inputFilename += ".fnt";
		q_path_to_inputfile += ".dat";
		common->Printf( "---- decompiling font ----\n" );
	} else {
		inputFilename += ".dat";
		q_path_to_inputfile += ".fnt";
		common->Printf( "---- compiling font ----\n" );
	}
	fontCodecGlobals.inputFilename = q_path_to_inputfile;
	fontCodecGlobals.outputFilename = inputFilename;

	bool filExists = common->FileExists( fontCodecGlobals.inputFilename.c_str() );

	common->Printf( "checking whether '%s' exists in the file system\n", fontCodecGlobals.inputFilename.c_str() );

	if ( filExists ) {
		common->Printf( "the file '%s' exists!", fontCodecGlobals.inputFilename.c_str() );
	} else {
		common->Error( "the file '%s' doesn't exist!", fontCodecGlobals.inputFilename.c_str() );
	}

	if( fontCodecGlobals.decompile ) {
		//BFG_font = new(TAG_TOOLS) BFGfont();
		//TODO check if BFG fonts can be read!
		common->Error( "at the moment, there isn't any method specified for this process!" );
	} else {
		common->Printf( "creating a BM font at %s\n", fontCodecGlobals.inputFilename.c_str() );
		/*
		BM_font = new(TAG_TOOLS) BMfont( fontCodecGlobals.inputFilename );
		common->Printf( "reading the BM font\n" );
		if( BM_font->Read() ) {
			common->Printf( "creating a BFG font\n" );
			//BFG_font = new(TAG_TOOLS) BFGfont();
		} else {
			common->Error( "Can't open font at: %s", q_path_to_inputfile.c_str() );
		}
		*/
	}


}

} /* namespace BFG */
