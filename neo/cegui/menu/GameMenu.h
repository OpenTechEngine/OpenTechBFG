/*
 * GameMenu.h
 *
 *  Created on: 3.4.2015
 *      Author: Administrator
 */

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "MenuInterface.h"
#include "GameMenu.h"
#include "cegui/wrap_cegui.h"


namespace CEGUIMenu
{

class GameMenu : public MenuInterface
{
public:
	GameMenu();
	GameMenu( CEGUI::String layoutFile );
	virtual ~GameMenu();
	
	virtual void init() = 0;
	virtual void destroy() = 0;

	virtual void setVisible( bool visible );
	virtual bool isVisible();

	virtual CEGUI::Window* getWindowPtr() { return window; }

protected:
	virtual void CreateCEGUIWindow();
	virtual void RegisterHandlers() = 0;
	virtual void LoadNestedWindows() = 0;
	CEGUI::Window* window;
	
private:
	CEGUI::String layoutFile;
};

} /* namespace CEGUIMenu */

#endif /* GAMEMENU_H */
