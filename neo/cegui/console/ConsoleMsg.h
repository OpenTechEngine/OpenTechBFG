/*
 * CEGUIConsoleMsg.h
 *
 *  Created on: Dec 17, 2014
 *      Author: kordex
 */

#ifndef CEGUICONSOLEMSG_H_
#define CEGUICONSOLEMSG_H_

#include "../idlib/Str.h"
#include "../wrap_cegui.h"

namespace CEGUIConsole
{

class ConsoleMsg
{
public:
	ConsoleMsg( const CEGUI::String inMsg );
	virtual ~ConsoleMsg();
	
	ConsoleMsg& operator=( const ConsoleMsg& rhs )
	{
		return *this;
	}
	
	CEGUI::String msg;
	
private:
	const CEGUI::String Convert( const CEGUI::String convertString );
};


} /* namespace CEGUIConsole */

#endif /* CEGUICONSOLEMSG_H_ */
