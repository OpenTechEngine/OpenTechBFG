/*
 * ceguiConsole.h
 *
 *  Created on: Sep 5, 2014
 *      Author: kordex
 */

#ifndef CEGUICONSOLE_H_
#define CEGUICONSOLE_H_

#include "framework/Console.h"

namespace CEGUIConsole {

class Console: public virtual BFG::idConsole {
public:
	Console();
	virtual ~Console();

	// the system code can release the mouse pointer when the console is active
	bool	Active();

	// force console open
	void	Open();

	// some console commands, like timeDemo, will force the console closed before they start
	void	Close();

	void	Print( const char* text );

	// process console event, like toggle show hide, and other keys
	bool	ProcessEvent( const BFG::sysEvent_t* event, bool forceAccept );


	// unimplemented

	void	Init() { };
	void	Shutdown() { };
	// clear the timers on any recent prints that are displayed in the notify lines
	void	ClearNotifyLines() { };
	void	Draw( bool forceFullScreen ) { };
	void	PrintOverlay( BFG::idOverlayHandle& handle, BFG::justify_t justify, VERIFY_FORMAT_STRING const char* text, ... ) { };
	BFG::idDebugGraph* 	CreateGraph( int numItems ) { return NULL; }; // TODO implement
	void			DestroyGraph( BFG::idDebugGraph* graph )  { }; // TODO implement

private:
	bool isInitialized();

	void TabComplete(void);

	struct ConsoleVars;
	ConsoleVars *ourVars;
};

} /* namespace CEGUIConsole */

#endif /* CEGUICONSOLE_H_ */
