/*
 * FontMethods.cpp
 *
 *  Created on: 3 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

//#include <rapidxml>
#include "../importfont/FontMethods.h"

#include "../../libs/rapidxml/rapidxml-1.13/rapidxml.hpp"
#include "../../libs/rapidxml/rapidxml-1.13/rapidxml_utils.hpp"
#include "../framework/File.h"
#include "../framework/Common.h"

namespace BFG {

//BMfont

/*
 * glyphs
 */

BMglyph::BMglyph() {
	Clear();
}

void BMglyph::Clear() {
	glyphStructue.id = 0;
	glyphStructue.x = 0;
	glyphStructue.y = 0;
	glyphStructue.width = 0;
	glyphStructue.height = 0;
	glyphStructue.xoffset = 0;
	glyphStructue.yoffset = 0;
	glyphStructue.xadvance = 0;
	glyphStructue.page = 0;
	glyphStructue.chnl = 0;
}

void BMglyph::Read(int _id, int _x, int _y, int _width, int _height, int _xoffset, int _yoffset, int _xadvance, int _page, int _chnl) {
	glyphStructue.id = _id;
	glyphStructue.x = _x;
	glyphStructue.y = _y;
	glyphStructue.width = _width;
	glyphStructue.height = _height;
	glyphStructue.xoffset = _xoffset;
	glyphStructue.yoffset = _yoffset;
	glyphStructue.xadvance = _xadvance;
	glyphStructue.page = _page;
	glyphStructue.chnl = _chnl;
}

/*
 * pages
 */

BMpage::BMpage() {
	id = 0;
	qPath_ImageFile = "";
}

void BMpage::Read( int id_num, idStr image_file ) {
	id = id_num;
	qPath_ImageFile = image_file;
}

/*
 * fonts
 */

BMfont::BMfont( sharedStruct_t _sharedStruct ) {
	Clear();
	sharedStruct = _sharedStruct;
}

BMfont::~BMfont() {
	Clear();
}

void BMfont::Clear() {
	glyphList.Clear();
	pageList.Clear();

	sharedStruct.relativeFilePath = "";
	sharedStruct.relativeInputDir = "";
	sharedStruct.relativeOutputDir = "";

	processStrucutre.faceName = "";
	processStrucutre.size = 0;
	processStrucutre.bold = false;
	processStrucutre.italic = false;
	processStrucutre.charset = "";
	processStrucutre.unicode = false;
	processStrucutre.heightStretchPercent = 0;
	processStrucutre.fontSmoothing = 0;
	processStrucutre.antiAliasLevel = 0;
	processStrucutre.paddingT = 0;
	processStrucutre.paddingR = 0;
	processStrucutre.paddingB = 0;
	processStrucutre.paddingL = 0;
	processStrucutre.spacingHoriz = 0;
	processStrucutre.spacingVert = 0;
	processStrucutre.outlineThickness = 0;

	generatedFontStructure.lineHeight = 0;
	generatedFontStructure.fontBase = 0;
	generatedFontStructure.scaleW = 0;
	generatedFontStructure.scaleH = 0;
	generatedFontStructure.numPages = 0;
	generatedFontStructure.packed = false;
	generatedFontStructure.alphaChnl = 0;
	generatedFontStructure.redChnl = 0;
	generatedFontStructure.greenChnl = 0;
	generatedFontStructure.blueChnl = 0;
}

bool BMfont::Read(void) {

	if( sharedStruct.relativeFilePath == "\0" ) {
		common->Error( "BMfont: file path is empty!\n" );
	}
	if ( fileSystem->FindFile( sharedStruct.relativeFilePath ) == FIND_NO ) {
		common->Error( "BMfont: file path '%s' leads to nothing!\n", sharedStruct.relativeFilePath.c_str() );
	}

	idStr value, textToParse;

	//rapidxml::file<> xmlFile(fntFile); //it seems it doesn't work? maybe the path should be given in full instead of relative?
	rapidxml::xml_document<> doc;

	if ( common->GetTextBuffer( sharedStruct.relativeFilePath, textToParse ) < 0 ) {
		common->Error( "BMfont: Error getting the file '%s': couldn't read the file\n", sharedStruct.relativeFilePath.c_str() );
	}

	doc.parse<0>( ( char* )textToParse.c_str() );
	//doc.parse<0>( xmlFile.data() );

	rapidxml::xml_node<> *nodeFont = doc.first_node("font");
	rapidxml::xml_node<> *nodeInfo = nodeFont->first_node("info");
	rapidxml::xml_node<> *nodeCommon = nodeFont->first_node("common");
	rapidxml::xml_node<> *nodePages = nodeFont->first_node("pages");
	rapidxml::xml_node<> *nodeChars = nodeFont->first_node("chars");

	//capture info
	//common->Printf( "capture info\n" );

	processStrucutre.faceName = nodeInfo->first_attribute( "face" )->value();
	value = nodeInfo->first_attribute( "size" )->value();
	processStrucutre.size =  value.c_int();
	processStrucutre.bold = *nodeInfo->first_attribute( "bold" )->value() == true;
	processStrucutre.italic = *nodeInfo->first_attribute( "italic" )->value() == true;
	processStrucutre.unicode = *nodeInfo->first_attribute( "unicode" )->value() == true;
	value = nodeInfo->first_attribute( "stretchH" )->value();
	processStrucutre.heightStretchPercent = value.c_int();
	processStrucutre.fontSmoothing = *nodeInfo->first_attribute( "smooth" )->value() == true;
	value = nodeInfo->first_attribute( "aa" )->value();
	processStrucutre.antiAliasLevel = value.c_int();

	//common->Printf( "capture padding\n" );

	idStr paddingNumbers = "";
	paddingNumbers.Append( nodeInfo->first_attribute( "padding" )->value() );
	int j = 0;
	int i = 0;
	value = "";
	for( ; i <= paddingNumbers.Length(); i++ ) {
		if ( paddingNumbers[i] == ',' ) {
			if ( j == 0 ) {
				processStrucutre.paddingT =  value.c_int();
				value = "";
				j++;
			} else if ( j == 1 ) {
				processStrucutre.paddingR = value.c_int();
				value = "";
				j++;
			} else {
				processStrucutre.paddingB = value.c_int();
				value = "";
				j = 0;
			}
		} else if ( i == paddingNumbers.Length() ) {
			processStrucutre.paddingL = value.c_int();
			value = "";
		} else {
			value += paddingNumbers[i];
		}
	}

	//common->Printf( "capture spacing\n" );

	idStr spacingNumbers = "";
	spacingNumbers.Append( nodeInfo->first_attribute( "spacing" )->value() );
	value = "";
	for( i = 0; i <= spacingNumbers.Length(); i++ ) {
		if ( spacingNumbers[i] == ',' ) {
			processStrucutre.spacingVert = value.c_int();
			value = "";
		} else if ( i == spacingNumbers.Length() - 1 ) {
				processStrucutre.spacingHoriz = value.c_int();
				value = "";
		} else {
			value += paddingNumbers[i];
		}
	}

	value = nodeInfo->first_attribute( "outline" )->value();
	processStrucutre.outlineThickness = value.c_int();


	//capture common
	//common->Printf( "capture common\n" );

	value = nodeCommon->first_attribute( "lineHeight" )->value();
	generatedFontStructure.lineHeight = value.c_int();
	value = nodeCommon->first_attribute( "base" )->value();
	generatedFontStructure.fontBase = value.c_int();
	value = nodeCommon->first_attribute( "scaleW" )->value();
	generatedFontStructure.scaleW = value.c_int();
	value = nodeCommon->first_attribute( "scaleH" )->value();
	generatedFontStructure.scaleH = value.c_int();
	value = nodeCommon->first_attribute( "pages" )->value();
	generatedFontStructure.numPages = value.c_int();
	generatedFontStructure.packed = nodeCommon->first_attribute( "packed" )->value() != 0;
	value = nodeCommon->first_attribute( "alphaChnl" )->value();
	generatedFontStructure.alphaChnl = value.c_int();
	value = nodeCommon->first_attribute( "redChnl" )->value();
	generatedFontStructure.redChnl = value.c_int();
	value = nodeCommon->first_attribute( "greenChnl" )->value();
	generatedFontStructure.greenChnl = value.c_int();
	value = nodeCommon->first_attribute( "blueChnl" )->value();
	generatedFontStructure.blueChnl = value.c_int();

	//pages
	//common->Printf( "pages\n" );

	if( pageList.Num() != 0 ) {
		pageList.Clear();
	}

	rapidxml::xml_node<> *nodePage;
	for( int i = 0; i < generatedFontStructure.numPages; i++ ) {
		if( i == 0 ) {
			nodePage = nodePages->first_node("page");
		} else {
			nodePage = nodePages->next_sibling(); //FIXME this might fail with a 'Segmentation fault (core dumped)'
												  //because the "next_sibiling" method never seems to work accordingly
		}
		BMpage BM_page;
		idStr page_id = nodePage->first_attribute( "id" )->value();
		idStr page_file = nodePage->first_attribute( "file" )->value();
		BM_page.Read( page_id.c_int(), sharedStruct.relativeInputDir + page_file );

		pageList.Append( BM_page );
	}

	//glyphs or "chars"
	//common->Printf( "glyphs\n" );

	if( glyphList.Num() != 0 ) {
		glyphList.Clear();
	}

	value = nodeChars->first_attribute( "count" )->value();
	int num_o_glyphs = value.c_int(); 			//ATTENTION: I don't know why it gets an extra integer to the real amount!

	rapidxml::xml_node<> *nodeGlyph = nodeChars->first_node( "char" );

	for( int i = 0; i < num_o_glyphs; i++ ) {	//hence why: i < num_o_glyphs
		BMglyph BM_glyph;
		idStr glyph_id = nodeGlyph->first_attribute( "id" )->value();
		idStr glyph_x = nodeGlyph->first_attribute( "x" )->value();
		idStr glyph_y = nodeGlyph->first_attribute( "y" )->value();
		idStr glyph_width = nodeGlyph->first_attribute( "width" )->value();
		idStr glyph_height = nodeGlyph->first_attribute( "height" )->value();
		idStr glyph_xoffset = nodeGlyph->first_attribute( "xoffset" )->value();
		idStr glyph_yoffset = nodeGlyph->first_attribute( "yoffset" )->value();
		idStr glyph_xadvance = nodeGlyph->first_attribute( "xadvance" )->value();
		idStr glyph_page = nodeGlyph->first_attribute( "page" )->value();
		idStr glyph_chnl = nodeGlyph->first_attribute( "chnl" )->value();

		BM_glyph.Read(	glyph_id.c_int(),
						glyph_x.c_int(),
						glyph_y.c_int(),
						glyph_width.c_int(),
						glyph_height.c_int(),
						glyph_xoffset.c_int(),
						glyph_yoffset.c_int(),
						glyph_xadvance.c_int(),
						glyph_page.c_int(),
						glyph_chnl.c_int()
					 );
		glyphList.Append( BM_glyph );
		nodeChars->next_sibling(); //FIXME does it work or does it error out with a 'Segmentation fault (core dumped)'?
	}

	return true;
}

void BMfont::DeclareContents(void) {
	common->Printf( "\n ------ declaring the stored BM font info ------ \n\n");
	common->Printf( "font named '%s', is a %i sized font\n", processStrucutre.faceName.c_str(), processStrucutre.size );
	common->Printf( "and is a %s, as well as a %s font\n", processStrucutre.bold ? "BOLD" : "non-bold", processStrucutre.italic ? "italic" : "non-italic" );
	common->Printf( "\n");
}

IntermediateGlyph::IntermediateGlyph( BMfont* font, BMglyph glyph ) {
	InterGlyphStructue.id = glyph.getGlyphStructue().id;

	InterGlyphStructue.width = ( byte )glyph.getGlyphStructue().width;
	InterGlyphStructue.height = ( byte )glyph.getGlyphStructue().height;
	InterGlyphStructue.top = ( char )font->getGeneratedFontStructure().fontBase - glyph.getGlyphStructue().yoffset;
	InterGlyphStructue.left = ( char )glyph.getGlyphStructue().xoffset;
	InterGlyphStructue.xSkip = ( byte )glyph.getGlyphStructue().xadvance;

	int number_zero = 0;
	InterGlyphStructue.padding = ( byte )number_zero;
	InterGlyphStructue.s = ( uint16 )glyph.getGlyphStructue().x;
	InterGlyphStructue.t = ( uint16 )glyph.getGlyphStructue().y;
}

//BFGglyph
BFGglyph::BFGglyph() {
	glyphStructue.width = 0;
	glyphStructue.height = 0;
	glyphStructue.top = 0;
	glyphStructue.left = 0;
	glyphStructue.xSkip = 0;
	glyphStructue.s = 0;
	glyphStructue.t = 0;
}


void BFGpage::Load( BMfont* font, int _id ) {
	id = _id;
	for( int i = 0; i < font->getPageList().Num(); i++ ) {
		if ( font->getPageList()[i].getId() == _id ) {
			imageFile = font->getPageList()[i].getImageFile();
		}
	}

}
//BFGfont

BFGfont::BFGfont( sharedStruct_t _sharedStruct ) {
	Clear();
	sharedStruct = _sharedStruct;

	basePath = cvarSystem->GetCVarString( "fs_basepath" );
	basePath += "/";
	basePath.Append( cvarSystem->GetCVarString( "fs_game" ) );
	basePath += "/";
}

BFGfont::~BFGfont() {
	Clear();
}
void BFGfont::Clear() {
	pages.Clear();

	sharedStruct.relativeFilePath = "";
	sharedStruct.relativeInputDir = "";
	sharedStruct.relativeOutputDir = "";

	BFGfileStructure.pointSize = 0;
	BFGfileStructure.ascender = 0;
	BFGfileStructure.descender = 0;
	BFGfileStructure.numGlyphs = 0;
	BFGfileStructure.glyphs.Clear();

	basePath = "";
	dest_global_folder = "";
	dest_relative_file = "";
	dest_global_file = "";
}

void BFGfont::Load( BMfont* font ) {
	int i, j;

	//list the pages and include them in the BFG font
	for ( i = 0; i < font->getPageList().Num(); i++ ) {
		BFGpage* workingPage = new( TAG_FONT ) BFGpage();
		workingPage->Load( font, i );
		pages.Append( workingPage );
	}

	// if we don't have a single page or have more than one fail, for reasons, FIXME, should work for all pages
	assert( ( font->getGeneratedFontStructure().numPages == 1 ) && ( pages.Num() == 1 ) );

	//get page info
	BFGfileStructure.pointSize = 48; // must be 48!
	BFGfileStructure.ascender = (short)font->getGeneratedFontStructure().fontBase;
	BFGfileStructure.descender = (short)( font->getGeneratedFontStructure().fontBase - font->getGeneratedFontStructure().lineHeight );

	int lowestPoint = 0;

	//the BFG code use only the glyphs in the first page, I guess this is because it means using just a single texture per font.
	//so we will have to select just the glyphs that are registered as belonging to the first page,
	//FIXME in the future we might want to use an unrestricted amount of pages?
	for( i = 0; i < font->getGlyphList().Num(); i++ ) {
		BMglyph workingGlyph = font->getGlyphList()[i];
		if ( workingGlyph.getGlyphStructue().page == 0 ) {
			//TODO since there is some information unused by the BFG code we will be using an intermediate in case we use it in the future
			// this can be mae simpler by using here the finalGlyph instead of the intermediate Glyph
			IntermediateGlyph* intermedGlyph = new( TAG_FONT ) IntermediateGlyph( font, workingGlyph );

			int lowestGlyph = workingGlyph.getGlyphStructue().yoffset + intermedGlyph->getInterGlyphStructue().height;
			if ( lowestGlyph > lowestPoint ) {
				lowestPoint = lowestGlyph;
			}
			if ( lowestGlyph > font->getGeneratedFontStructure().lineHeight ) {
				common->Warning( "WARNING: Glyph number '%i' is too high at '%i' for line height at '%i'.\n",
								 workingGlyph.getGlyphStructue().id,
								 lowestGlyph,
								 font->getGeneratedFontStructure().lineHeight
							   );
			}
			//TODO see last comment
			BFGglyph* finalGlyph = new( TAG_FONT ) BFGglyph();
			BFGglyphStructure_t glyphStructue;
			glyphStructue.width = intermedGlyph->getInterGlyphStructue().width;
			glyphStructue.height = intermedGlyph->getInterGlyphStructue().height;
			glyphStructue.top = intermedGlyph->getInterGlyphStructue().top;
			glyphStructue.left = intermedGlyph->getInterGlyphStructue().left;
			glyphStructue.xSkip = intermedGlyph->getInterGlyphStructue().xSkip;
			glyphStructue.s = intermedGlyph->getInterGlyphStructue().s;
			glyphStructue.t = intermedGlyph->getInterGlyphStructue().t;
			finalGlyph->setGlyphStructue( glyphStructue );
			BFGfileStructure.glyphs.Append( finalGlyph );
			BFGfileStructure.glyphsIds.Append( intermedGlyph->getInterGlyphStructue().id );
		}
	}

	BFGfileStructure.numGlyphs = ( short )BFGfileStructure.glyphs.Num();

	if ( lowestPoint != font->getGeneratedFontStructure().lineHeight ) {
		common->Warning( "WARNING: Line height '%i' is not what I thought it would be '%i'.\n"
						 "         BMFont's settings used to generate source font might be wrong.\n"
						 "         Also descender might be wrong: '%i' instead of '%i'.\n",
						 font->getGeneratedFontStructure().lineHeight,
						 lowestPoint,
						 BFGfileStructure.descender,
						 font->getGeneratedFontStructure().fontBase - lowestPoint
					   );
	}
}

void BFGfont::CreateFolders() {
	dest_global_folder = basePath + sharedStruct.relativeOutputDir;
	dest_relative_file = sharedStruct.relativeOutputDir + BFGfileStructure.pointSize + ".dat";
	dest_global_file = basePath + dest_relative_file;

	//debug
	//common->Printf( "folder name is '%s', which means '%s', and filename is '%s'.\n", sharedStruct.relativeOutputDir.c_str(), dest_global_folder.c_str(), dest_relative_file.c_str() );


	if( fileSystem->IsFolder( sharedStruct.relativeOutputDir.c_str() ) == FOLDER_NO ) {
		common->Error( "there is already a file with the same name as the requested folder name in '//newfonts/'!\n" );
	}

	if ( fileSystem->IsFolder( sharedStruct.relativeOutputDir.c_str() ) == FOLDER_ERROR ) {
		idStr working_dir = sharedStruct.relativeOutputDir;
		working_dir.StripLeading( "newfonts/");
		working_dir.StripTrailing( "/" );
		common->Printf( "a new folder '%s' has been created in '/newfonts/'.\n", working_dir.c_str() );
	} else if ( fileSystem->IsFolder( sharedStruct.relativeOutputDir.c_str() ) == FOLDER_YES ) {
		common->Printf( "deleting folder '%s' first in order to recreate it later.\n", sharedStruct.relativeOutputDir.c_str() );
		fileSystem->RemoveDir( sharedStruct.relativeOutputDir.c_str() ); //FIXME: does this erase the included files within the folder?
	}
	fileSystem->CreateOSPath( dest_global_folder.c_str() );
}

void BFGfont::Save() {

	//fonts all have the same filename: "48.dat" a reference to the "size" of the font.
	//but all different fonts are separated in folders bearing their name inside the "newfonts" folder
	//so the font "futura" sould be in: /{'base' folder}/{'game' Folder}/newfonts/futura/48.dat

	int i;

	// the 48.dat file
	if ( fileSystem->FindFile( dest_global_file ) == FIND_YES ) {
		fileSystem->RemoveFile( dest_global_file );
	}

	idFile* outputFile = fileSystem->OpenFileWrite( dest_global_file, "fs_basepath" );
	/*if( outputFile == NULL ) {
		common->Printf( "BFGfont: the file named '%s' is empty!\n", dest_relative_file.c_str() );
	}*/

	static const int FONT_INFO_VERSION = 42;
	const int FONT_INFO_MAGIC = ( FONT_INFO_VERSION | ( 'i' << 24 ) | ( 'd' << 16 ) | ( 'f' << 8 ) );

	outputFile->WriteBig( FONT_INFO_MAGIC );
	outputFile->WriteBig( BFGfileStructure.pointSize );
	outputFile->WriteBig( BFGfileStructure.ascender );
	outputFile->WriteBig( BFGfileStructure.descender );
	outputFile->WriteBig( BFGfileStructure.numGlyphs );

	for( i = 0; i < BFGfileStructure.glyphs.Num(); i++ ) {
		outputFile->WriteUnsignedChar( BFGfileStructure.glyphs[i]->getGlyphStructue().width );
		outputFile->WriteUnsignedChar( BFGfileStructure.glyphs[i]->getGlyphStructue().height );
		outputFile->WriteChar( BFGfileStructure.glyphs[i]->getGlyphStructue().top );
		outputFile->WriteChar( BFGfileStructure.glyphs[i]->getGlyphStructue().left );
		outputFile->WriteUnsignedChar( BFGfileStructure.glyphs[i]->getGlyphStructue().xSkip );
		outputFile->WriteUnsignedShort( BFGfileStructure.glyphs[i]->getGlyphStructue().s );
		outputFile->WriteUnsignedShort( BFGfileStructure.glyphs[i]->getGlyphStructue().t );
	}

	for( i = 0; i < BFGfileStructure.glyphsIds.Num(); i++ ) {
		outputFile->WriteInt( BFGfileStructure.glyphsIds[i] );
	}
	common->Printf( "BMfont: done writing the %i.dat file!\n", BFGfileStructure.pointSize );
	delete outputFile;
}

void BFGfont::CopyPageFiles( void ) {
	for( int i = 0; i < pages.Num(); i++) {
		idStr pageImage = pages[i]->getImageFile();

		idStr orig_global_pageImage = basePath + sharedStruct.relativeInputDir + pageImage.StripPath();
		idStr dest_global_pageImage = basePath + sharedStruct.relativeOutputDir + pageImage.StripPath();

		if ( fileSystem->FindFile( dest_global_pageImage ) == FIND_YES ) {
			fileSystem->RemoveFile( dest_global_pageImage );
		}
		//debug
		//common->Printf( "search path in origin: '%s', and in destine: '%s'.\n", orig_global_pageImage.c_str(), dest_global_pageImage.c_str() );

		fileSystem->CopyFile( orig_global_pageImage.c_str(), dest_global_pageImage.c_str() );
	}

}


} /* namespace BFG */
