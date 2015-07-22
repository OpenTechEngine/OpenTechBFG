#ifndef MainMenu_H_
#define MainMenu_H_

#include "cegui/menu/GameMenu.h"

#include "cegui/wrap_cegui.h"
#include "cegui/CEGUI_Hooks.h"


namespace CEGUIMenu
{

class MainMenu : public GameMenu
{
public:
	MainMenu();
	virtual ~MainMenu();
	
	virtual void init();
	virtual void destroy();
	
	virtual void setVisible( bool visible );
	
protected:
	virtual void LoadNestedWindows();
	virtual void RegisterHandlers();
	
private:
	void AttachCEGUIRootWindow();
	
	bool Handle_CampaignClick( const CEGUI::EventArgs& );
	bool Handle_MultiplayerClick( const CEGUI::EventArgs& );
	bool Handle_SettingsClick( const CEGUI::EventArgs& );
	bool Handle_CreditsClick( const CEGUI::EventArgs& );
	bool Handle_QuitClick( const CEGUI::EventArgs& );
	
	GameMenu* settings;
};


} /* namespace CEGUIMenu */

#endif /* MainMenu_H_ */
