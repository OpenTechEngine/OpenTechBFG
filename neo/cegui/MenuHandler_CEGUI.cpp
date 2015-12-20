
#include "MenuHandler_CEGUI.h"
#include "MenuScreen_CEGUI.h" // for idMenuScreen_HUD

#include "framework/Common.h" // TODO remove temp include

#include "menu/MenuLocator.h"

#include "cegui/CEGUI_Hooks.h"

/* Notes

In to the mainmenu:

Shell:
SetInGame 0
Initialize "shell"
ActivateMenu 1
SetShellState 0

HandleGuiEvent spam

Entering map:

Update spam

Returning to mainmenu from map:
ActivateMenu 0
SetInGame 0
Initialize "shell"
ActivateMenu 1
SetShellState 1

In to the game:
HUD:
Intialize "hud"
ActivateMenu 1
GetHud spam
Update spam

PDA:
Initialize "pda"

Shell:
SetInGame 1
Initialize "pause"
SetShellState 4

 */

namespace BFG
{

struct idMenuHandler::MenuVars
{
	idMenuScreen_HUD* ourHud;
};


/*
================================================
idMenuHandler
================================================
*/
idMenuHandler::idMenuHandler() :
	ourVars( new MenuVars )
{
}
idMenuHandler::~idMenuHandler()
{
}

bool idMenuHandler::IsActive()
{
	//common->Printf("idMenuHandler::IsActive\n");
	return CEGUIMenu::MenuLocator::getMain()->isVisible();
}
void idMenuHandler::ClearWidgetActionRepeater()
{
	common->Printf( "idMenuHandler::ClearWidgetActionRepeater\n" );
}
bool idMenuHandler::HandleGuiEvent( const sysEvent_t* sev )
{
	return idCEGUI::InjectSysEvent( sev );
}

/*
================================================
idMenuHandler_Shell
================================================
 */
idMenuHandler_Shell::idMenuHandler_Shell()
	: state( SHELL_STATE_INVALID )
{
	// not really like this, multiple instances of this idMenuHandler exist :|
	// our static
}
idMenuHandler_Shell::~idMenuHandler_Shell()
{
}

void idMenuHandler_Shell::Update()
{
//	common->Printf("idMenuHandler_Shell::Update\n");
// to update the menu content based on the internal variables?
	return;
}

void idMenuHandler_Shell::ActivateMenu( bool show )
{
	CEGUIMenu::MenuLocator::getMain()->setVisible( show );
	common->Printf( "idMenuHandler_Shell::ActivateMenu %d\n", show );
// show hide?
}

void idMenuHandler_Shell::Initialize( const char* swfFile, idSoundWorld* sw )
{
//	common->Printf("idMenuHandler_Shell::Initialize %s\n", swfFile);
// if swfFile strcmp "shell" -> main, strcmp "pause" -> pause
	return;
}

void idMenuHandler_Shell::UpdateSavedGames()
{
	common->Printf( "idMenuHandler_Shell::UpdateSavedGames\n" );
// update the saved games list?
}
void idMenuHandler_Shell::SetShellState( shellState_t s )
{
	if( s != state )
	{
		state = s;
		common->Printf( "idMenuHandler_Shell::SetShellState CHANGED %d\n", s );
		
		if( state == SHELL_STATE_PAUSED )
		{
			// no pause menu yet so we just hide the main and get going
			CEGUIMenu::MenuLocator::getMain()->setVisible( false );
		}
	}
	
// enum with initial press start? and multiplayer lobby states
}
void idMenuHandler_Shell::SetNextScreen( int screen, int trans )
{
	// called with SHELL_AREA_INVALID to close main menu
	if( screen == SHELL_AREA_INVALID )
	{
		ActivateMenu( false );
	}
	else
	{
		common->Printf( "idMenuHandler_Shell::SetNextScreen %d %d\n", screen, trans );
		// TODO: are there any other cases we should care about?
	}
}

void idMenuHandler_Shell::SetInGame( bool val )
{
	common->Printf( "idMenuHandler_Shell::SetInGame %d\n", val );
// set internal variable to show pause menu or main
}
void idMenuHandler_Shell::UpdateLeaderboard( const idLeaderboardCallback* callback )
{
	common->Printf( "idMenuHandler_Shell::UpdateLeaderboard\n" );
// update leaderboards? whatever that is from callback, rows mainly?
}
void idMenuHandler_Shell::SetCanContinue( bool valid )
{
	common->Printf( "idMenuHandler_Shell::SetCanContinue %d\n", valid );
// set internal variable for dead or not dead? multiplayer always continue?
}
void idMenuHandler_Shell::SetGameComplete()
{
	common->Printf( "idMenuHandler_Shell::SetGameComplete\n" );
// not slightest idea? perhaps credits?
}
bool idMenuHandler_Shell::GetGameComplete()
{
	common->Printf( "idMenuHandler_Shell::GetGameComplete\n" );
	return false;
}
void idMenuHandler_Shell::SetTimeRemaining( int time )
{
	common->Printf( "idMenuHandler_Shell::SetTimeRemaining\n" );
// objective?
}


/*
================================================
idMenuHandler_PDA
================================================
*/
idMenuHandler_PDA::idMenuHandler_PDA() {}
idMenuHandler_PDA::~idMenuHandler_PDA() {}

void idMenuHandler_PDA::Update()
{
	common->Printf( "idMenuHandler_PDA::Update\n" );
}
void idMenuHandler_PDA::ActivateMenu( bool show )
{
	common->Printf( "idMenuHandler_PDA::ActivateMenu %d\n", show );
}
void idMenuHandler_PDA::Initialize( const char* swfFile, idSoundWorld* sw )
{
	common->Printf( "idMenuHandler_PDA::Initialize %s\n", swfFile );
}

/*
================================================
idMenuHandler_HUD
================================================
*/
idMenuHandler_HUD::idMenuHandler_HUD()
{
	ourVars->ourHud = new idMenuScreen_HUD;
}
idMenuHandler_HUD::~idMenuHandler_HUD()
{
	delete ourVars->ourHud;
}

void idMenuHandler_HUD::Update()
{
	// common->Printf( "idMenuHandler_HUD::Update\n" ); // FIXME: DG: don't spam.
}
void idMenuHandler_HUD::ActivateMenu( bool show )
{
	common->Printf( "idMenuHandler_HUD::ActivateMenu %d\n", show );
}
void idMenuHandler_HUD::Initialize( const char* swfFile, idSoundWorld* sw )
{
	common->Printf( "idMenuHandler_HUD::Initialize %s\n", swfFile );
}

idMenuScreen_HUD* idMenuHandler_HUD::GetHud()
{
	// common->Printf( "idMenuHandler_HUD::GetHud()\n" );
	return ourVars->ourHud;
}
void idMenuHandler_HUD::ShowTip( const char* title, const char* tip, bool autoHide )
{
	common->Printf( "idMenuHandler_HUD::ShowTip %s %s %d\n", title, tip, autoHide );
}
void idMenuHandler_HUD::HideTip()
{
	common->Printf( "idMenuHandler_HUD::HideTip\n" );
}
void idMenuHandler_HUD::SetRadioMessage( bool show )
{
	common->Printf( "idMenuHandler_HUD::SetRadioMessage %d\n", show );
}

/*
================================================
idMenuHandler_Scoreboard
================================================
*/
idMenuHandler_Scoreboard::idMenuHandler_Scoreboard() {}
idMenuHandler_Scoreboard::~idMenuHandler_Scoreboard() {}

void idMenuHandler_Scoreboard::Update()
{
	common->Printf( "idMenuHandler_Scoreboard::Update\n" );
}
void idMenuHandler_Scoreboard::ActivateMenu( bool show )
{
	common->Printf( "idMenuHandler_Scoreboard::ActivateMenu %d\n", show );
}
void idMenuHandler_Scoreboard::Initialize( const char* swfFile, idSoundWorld* sw )
{
	common->Printf( "idMenuHandler_Scoreboard::Initialize %s\n", swfFile );
}
void idMenuHandler_Scoreboard::UpdateScoreboard( idList< mpScoreboardInfo >& data, idStr gameInfo )
{
	common->Printf( "idMenuHandler_Scoreboard::UpdateScoreboard\n" );
}
void idMenuHandler_Scoreboard::UpdateSpectating( idStr spectate, idStr follow )
{
	common->Printf( "idMenuHandler_Scoreboard::UpdateSpectating %s %s\n", spectate.c_str(), follow.c_str() );
}
void idMenuHandler_Scoreboard::SetTeamScores( int r, int b )
{
	common->Printf( "idMenuHandler_Scoreboard::SetTeamScores %d %d\n", r, b );
}
void idMenuHandler_Scoreboard::SetActivationScreen( int screen, int trans )
{
	common->Printf( "idMenuHandler_Scoreboard::SetActivationScreen %d %d\n", screen, trans );
}
void idMenuHandler_Scoreboard::UpdateScoreboardSelection()
{
	common->Printf( "idMenuHandler_Scoreboard::UpdateScoreboardSelection\n" );
}

} // namespace BFG
