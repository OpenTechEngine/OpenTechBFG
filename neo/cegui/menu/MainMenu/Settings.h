/*
 * Settings.h
 *
 *  Created on: Apr 26, 2015
 *      Author: kordex
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <cegui/menu/GameMenu.h>

namespace CEGUIMenu
{

class Settings: public GameMenu
{
public:
	Settings();
	virtual ~Settings();
	
	virtual void init();
	virtual void destroy();
	
	
protected:
	virtual void LoadNestedWindows();
	virtual void RegisterHandlers();
	
private:
	void hide();
};

} /* namespace CEGUIMenu */

#endif /* SETTINGS_H_ */
