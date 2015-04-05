/*
 * GameMenu.cpp
 *
 *  Created on: 3.4.2015
 *      Author: Administrator
 */

#include "GameMenu.h"
#include "../CEGUI_Hooks.h"

namespace CEGUIMenu
{


GameMenu::GameMenu() :
	layoutFile(),
	rootWindowName(),
	rootWindow( static_cast<CEGUI::Window*>( 0 ) )
{
	/*
	CreateCEGUIWindow();
	RegisterHandlers();
	setVisible( true );
	*/
}

GameMenu::GameMenu( CEGUI::String layoutFile, CEGUI::String rootWindowName ) :
	layoutFile( layoutFile ),
	rootWindowName( rootWindowName ),
	rootWindow( static_cast<CEGUI::Window*>( 0 ) )
{
	CreateCEGUIWindow();
	//	RegisterHandlers();
	setVisible( false );
}

GameMenu::~GameMenu()
{
	// TODO GameMenu destructor
}

void GameMenu::CreateCEGUIWindow()
{
	if( idCEGUI::IsInitialized() )
	{
		CEGUI::System::getSingleton().getDefaultGUIContext()
		.getRootWindow()->addChild(
			CEGUI::WindowManager::getSingleton().
			loadLayoutFromFile( layoutFile ) );
			
		rootWindow = CEGUI::System::getSingleton().getDefaultGUIContext()
					 .getRootWindow()->getChild( rootWindowName );
	}
}

void GameMenu::setVisible( bool visible )
{
	if( idCEGUI::IsInitialized() )
	{
		rootWindow->setVisible( visible );
		
		if( visible )
		{
			CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
		}
		else
		{
			CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
		}
	}
}

bool GameMenu::isVisible()
{
	if( idCEGUI::IsInitialized() )
	{
		return rootWindow->isVisible();
	}
	return false;
}


} /* namespace CEGUIMenu */
