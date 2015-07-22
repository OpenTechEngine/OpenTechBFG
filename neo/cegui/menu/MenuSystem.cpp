/*
 * MenuSystem.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: kordex
 */

#include "MenuLocator.h"
#include "MainMenu/MainMenu.h"

#include "MenuSystem.h"

namespace CEGUIMenu
{

MenuSystem::MenuSystem() :
	mainMenu()
{
	// TODO Auto-generated constructor stub
	
}

MenuSystem::~MenuSystem()
{
	// TODO Auto-generated destructor stub
}

void MenuSystem::Init()
{
	mainMenu = new MainMenu();
	mainMenu->init();
	MenuLocator::provideMain( mainMenu );
}

void MenuSystem::Destroy()
{
	mainMenu->destroy();
	delete mainMenu;
}

} /* namespace CEGUIMenu */
