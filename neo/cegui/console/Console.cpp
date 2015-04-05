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
#include "cegui/CEGUI_Hooks.h" // for initialization check

namespace CEGUIConsole
{

struct Console::ConsoleVars
{
	ConsoleImpl* consoleInstance;
	ConsoleQueue msgQueue;
};

Console::Console()
	: ourVars( new ConsoleVars )
{
	ourVars->consoleInstance = NULL;
}

Console::~Console()
{

}

bool Console::isInitialized()
{
	if( idCEGUI::IsInitialized() )
	{
		// checks if ceguiPart of the console is up and running
		// all functionality except messages buffered are disabled
		// until cegui part is up and running
		if( ourVars->consoleInstance != NULL )
			return true;
	}
	return false;
}

void Console::Init()
{
	// this is called first from BFG code and then again once cegui is up from startup
	if( idCEGUI::IsInitialized() )
	{
		ourVars->consoleInstance = new ConsoleImpl;
	}
}

void Console::Shutdown()
{
	// this is called first from idCEGUI shutdown and then again from BFG code
	if( idCEGUI::IsInitialized() )
	{
		delete ourVars->consoleInstance;
		ourVars->consoleInstance = NULL;
	}
}

bool Console::Active()
{
	if( isInitialized() )
		return ourVars->consoleInstance->isVisible();
	else
		return false;
}

void Console::Open()
{
	if( isInitialized() )
	{
		ourVars->consoleInstance->setVisible( true );
	}
}

void Console::Close()
{
	if( isInitialized() )
	{
		ourVars->consoleInstance->setVisible( false );
	}
}

void Console::TabComplete( void )
{
	if( isInitialized() )
	{
		ourVars->consoleInstance->TabComplete();
	}
}

void Console::Print( const char* text )
{

	ourVars->msgQueue.push( ConsoleMsg( text ) );
	if( isInitialized() )
	{
		while( !ourVars->msgQueue.empty() )
		{
			ConsoleMsg outMsg = ourVars->msgQueue.pop();
			ourVars->consoleInstance->OutputText( outMsg );
		}
	}
}

bool Console::ProcessEvent( const sysEvent_t* event, bool forceAccept )
{
	if( isInitialized() )
	{
		const bool consoleKey = event->evType == SE_KEY && event->evValue == K_GRAVE && com_allowConsole.GetBool();
		
		const bool tabKey = event->evType == SE_KEY && event->evValue == K_TAB;
		
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
				Sys_GrabMouseCursor( true );
			}
			else
			{
				Open();
				Sys_GrabMouseCursor( false );
			}
			return true;
		}
		
		// return event as processed when console open
		// aka don't pass the input further
		if( Active() )
		{
			if( tabKey )
			{
				// ignore up events
				if( event->evValue2 == 0 )
				{
					return true;
				}
				TabComplete();
			}
			return true;
		}
		
		// if we aren't Active, dump all the other events
		if( !forceAccept && !Active() )
		{
			return false;
		}
		
		if( forceAccept )
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
idConsole* console = &localConsole;
