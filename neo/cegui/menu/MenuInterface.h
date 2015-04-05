/*
 * MenuInterface.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kordex
 */

#ifndef MENUINTERFACE_H_
#define MENUINTERFACE_H_

namespace CEGUIMenu
{

class MenuInterface
{
public:
	virtual ~MenuInterface() {};
	
	virtual void setVisible( bool visible ) = 0;
	virtual bool isVisible() = 0;
	
};

} /* namespace CEGUIMenu */

#endif /* MENUINTERFACE_H_ */
