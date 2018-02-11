/*
 * BMfont.cpp
 *
 *  Created on: 3 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

//#include <rapidxml>
#include "../../libs/rapidxml/rapidxml-1.13/rapidxml.hpp"
#include "../../libs/rapidxml/rapidxml-1.13/rapidxml_utils.hpp"

#include "../tools/compilers/fontcodec/BMfont.h"
#include "../framework/Common.h"

namespace BFG {


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

void BMglyph::Load(idStr glyphLine) {
	/*
	idStr pattern = "char\s+id=(\d+)\s+x=(\d+)\s+y=(\d+)\s+width=(\d+)\s+height=(\d+)\s+xoffset=([+\-\d]+)\s+yoffset=([+\-\d]+)\s+xadvance=([+\-\d]+)\s+page=(\d+)\s+chnl=([+\-\d]+)";
	Regex rexex = new Regex( pattern );
	*/
}

/*
 * pages
 */

BMpage::BMpage() {
	id = 0;
	file = "";
}

bool BMpage::Load(idStr line) {
	//TODO stub
	return true;
}

/*
 * fonts
 */

BMfont::BMfont() {
	Clear();
}

BMfont::~BMfont() {
	// TODO Auto-generated destructor stub
	Clear();
}

void BMfont::Clear() {
	fntFile = "";
	glyphs.Clear();
	pages.Clear();
	codec = NULL;

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

void BMfont::GatherCodec( blFontCodec * _codec ) {
	codec = _codec;
}

bool BMfont::LoadInfo(idStr line) {
	return true;//stub TODO
}

bool BMfont::LoadCommon(idStr line) {
	return true;//stub TODO
}

bool BMfont::Load(void) {
	fntFile = codec->getfontCodecGlobals().inputFilename;

	if( fntFile == "\0" ) {
		common->Error( "BMfont: file is empty!\n" );
	}
	/*
	rapidxml::file<> xmlFile(fntFile); // Default template is char
	rapidxml::xml_document<> doc;
	doc.parse<0>( xmlFile.data() );
	*/
	return true;//stub TODO
}

} /* namespace BFG */




