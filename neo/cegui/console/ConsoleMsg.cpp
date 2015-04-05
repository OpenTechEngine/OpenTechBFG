/*
 * CEGUIConsoleMsg.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: kordex
 */

#include "ConsoleMsg.h"

#include "../idlib/Str.h"

namespace CEGUIConsole
{

ConsoleMsg::ConsoleMsg( const CEGUI::String inMsg ) :
	msg( Convert( inMsg ) )
{
	//msg = Convert(inMsg);
}

ConsoleMsg::~ConsoleMsg()
{
	// TODO Auto-generated destructor stub
}

const CEGUI::String ConsoleMsg::Convert( const CEGUI::String convertString )
{

	// see http://cegui.org.uk/wiki/Formatting_Tags_in_CEGUI
	
	// I personally like working with std::string. So i'm going to convert it here.
	std::string inString = convertString.c_str();
	
	if( inString.length() >= 1 ) // Be sure we got a string longer than 0
	{
		std::string::size_type caretLoc = 0;
		
		// find first carret in string if exists
		
		// find all carets in the string
		while( caretLoc != std::string::npos )
		{
			int escapeFlag = 0;
			
			caretLoc = inString.find( '^', caretLoc );
			
			if( caretLoc != std::string::npos )
			{
			
				if( escapeFlag == 0 )
				{
					// removing the caret
					inString.erase( caretLoc, 1 );
					// next character on the string is the color code
					char colorCand = inString.at( caretLoc );
					
					switch( colorCand )
					{
					
						case '1':	// C_COLOR_RED
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FFFF0000']" );
							break;
						case '2':	// C_COLOR_GREEN
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FF00FF00']" );
							break;
						case '3':	// C_COLOR_YELLOW
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FFFFFF00']" );
							break;
						case '4':	// C_COLOR_BLUE
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FF0000FF']" );
							break;
						case '5':	// C_COLOR_CYAN
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FF33CCCC']" );
							break;
						case '6':	// C_COLOR_ORANGE
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FFFF6600']" );
							break;
						case '7':	// C_COLOR_WHITE
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FFFFFFFF']" );
							break;
						case '8':	// C_COLOR_GRAY
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FF808080']" );
							break;
						case '9':	// C_COLOR_BLACK
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FF000000']" );
							break;
						case '^': // Escaped caret
							escapeFlag = 1;
							break;
						case '0': // C_COLOR_DEFAULT
						default: // C_COLOR_DEFAULT
							inString.erase( caretLoc, 1 );
							inString.insert( caretLoc, "[colour='FF33CCCC']" );
							break;
					}
				}
				else
				{
					escapeFlag = 0;
				}
			}
		}
	}
	return inString;
	
}

} /* namespace CEGUIConsole */
