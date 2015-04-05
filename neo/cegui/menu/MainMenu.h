#ifndef MainMenu_H_
#define MainMenu_H_

#include "GameMenu.h"

#include "cegui/wrap_cegui.h"
#include "../CEGUI_Hooks.h"


namespace CEGUIMenu
{

class MainMenu : public GameMenu
{
public:
	MainMenu();
	virtual ~MainMenu();
	
protected:
	virtual void RegisterHandlers();
	
private:
	bool Handle_DemoMapClick( const CEGUI::EventArgs& );
	bool Handle_QuitClick( const CEGUI::EventArgs& );
	
};


} /* namespace CEGUIMenu */

#endif /* MainMenu_H_ */
