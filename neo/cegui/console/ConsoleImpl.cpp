/*
 * CEGUIConsole.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: kordex
 */

#include <memory>
#include <list>
#include "cegui/CEGUI_Hooks.h" // for initialization check
#include "Console.h"
#include "ConsoleEditBox.h"
#include "ConsoleImpl.h"
#include "ConsoleMsg.h"

#include "../idlib/Str.h"
#include "../framework/ConsoleHistory.h"
#include "../framework/CmdSystem.h"

namespace BFG
{

namespace CEGUIConsole
{

struct ConsoleImpl::ConsoleImplVars
{
	std::list<CEGUI::String> tabCompletions;
};

ConsoleImpl::ConsoleImpl() :
	ourVars( new ConsoleImplVars )
{
	CreateCEGUIWindow();
	RegisterHandlers();
	setVisible( false );
}

ConsoleImpl::~ConsoleImpl()
{
	// TODO should also remove subscriptions and windows ..
	this->ourVars->tabCompletions.clear();
}

void ConsoleImpl::CreateCEGUIWindow()
{
	if( idCEGUI::IsInitialized() )
	{
		// add our custom editbox, where tab does not insert enter
		CEGUI::WindowFactoryManager::addWindowType<CEGUIConsole::ConsoleEditBox>();
		
		CEGUI::System::getSingleton().getDefaultGUIContext()
		.getRootWindow()->addChild(
			CEGUI::WindowManager::getSingleton().
			loadLayoutFromFile( "console.layout" ) );
	}
}
void ConsoleImpl::RegisterHandlers()
{
	if( idCEGUI::IsInitialized() )
	{
		CEGUI::Window* ConsoleWin = CEGUI::System::getSingleton().getDefaultGUIContext()
									.getRootWindow()->getChild( "Console" );
									
									
		/*
		 * handles mouse on submit to input
		 */
		ConsoleWin->getChild( "Submit" )->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			&ConsoleImpl::Handle_TextSubmitted,
			( this )
		);
		/*
		 * handles keypress (enter) to input
		 */
		
		// FIXME catches tab too, some way to avoid that?
		ConsoleWin->getChild( "Combobox" )->subscribeEvent(
			CEGUI::Combobox::EventTextAccepted,
			&ConsoleImpl::Handle_TextSubmitted,
			( this )
		);
	}
}

bool ConsoleImpl::Handle_TextSubmitted( const CEGUI::EventArgs& args )
{
	if( idCEGUI::IsInitialized() )
	{
		CEGUI::Window* ConsoleWin = CEGUI::System::getSingleton().getDefaultGUIContext()
									.getRootWindow()->getChild( "Console" );
									
		CEGUI::String Line = ConsoleWin->getChild( "Combobox" )->getText();
		
		( this )->Execute( Line );
		
		ConsoleWin->getChild( "Combobox" )->setText( "" );
		
		return true;
	}
	return false;
}

void ConsoleImpl::OutputText( ConsoleMsg outMsg )
{
	/*
	 * checks if cegui is initialized
	 */
	if( idCEGUI::IsInitialized() )
	{
		//ConsoleMsg outMsg = ConsoleMsg(inMsg);
		
		CEGUI::Window* ConsoleWin = CEGUI::System::getSingleton().getDefaultGUIContext()
									.getRootWindow()->getChild( "Console" );
		if( ConsoleWin != NULL )
		{
			CEGUI::Listbox* outputWindow = static_cast<CEGUI::Listbox*>( ConsoleWin->getChild( "History" ) );
			
			CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem( outMsg.msg );
			outputWindow->addItem( newItem );
			( this )->ScrollBottom();
		}
		
	}
}


void ConsoleImpl::setVisible( bool visible )
{
	if( idCEGUI::IsInitialized() )
	{
		CEGUI::Window* ConsoleWin = CEGUI::System::getSingleton().getDefaultGUIContext()
									.getRootWindow()->getChild( "Console" );
		ConsoleWin->setVisible( visible );
		
		if( visible )
		{
			ConsoleWin->getChild( "Combobox" )->activate();
			CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
		}
		else
		{
			ConsoleWin->getChild( "Combobox" )->deactivate();
			CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
		}
	}
}

bool ConsoleImpl::isVisible()
{
	if( idCEGUI::IsInitialized() )
	{
		CEGUI::Window* ConsoleWin = CEGUI::System::getSingleton().getDefaultGUIContext()
									.getRootWindow()->getChild( "Console" );
		return ConsoleWin->isVisible();
	}
	return false;
}

void ConsoleImpl::ScrollBottom()
{
	if( idCEGUI::IsInitialized() )
	{
		CEGUI::Window* ConsoleWin = CEGUI::System::getSingleton().getDefaultGUIContext()
									.getRootWindow()->getChild( "Console" );
									
		CEGUI::Listbox* outputWindow = static_cast<CEGUI::Listbox*>( ConsoleWin->getChild( "History" ) );
		
		float document_size = outputWindow->getVertScrollbar()->getDocumentSize();
		float page_size = outputWindow->getVertScrollbar()->getPageSize();
		
		
		outputWindow->getVertScrollbar()->setScrollPosition( document_size - page_size );
	}
}

void ConsoleImpl::Execute( CEGUI::String inMsg )
{
	const char* cmd = inMsg.c_str();
	if( strlen( cmd ) >= 1 )
	{
	
		BFG::cmdSystem->BufferCommandText( BFG::CMD_EXEC_APPEND, cmd );	// valid command
		BFG::cmdSystem->BufferCommandText( BFG::CMD_EXEC_APPEND, "\n" );
		BFG::consoleHistory.AddToHistory( cmd );
	}
}

void ConsoleImpl::PopulateHistory( void )
{
	// TODO implement cegui window historylist aka the dropdown list,
	// should be filled on access
	BFG::idStr hist = BFG::consoleHistory.RetrieveFromHistory( true );
}

void ConsoleImpl::TabComplete( void )
{
	if( idCEGUI::IsInitialized() )
	{
		CEGUI::Window* ConsoleWin = CEGUI::System::getSingleton().getDefaultGUIContext()
									.getRootWindow()->getChild( "Console" );
									
		CEGUI::String cmdStub = ConsoleWin->getChild( "Combobox" )->getText();
		
		// provides all valid commands to callback function
		BFG::cmdSystem->CommandCompletion( AutoCompleteCallback ); // function pointer to our static member function
		// provides all valid arguments for supplied command to callback function
		BFG::cmdSystem->ArgCompletion( cmdStub.c_str(), AutoCompleteCallback );
		
		// provides all valid cvar commands to callback function
		cvarSystem->CommandCompletion( AutoCompleteCallback );
		// provides all valid cvar arguments for supplied command to callback function
		cvarSystem->ArgCompletion( cmdStub.c_str(), AutoCompleteCallback );
		
		// sorting matches
		this->ourVars->tabCompletions.sort();
		// for finding common part of the completion
		int matchSize = INT_MAX;
		CEGUI::String bestMatch = cmdStub;
		// iterating over the list of matches
		std::list<CEGUI::String>::iterator it;
		for(
			std::list<CEGUI::String>::iterator it = this->ourVars->tabCompletions.begin();
			it != this->ourVars->tabCompletions.end();
			it++
		)
		{
			if( it->length() < matchSize )
			{
				matchSize = it->length();
				bestMatch = *it;
			}
			OutputText( ConsoleMsg( *it ) );
		}
		// set command line to best match
		ConsoleWin->getChild( "Combobox" )->setText( bestMatch );
		this->ourVars->tabCompletions.clear();
	}
}

// for accessing friend class CEGUIConsole::Console::ConsoleVars struct
struct Console::ConsoleVars
{
	ConsoleImpl* consoleInstance;
};

void ConsoleImpl::AutoCompleteCallback( const char* s )
{
	// this little fellow just gets all the matches and is responsible for acting accordingly
	// for now let's test and print..
	
	// accessing friend class for function pointer
	CEGUIConsole::Console* ourConsole = dynamic_cast<CEGUIConsole::Console*>( BFG::console );
	ourConsole->ourVars->consoleInstance->TabCompleteListAdd( CEGUI::String( s ) );
}

// this is a iterator function which goes through all options for completion
void ConsoleImpl::TabCompleteListAdd( CEGUI::String option )
{
	if( idCEGUI::IsInitialized() )
	{
		CEGUI::Window* ConsoleWin =
			CEGUI::System::getSingleton()
			.getDefaultGUIContext().getRootWindow()->getChild( "Console" );
		if( ConsoleWin != NULL )
		{
			// our console input
			CEGUI::String cmdStub = ConsoleWin->getChild( "Combobox" )->getText();
			
			// stub matches fully to this option
			if( BFG::idStr::Icmpn( option.c_str(), cmdStub.c_str(), strlen( cmdStub.c_str() ) ) == 0 )
			{
				// add the partitial match
				// TODO color the matching part
				this->ourVars->tabCompletions.push_back( option );
				return;
			}
		}
	}
}

} /* namespace CEGUIConsole */

} // namespace BFG
