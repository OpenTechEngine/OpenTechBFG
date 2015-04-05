/*
 * MenuSystem.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kordex
 */

#ifndef MENUSYSTEM_H_
#define MENUSYSTEM_H_

#include "MenuInterface.h"

namespace CEGUIMenu
{

class MenuSystem
{
public:
	MenuSystem();
	virtual ~MenuSystem();
	
	void Init();
	void Destroy();
private:
	MenuInterface* mainMenu;
};

} /* namespace CEGUIMenu */

#endif /* MENUSYSTEM_H_ */
