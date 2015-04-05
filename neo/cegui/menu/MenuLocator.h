/*
 * MenuLocator.h
 *
 *  Created on: 5.4.2015
 *      Author: Administrator
 */

#ifndef _MENULOCATOR_H_
#define _MENULOCATOR_H_

#include "MenuInterface.h"
#include "NullMenu.h"

namespace CEGUIMenu {

class MenuLocator {
public:
	MenuLocator();
	virtual ~MenuLocator();

	static MenuInterface* getMain()
	{
		if (service_)
		{
			return service_;
		}
		else {
			return nullService_;
		}

	}

	static void provideMain(MenuInterface* service)
	{
		service_ = service;
	}

private:
	static MenuInterface* nullService_;
	static MenuInterface* service_;
};

} /* namespace CEGUIMenu */

#endif /* _MENULOCATOR_H_ */

