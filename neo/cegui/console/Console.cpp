/*
 * Console.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: kordex
 */


#include "Console.h"

#include "ConsoleImpl.h"
#include "ConsoleQueue.h"
#include "ConsoleMsg.h"

namespace CEGUIConsole {

struct Console::ConsoleVars {
	ConsoleImpl *consoleInstance;
	ConsoleQueue msgQueue;
};

Console::Console()
: ourVars(new ConsoleVars)
{
	ourVars->consoleInstance = NULL;
}

Console::~Console() {
}

bool Console::isInitialized() {
	// checks if cegui is up and running
	if (CEGUI::System::getSingletonPtr() != NULL) {
		if (ourVars->consoleInstance == NULL)
		{
			// initializes the console singleton
			ourVars->consoleInstance = &ConsoleImpl::getInstance();
		}
		return true;
	}
	else
		return false;
}

bool Console::Active()
{
	if (isInitialized())
		return ourVars->consoleInstance->isVisible();
	else
		return false;
}

void Console::Open()
{
	if (isInitialized()) {
		ourVars->consoleInstance->setVisible(true);
	}
}

void Console::Close()
{
	if (isInitialized()) {
		ourVars->consoleInstance->setVisible(false);
	}
}

void Console::TabComplete(void)
{
	if (isInitialized()) {
		ourVars->consoleInstance->TabComplete();
	}
}

void Console::Print(const char * text)
{

	ourVars->msgQueue.push(ConsoleMsg(text));
	if (isInitialized())
	{
		while (!ourVars->msgQueue.empty()) {
			ConsoleMsg outMsg = ourVars->msgQueue.pop();
			ourVars->consoleInstance->OutputText(outMsg);
		}
	}
}

bool Console::ProcessEvent( const BFG::sysEvent_t* event, bool forceAccept )
{
	if (isInitialized()) {
		const bool consoleKey = event->evType == BFG::SE_KEY && event->evValue == BFG::K_GRAVE && BFG::com_allowConsole.GetBool();

		const bool tabKey = event->evType == BFG::SE_KEY && event->evValue == BFG::K_TAB;

		// we always catch the console key event
		if( !forceAccept && consoleKey )
		{
			// ignore up events
			if( event->evValue2 == 0 )
			{
				return true;
			}

			// if window is Active we close it with consoleKey
			if( Active() )
			{
				Close();
				BFG::Sys_GrabMouseCursor( true );
			}
			else
			{
				Open();
				BFG::Sys_GrabMouseCursor( false );
			}
			return true;
		}

		// return event as processed when console open
		// aka don't pass the input further
		if( Active() )
		{
			if(tabKey) {
				TabComplete();
			}
			return true;
		}

		// if we aren't Active, dump all the other events
		if( !forceAccept && !Active() )
		{
			return false;
		}

		if (forceAccept)
		{
			// a dummy here
			return true;
		}

		// we don't handle things like mouse, joystick, and network packets
		return false;
	}
	return false;
}
} /* namespace CEGUIConsole */

static CEGUIConsole::Console localConsole;
BFG::idConsole* BFG::console = &localConsole;
