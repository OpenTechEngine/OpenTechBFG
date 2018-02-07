/*
 * blFontCodec.h
 *
 *  Created on: 4 de febr. 2018
 *      Author: Biel Bestué de Luna
 *
 *      this file is GPLv3
 */

#ifndef NEO_TOOLS_COMPILERS_FONTCODEC_BLFONTCODEC_H_
#define NEO_TOOLS_COMPILERS_FONTCODEC_BLFONTCODEC_H_

#include "../idlib/Str.h"
#include "../idlib/containers/List.h"
#include "../framework/Common.h"

#include "../tools/compilers/fontcodec/BMfont.h"
#include "../tools/compilers/fontcodec/BFGfont.h"

namespace BFG {

typedef struct
{
	bool	verbose;
	bool	decompile;
	idStr	inputFilename;
	idStr	outputFilename;
	idStr	inputDirectory;
} fontCodecGlobals_t;

class blFontCodec {
public:
	blFontCodec();
	virtual ~blFontCodec();

	void 		FontCompHelp();
	void 		FontCodec( const idCmdArgs& args );

	const fontCodecGlobals_t& getfontCodecGlobals() const {
		return fontCodecGlobals;
	}

private:
	void				clear();
	BMfont 				BM_font;
	BFGfont 			BFG_font;
	fontCodecGlobals_t	fontCodecGlobals;
	idStr 		GatherComandArgs( const idCmdArgs& args );
};

} /* namespace BFG */

#endif /* NEO_TOOLS_COMPILERS_FONTCODEC_BLFONTCODEC_H_ */
