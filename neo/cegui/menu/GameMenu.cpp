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

GameMenu::GameMenu( CEGUI::String layoutFile ) :
	window( static_cast<CEGUI::Window*>( 0 ) ),
	layoutFile( layoutFile )
{

}

GameMenu::~GameMenu()
{

}

void GameMenu::CreateCEGUIWindow()
{
	if( idCEGUI::IsInitialized() )
	{
		window = CEGUI::WindowManager::getSingleton().
				loadLayoutFromFile( layoutFile );
	}
}

void GameMenu::setVisible( bool visible )
{
	if( idCEGUI::IsInitialized() )
	{
		window->setVisible( visible );
	}
}

bool GameMenu::isVisible()
{
	if( idCEGUI::IsInitialized() )
	{
		return window->isVisible();
	}
	return false;
}


} /* namespace CEGUIMenu */
