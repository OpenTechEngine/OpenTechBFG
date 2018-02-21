/*
 * BMfont.h
 *
 *  Created on: 3 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#ifndef NEO_TOOLS_COMPILERS_FONTCODEC_FONTMETHODS_H_
#define NEO_TOOLS_COMPILERS_FONTCODEC_FONTMETHODS_H_

#include "../idlib/Str.h"
#include "../idlib/containers/List.h"

namespace BFG {
/*
 * These are classes represent fonts generated by BMFont
 */

typedef struct
{
    int 	id;        	// char utf32
    int 	x;         	// x position in image (in pixels)
    int 	y;         	// y position in image (in pixels)
    int 	width;    	// width in image (in pixels)
    int 	height;    	// height in image (in pixels)
    int 	xoffset;   	// offset from pen position to start of glyph (in pixels)
    int 	yoffset;  	// offset from top of the line to start of glyph (in pixels)
    int 	xadvance;	// how much to move pen after drawing glyph (in pixels)
    int 	page;      	// image number
    int 	chnl;      	// channel mask in the image (0xF == all channels) (important when chars are packed)
} BMglyphStructure_t;

// information about how the font was generated
typedef struct
{
	idStr 	faceName;
	int		size;		// font size in points
	bool 	bold;
  	bool 	italic;
  	idStr	charset;
	bool	unicode;    // true if unicode (charset is empty then)
	int 	heightStretchPercent;
	bool 	fontSmoothing;
 	int 	antiAliasLevel;
 	int 	paddingT;
  	int 	paddingR;
  	int 	paddingB;
   	int 	paddingL;
  	int 	spacingHoriz;
   	int 	spacingVert;
  	int 	outlineThickness;
} BMprocessfontStructure_t;

// information about the generated font
typedef struct
{
	int 	lineHeight;	// line height
	int		fontBase;	// dist from top to baseline
	int		scaleW;  	// width of the picture
	int 	scaleH;  	// height of the picture
	int 	numPages;	// numeber of pictures
	bool 	packed;     // true if glyphs are packed into multiple channels
	int		alphaChnl;	// contents of alpha channel: 0 - glyph, 1 - outline, 2 - encoded glyph & outline, 3 - zero, 4 - one
	int		redChnl;  	// same
	int		greenChnl; 	// same
	int 	blueChnl;  	// same
} BMgeneratedfontStructure_t;

class BMglyph {
public:
	BMglyph();
	void Read(int _id, int _x, int _y, int _width, int _height, int _xoffset, int _yoffset, int _xadvance, int _page, int _chnl);

	const BMglyphStructure_t& getGlyphStructue() const {
		return glyphStructue;
	}

private:
	void		Clear();
	BMglyphStructure_t glyphStructue;
};

class BMpage {
public:
	BMpage();

	void Read(int id_num, idStr image_file, idStr fnt_file);

	int getId() const {
		return id;
	}

	const idStr& getImageFile() const {
		return qPath_ImageFile;
	}

private:
	int id;
    idStr qPath_ImageFile;

};

class BMfont {
public:
	BMfont( idStr inputFile );
	virtual ~BMfont();

	bool Read();

	const BMgeneratedfontStructure_t& getGeneratedFontStructure() const {
		return generatedFontStructure;
	}

	void setGeneratedFontStructure(
			const BMgeneratedfontStructure_t& generatedFontStructure) {
		this->generatedFontStructure = generatedFontStructure;
	}

	const BMprocessfontStructure_t& getProcessStrucutre() const {
		return processStrucutre;
	}

	void setProcessStrucutre(const BMprocessfontStructure_t& processStrucutre) {
		this->processStrucutre = processStrucutre;
	}

	const idStr& getFontName() const {
		return fontName;
	}
	/*
	void setFontName(const idStr& fontName) {
		this->fontName = fontName;
	}
	*/

private:
	void						Clear();
	idStr 						fntFile;
	idStr						fontName;
	idList<BMglyph> 			glyphList;
	idList<BMpage> 				pageList;
	BMprocessfontStructure_t	processStrucutre;
	BMgeneratedfontStructure_t 	generatedFontStructure;
};


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
	//ushort 	s;        	// x offset in image where glyph starts (in pixels)
	//ushort 	t;        	// y offset in image where glyph starts (in pixels)
	short 	s;        	// x offset in image where glyph starts (in pixels)
	short 	t;        	// y offset in image where glyph starts (in pixels)
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

	void 	Read( idStr fileName );
	void 	Write( BMfont font );

	const idStr& getFontName() const {
		return fontName;
	}
	/*
	void setFontName(const idStr& fontName) {
		this->fontName = fontName;
	}
	*/
private:
	idList<BFGglyph> 			glyphs;
	idStr						fontName;
	short						pointSize;
	short						ascender;
	short						descender;
};

} /* namespace BFG */

#endif /* NEO_TOOLS_COMPILERS_FONTCODEC_FONTMETHODS_H_ */
