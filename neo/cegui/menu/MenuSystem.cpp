/*
 * MenuSystem.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: kordex
 */

#include "MenuLocator.h"
#include "MainMenu.h"

#include "MenuSystem.h"

namespace CEGUIMenu {

MenuSystem::MenuSystem() {
	// TODO Auto-generated constructor stub

}

MenuSystem::~MenuSystem() {
	// TODO Auto-generated destructor stub
}

void MenuSystem::Init()
{
	mainMenu = new MainMenu();
	MenuLocator::provideMain(mainMenu);
}

void MenuSystem::Destroy()
{
	delete mainMenu;
}

} /* namespace CEGUIMenu */
