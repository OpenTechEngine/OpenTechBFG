/*
 * BMfont.cpp
 *
 *  Created on: 3 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

//#include <rapidxml>
#include "FontMethods.h"

#include "../../libs/rapidxml/rapidxml-1.13/rapidxml.hpp"
#include "../../libs/rapidxml/rapidxml-1.13/rapidxml_utils.hpp"

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

void BMpage::Read(int id_num, idStr image_file, idStr fnt_file) {
	id = id_num;
	fnt_file.ExtractFilePath( qPath_ImageFile );
	qPath_ImageFile += image_file;
}

/*
 * fonts
 */

BMfont::BMfont( idStr inputFile ) {
	Clear();
	fntFile = inputFile;
}

BMfont::~BMfont() {
	// TODO Auto-generated destructor stub
	Clear();
}

void BMfont::Clear() {
	fntFile = "";
	glyphList.Clear();
	pageList.Clear();

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

	if( fntFile == "\0" ) {
		common->Error( "BMfont: file is empty!\n" );
	}

	rapidxml::file<> xmlFile(fntFile);
	rapidxml::xml_document<> doc;
	doc.parse<0>( xmlFile.data() );
	rapidxml::xml_node<> *font = doc.first_node("font");
	rapidxml::xml_node<> *info = font->next_sibling("info");
	rapidxml::xml_node<> *common = font->next_sibling("common");
	rapidxml::xml_node<> *pages = font->next_sibling("pages");
	rapidxml::xml_node<> *chars = font->next_sibling("chars");

	//capture info
	processStrucutre.faceName = info->first_attribute( "face" )->value();
	processStrucutre.size =  static_cast<int>( * info->first_attribute( "size" )->value() );
	processStrucutre.bold = *info->first_attribute( "bold" )->value() == true;
	processStrucutre.italic = *info->first_attribute( "italic" )->value() == true;
	//processStrucutre.charset =
	processStrucutre.unicode = *info->first_attribute( "unicode" )->value() == true;
	processStrucutre.heightStretchPercent = static_cast<int>( * info->first_attribute( "stretchH" )->value() );
	processStrucutre.fontSmoothing = *info->first_attribute( "smooth" )->value() == true;
	processStrucutre.antiAliasLevel = static_cast<int>( * info->first_attribute( "aa" )->value() );

	idStr value = "";
	idStr paddingNumbers = info->first_attribute( "padding" )->value();
	for( int i, j = 0; i <= paddingNumbers.Length(); i++ ) {
		if ( &paddingNumbers[i] == "," ) {
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
			value = value + paddingNumbers[i];
		}
	}

	idStr SpacingNumbers = info->first_attribute( "spacing" )->value();
	for( int i = 0; i <= SpacingNumbers.Length(); i++ ) {
		if ( &SpacingNumbers[i] == "," ) {
			processStrucutre.spacingVert = value.c_int();
			value = "";
		} else if ( i == SpacingNumbers.Length() - 1 ) {
				/*value = value +*/
				processStrucutre.spacingHoriz = value.c_int();
				value = "";
		} else {
			value = value + SpacingNumbers[i];
		}
	}
	value = info->first_attribute( "outline" )->value();
	processStrucutre.outlineThickness = value.c_int();

	fontName = processStrucutre.faceName;

	//capture common
	value = info->first_attribute( "lineHeight" )->value();
	generatedFontStructure.lineHeight = value.c_int();
	value = info->first_attribute( "base" )->value();
	generatedFontStructure.fontBase = value.c_int();
	value = info->first_attribute( "scaleW" )->value();
	generatedFontStructure.scaleW = value.c_int();
	value = info->first_attribute( "scaleH" )->value();
	generatedFontStructure.scaleH = value.c_int();
	value = info->first_attribute( "pages" )->value();
	generatedFontStructure.numPages = value.c_int();
	generatedFontStructure.packed = common->first_attribute( "packed" )->value() != 0;
	value = info->first_attribute( "alphaChnl" )->value();
	generatedFontStructure.alphaChnl = value.c_int();
	value = info->first_attribute( "redChnl" )->value();
	generatedFontStructure.redChnl = value.c_int();
	value = info->first_attribute( "greenChnl" )->value();
	generatedFontStructure.greenChnl = value.c_int();
	value = info->first_attribute( "blueChnl" )->value();
	generatedFontStructure.blueChnl = value.c_int();

	//pages
	if( pageList.Num() != 0 ) {
		pageList.Clear();
	}

	rapidxml::xml_node<> *page;
	for( int i = 0; i < generatedFontStructure.numPages; i++ ) {
		if( i == 0 ) {
			page = pages->next_sibling("page");
		} else {
			page = pages->next_sibling();
		}
		BMpage BM_page;
		idStr page_id = page->first_attribute( "id" )->value();
		idStr page_file = page->first_attribute( "file" )->value();
		BM_page.Read( page_id.c_int(), page_file, fntFile );

		pageList.Append( BM_page );
	}

	//glyphs
	if( glyphList.Num() != 0 ) {
		glyphList.Clear();
	}

	value = chars->first_attribute( "count" )->value();
	int num_o_glyphs = value.c_int(); 	//ATTENTION: I don't know why it gets an extra integer to the real amount!

	for( int i = 0; i > num_o_glyphs; i++ ) { 								//hence why: i < num_o_glyphs
		rapidxml::xml_node<> *glyph = chars->next_sibling();
		BMglyph BM_glyph;
		idStr glyph_id = glyph->first_attribute( "id" )->value();
		idStr glyph_x = glyph->first_attribute( "x" )->value();
		idStr glyph_y = glyph->first_attribute( "y" )->value();
		idStr glyph_width = glyph->first_attribute( "width" )->value();
		idStr glyph_height = glyph->first_attribute( "height" )->value();
		idStr glyph_xoffset = glyph->first_attribute( "xoffset" )->value();
		idStr glyph_yoffset = glyph->first_attribute( "yoffset" )->value();
		idStr glyph_xadvance = glyph->first_attribute( "xadvance" )->value();
		idStr glyph_page = glyph->first_attribute( "page" )->value();
		idStr glyph_chnl = glyph->first_attribute( "chnl" )->value();

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
	}

	DeclareContents();

	return true;
}

void BMfont::DeclareContents(void) {
	common->Printf( "\n ------ declaring the stored info ------ \n\n");
	common->Printf( "font name: %s a %i sized font\n", processStrucutre.faceName, processStrucutre.size );
	common->Printf( "is a %s and a %s font\n", processStrucutre.bold ? "BOLD" : "non-bold", processStrucutre.italic ? "italic" : "non-italic" );
}

//BFGfont

BFGfont::BFGfont() {
	// TODO Auto-generated constructor stub
	glyphs.Clear();
	pointSize = 0;
	ascender = 0;
	descender = 0;
	internalFontFile = NULL;
}

BFGfont::~BFGfont() {
	// TODO Auto-generated destructor stub
}

void BFGfont::Write(BMfont font) {

	// if we don't have a single page or have more than one fail
	assert( font.getGeneratedFontStructure().numPages == 1 );

	//get page info
	pointSize = 48; // must be 48!
	ascender = (short)font.getGeneratedFontStructure().fontBase;
	descender = (short)( font.getGeneratedFontStructure().fontBase - font.getGeneratedFontStructure().lineHeight );

	//fonts all have the same filename: "48.dat" a reference to the "size" of the font.
	//but all different fonts are separated in folders bearing their name inside the "newfonts" folder
	//so the font "futura" sould be in: //{game_Folder}/newfonts/futura/48.dat

	//order of the buffer

	//create file
	if ( internalFontFile == NULL ) {
		internalFontFile = new( TAG_FONT ) idFile_Memory( "48.dat" );
	} else {
		/* TODO erase file contents an overwrite with the new data */
		internalFontFile->Rewind();
		internalFontFile->Flush();
	}
/*
        public void Save(string fileName)
        {
            FileStream fs = File.Create(fileName);
            BinaryWriter bw = new BinaryWriter(fs);

            const int FONT_INFO_VERSION = 42;
            //const int FONT_INFO_MAGIC = (FONT_INFO_VERSION | ('i' << 24) | ('d' << 16) | ('f' << 8));

            ASCIIEncoding asen = new ASCIIEncoding();
            byte[] ascii = asen.GetBytes("idf1");
            ascii[3] = FONT_INFO_VERSION;
            bw.Write(ascii);

            bw.WriteBig(pointSize);
            bw.WriteBig(ascender);
            bw.WriteBig(descender);

            short numGlyphs = (short)glyphs.Count();
            bw.WriteBig(numGlyphs);

            foreach (var glyph in glyphs)
            {
                bw.Write(glyph.width);
                bw.Write(glyph.height);
                bw.Write(glyph.top);
                bw.Write(glyph.left);
                bw.Write(glyph.xSkip);
                byte padding = 0;
                bw.Write(padding);
                bw.Write(glyph.s);
                bw.Write(glyph.t);
            }

            foreach (var glyph in glyphs)
            {
                bw.Write(glyph.id);
            }

            bw.Close();
            fs.Close();
        }
    }
*/


}

} /* namespace BFG */




