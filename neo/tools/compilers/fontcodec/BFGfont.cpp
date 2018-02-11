/*
 * BFGfont.cpp
 *
 *  Created on: 3 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#include "BFGfont.h"

namespace BFG {

BFGfont::BFGfont() {
	// TODO Auto-generated constructor stub
	codec = NULL;
	glyphs.Clear();
	pointSize = 48; // must be 48!
	ascender = 0;
	descender = 0;
}

BFGfont::~BFGfont() {
	// TODO Auto-generated destructor stub
}

} /* namespace BFG */
