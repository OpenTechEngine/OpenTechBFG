/*
 * ConsoleEditBox.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: kordex
 */

#include <cegui/console/ConsoleEditBox.h>

namespace CEGUIConsole
{

const CEGUI::String ConsoleEditBox::WidgetTypeName( "CEGUIConsole/ConsoleEditBox" );

void ConsoleEditBox::onKeyDown( CEGUI::KeyEventArgs& e )
{
	// fire event.
	fireEvent( EventKeyDown, e, Window::EventNamespace );
	
	if( e.handled == 0 && hasInputFocus() )
	{
		if( isReadOnly() )
		{
			Window::onKeyDown( e );
			return;
		}
		
		CEGUI::WindowEventArgs args( this );
		switch( e.scancode )
		{
			case CEGUI::Key::LeftShift:
			case CEGUI::Key::RightShift:
				if( getSelectionLength() == 0 )
					d_dragAnchorIdx = d_caretPos;
				break;
				
			case CEGUI::Key::Backspace:
				handleBackspace();
				break;
				
			case CEGUI::Key::Delete:
				handleDelete();
				break;
				
			case CEGUI::Key::Return:
			case CEGUI::Key::NumpadEnter:
				// Fire 'input accepted' event
				onTextAcceptedEvent( args );
				break;
				
			case CEGUI::Key::ArrowLeft:
				if( e.sysKeys & CEGUI::Control )
					handleWordLeft( e.sysKeys );
				else
					handleCharLeft( e.sysKeys );
				break;
				
			case CEGUI::Key::ArrowRight:
				if( e.sysKeys & CEGUI::Control )
					handleWordRight( e.sysKeys );
				else
					handleCharRight( e.sysKeys );
				break;
				
			case CEGUI::Key::Home:
				handleHome( e.sysKeys );
				break;
				
			case CEGUI::Key::End:
				handleEnd( e.sysKeys );
				break;
				
			default:
				Window::onKeyDown( e );
				return;
		}
		
		++e.handled;
	}
	
}

} /* namespace CEGUIConsole */
