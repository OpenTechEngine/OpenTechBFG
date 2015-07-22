/*
 * Settings.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: kordex
 */

#include <cegui/menu/MainMenu/Settings.h>

namespace CEGUIMenu
{

Settings::Settings() :
	GameMenu( "MainMenu/Settings.layout" )
{


}

Settings::~Settings()
{

}

void Settings::init()
{
	CreateCEGUIWindow();
	setVisible( false );
	
	LoadNestedWindows();
	RegisterHandlers();
}

void Settings::destroy()
{

}

void Settings::LoadNestedWindows()
{

}

void Settings::RegisterHandlers()
{
	window->subscribeEvent(
		CEGUI::FrameWindow::EventCloseClicked,
		&Settings::hide,
		( this )
	);
}

void Settings::hide()
{
	setVisible( false );
}

} /* namespace CEGUIMenu */
