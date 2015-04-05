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


namespace CEGUIMenu {

class GameMenu : public MenuInterface {
public:
	GameMenu();
	GameMenu(CEGUI::String layoutFile, CEGUI::String rootWindowName);
	virtual ~GameMenu();

	virtual void setVisible( bool visible );
	virtual bool isVisible();

protected:
	virtual void CreateCEGUIWindow();
	virtual void RegisterHandlers() = 0;

	CEGUI::String layoutFile;
	CEGUI::String rootWindowName;
	CEGUI::Window* rootWindow;

};

} /* namespace CEGUIMenu */

#endif /* GAMEMENU_H */
