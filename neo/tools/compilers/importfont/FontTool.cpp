/*
 * FontTool.cpp
 *
 *  Created on: 26 de gen. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */


#include "../framework/Common.h"
#include "../importfont/FontMethods.h"
#include "../tools/compilers/compiler_public.h"


namespace BFG
{

/*
============
ImportFont_f
============
*/
void ImportFont_f( const idCmdArgs& args ) {
	common->ClearWarnings( "running the font importer" );

	blFontImporter FontImporter;
	// refresh the screen each time we print so it doesn't look
	// like it is hung
	common->SetRefreshOnPrint( true );

	FontImporter.Process( args );

	common->SetRefreshOnPrint( false );
	common->PrintWarnings();
}

blFontImporter::blFontImporter() {
	BM_font = NULL;
	BFG_font = NULL;

	verbose = false;
	oldSystem = false;

	sharedStruct.relativeFilePath = "";
	sharedStruct.relativeInputDir = "fonts/";
	sharedStruct.relativeOutputDir = "newfonts/";
}

/*
============
blFontImporter::FontCompHelp
============
*/
void blFontImporter::FontCompHelp() {
	common->Printf(
	  //"123456789012345678901234567890123456789012345678" <--48 chars
		"\nUsage: importFont [options] filename\n\n"
		"imports fonts from XML *.fnt files generated\n"
		"with the BMfont program into IdTech X useful\n"
		"*.dat files\n\n"
		"attention! the folder and the file name of the\n" //TODO this shouldn't be the case!
		"*.fnt file must be the same"
		"Options:\n"
		"-h, --help		Show this help and exit.\n"
		"-v				Verbose\n"
		//"-o				D3 Format instead of idTech X's\n" //TODO not yet, and even it might not be necessary at all!
		"\n\n"

	);
}

/*
============
blFontImporter::GatherComandArgs
============
*/
idStr blFontImporter::GatherComandArgs( const idCmdArgs& args ) {
	int i;
	for( i = 1; i < args.Argc(); i++ )
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
		else if( !idStr::Icmp( s, "v" ) )
		{
			common->Printf( "verbose = true\n" );
			verbose = true;
		}
		/*else if( !idStr::Icmp( s, "o" ) )
		{
			common->Printf( "old system = true\n" );
			old = true;
		}*/
		else
		{
			break;
		}
	}

	if( i >= args.Argc() )
	{
		common->Error( "Usage: importFont [options] filename\n" );
	}

	return args.Argv( i );
}

/*
============
blFontImporter::Process
============
*/
void blFontImporter::Process( const idCmdArgs& args ) {
	idStr gatheredText, workingDir;

	if( args.Argc() < 2 ) {
		FontCompHelp();
		return;
	}
	gatheredText = GatherComandArgs( args );

	sharedStruct.relativeFilePath.Append( sharedStruct.relativeInputDir );
	sharedStruct.relativeFilePath.Append( gatheredText );
	sharedStruct.relativeFilePath.BackSlashesToSlashes();

	workingDir = gatheredText.StripFilename();

	sharedStruct.relativeInputDir.Append( workingDir );
	sharedStruct.relativeInputDir.Append( "/" );
	sharedStruct.relativeInputDir.BackSlashesToSlashes();

	sharedStruct.relativeOutputDir.Append( workingDir );
	sharedStruct.relativeOutputDir.Append( "/" );
	sharedStruct.relativeOutputDir.BackSlashesToSlashes();

	/* debug
	common->Printf( "workingDir:			'%s'\n"
					"relativeFilePath: 		'%s'\n"
			        "relativeInputDir: 		'%s'\n"
					"relativeOutputDir: 	'%s'\n",
					workingDir.c_str(),
					sharedStruct.relativeFilePath.c_str(),
					sharedStruct.relativeInputDir.c_str(),
					sharedStruct.relativeOutputDir.c_str()
			      );
	*/

	common->Printf( "\n---- Import font ----\n\n" );

	BM_font = new(TAG_TOOLS) BMfont( sharedStruct );
	common->Printf( "Reading the info in the BM font file\n" );
	if( BM_font->Read() ) {
		common->Printf( "All the info in the BM font has been gathered\n" );
		//BM_font->DeclareContents();
		//if( verbose ) { BM_font->DeclareContents(); };
		BFG_font = new(TAG_TOOLS) BFGfont( sharedStruct );
		common->Printf( "\nCreating and feeding the BFG font\n" );
		BFG_font->Load( BM_font );
		BFG_font->CreateFolders();
		common->Printf( "Copying image pages to the folder\n" );
		BFG_font->CopyPageFiles();
		//BFG_font->DeclareContents();
		//if( fontCodecGlobals.verbose )  { BFG_font->DeclareContents(); }
		common->Printf( "\nSaving the final BFG font *.dat file\n" );
		BFG_font->Save();
	} else {
		common->Error( "Can't open or read the BM font file at: '%s'", sharedStruct.relativeInputDir.c_str() );
	}

	common->Printf( "\n---- Importing finished ----\n\n" );

	delete BM_font;
	delete BFG_font;
}

} // namespace BFG
