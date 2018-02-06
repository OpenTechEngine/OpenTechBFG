/*
 * BFGfont.h
 *
 *  Created on: 3 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#ifndef NEO_TOOLS_COMPILERS_FONTCODEC_BFGFONT_H_
#define NEO_TOOLS_COMPILERS_FONTCODEC_BFGFONT_H_

#include "../idlib/Str.h"
#include "FontTool.cxx"

namespace BFG {

/*
 * Here we have idTech .dat font file.
 * Only fonts with one page are supported.
 */

typedef struct
{
	int 	id;			// UTF32 - stored separately
	byte 	width;      // width of glyph in pixels
	byte 	height;     // height of glyph in pixels
	byte 	top;        // distance in pixels from the base line to the top of the glyph
	byte 	left;       // distance in pixels from the pen to the left edge of the glyph
	byte 	xSkip;      // x adjustment after rendering this glyph
	ushort 	s;        	// x offset in image where glyph starts (in pixels)
	ushort 	t;        	// y offset in image where glyph starts (in pixels)
} BFGglyphStructure_t;

class BFGglyph {
public:
	BFGglyph();

	void 	Compile( idStr fileName );
	void 	Decompile( BMglyph glyph, BMfont font );

	const BFGglyphStructure_t& getGlyphStructue() const {
		return glyphStructue;
	}

	void 	setGlyphStructue(const BFGglyphStructure_t& glyphStructue) {
		this->glyphStructue = glyphStructue;
	}

private:
	BFGglyphStructure_t glyphStructue;

};

class BFGfont {
public:
	BFGfont();
	virtual ~BFGfont();

	void 	Compile( idStr fileName );
	void 	Decompile( BMfont font );

private:
	idList<BFGglyph> 	glyphs;
	short				pointSize = 48; // must be 48!
	short				ascender;
	short				descender;


};

} /* namespace BFG */

#endif /* NEO_TOOLS_COMPILERS_FONTCODEC_BFGFONT_H_ */
