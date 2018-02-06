/*
 * BMfont.cpp
 *
 *  Created on: 3 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#include "../tools/compilers/fontcodec/BMfont.h"
#include "../framework/Common.h"

namespace BFG {


/*
 * glyphs
 */

BMglyph::BMglyph() {
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
	idStr pattern = "char\s+id=(\d+)\s+x=(\d+)\s+y=(\d+)\s+width=(\d+)\s+height=(\d+)\s+xoffset=([+\-\d]+)\s+yoffset=([+\-\d]+)\s+xadvance=([+\-\d]+)\s+page=(\d+)\s+chnl=([+\-\d]+)";
	Regex rexex = new Regex( pattern );
}

/*
 * pages
 */

BMpage::BMpage() {
	//TODO stub
}

bool BMpage::Load(idStr line) {
}

/*
 * fonts
 */

BMfont::BMfont( idStr file ) {

	if( file == "\0" ) {
		common->Error( "BMfont: file is empty!\n" );
	}

	fntFile = file;

	fntFile.BackSlashesToSlashes();
	if( fntFile.Icmpn( "fonts/", 5 ) != 0 ) {
		fntFile = "fonts/" + fntFile;
	}

	rapidxml::file<> xmlFile(fntFile); // Default template is char
	rapidxml::xml_document<> doc;
	doc.parse<0>( xmlFile.data() );
}

BMfont::~BMfont() {
	// TODO Auto-generated destructor stub
}

bool BMfont::LoadInfo(idStr line) {
}

bool BMfont::LoadCommon(idStr line) {
}

void BMfont::Load(idStr fileName) {
}

} /* namespace BFG */




