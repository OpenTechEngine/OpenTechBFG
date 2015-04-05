/*
 * NullMenu.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kordex
 */

#ifndef NULLMENU_H_
#define NULLMENU_H_

#include <cegui/menu/MenuInterface.h>

namespace CEGUIMenu {

class NullMenu: public MenuInterface {
public:
	NullMenu();
	virtual ~NullMenu();

	virtual void setVisible( bool visible ) {}
	virtual bool isVisible() { return false; }
};

} /* namespace CEGUIMenu */

#endif /* NULLMENU_H_ */
