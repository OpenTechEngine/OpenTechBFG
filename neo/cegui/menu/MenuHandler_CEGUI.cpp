
#include "MenuHandler_CEGUI.h"
#include "MenuScreen_CEGUI.h" // for idMenuScreen_HUD

/*
================================================
idMenuHandler
================================================
*/
idMenuHandler::idMenuHandler() {}
idMenuHandler::~idMenuHandler() {}

bool idMenuHandler::IsActive()
{
	return false;
}
void idMenuHandler::ClearWidgetActionRepeater() {}
bool idMenuHandler::HandleGuiEvent( const sysEvent_t* sev )
{
	return true;
}

/*
================================================
idMenuHandler_Shell
================================================
 */
idMenuHandler_Shell::idMenuHandler_Shell() {}
idMenuHandler_Shell::~idMenuHandler_Shell() {}

void idMenuHandler_Shell::Update() {}
void idMenuHandler_Shell::ActivateMenu( bool show ) {}
void idMenuHandler_Shell::Initialize( const char* swfFile, idSoundWorld* sw ) {}

void idMenuHandler_Shell::UpdateSavedGames() {}
void idMenuHandler_Shell::SetShellState( shellState_t s ) {}
void idMenuHandler_Shell::SetNextScreen( int screen, int trans ) {}

void idMenuHandler_Shell::SetInGame( bool val ) {}
void idMenuHandler_Shell::UpdateLeaderboard( const idLeaderboardCallback* callback ) {}
void idMenuHandler_Shell::SetCanContinue( bool valid ) {}
void idMenuHandler_Shell::SetGameComplete() {}
bool idMenuHandler_Shell::GetGameComplete()
{
	return false;
}
void idMenuHandler_Shell::SetTimeRemaining( int time ) {}


/*
================================================
idMenuHandler_PDA
================================================
*/
idMenuHandler_PDA::idMenuHandler_PDA() {}
idMenuHandler_PDA::~idMenuHandler_PDA() {}

void idMenuHandler_PDA::Update() {}
void idMenuHandler_PDA::ActivateMenu( bool show ) {}
void idMenuHandler_PDA::Initialize( const char* swfFile, idSoundWorld* sw ) {}

/*
================================================
idMenuHandler_HUD
================================================
*/
idMenuHandler_HUD::idMenuHandler_HUD() {}
idMenuHandler_HUD::~idMenuHandler_HUD() {};

void idMenuHandler_HUD::Update() {}
void idMenuHandler_HUD::ActivateMenu( bool show ) {}
void idMenuHandler_HUD::Initialize( const char* swfFile, idSoundWorld* sw ) {}

idMenuScreen_HUD* idMenuHandler_HUD::GetHud()
{
	return new idMenuScreen_HUD;
}
void idMenuHandler_HUD::ShowTip( const char* title, const char* tip, bool autoHide ) {}
void idMenuHandler_HUD::HideTip() {}
void idMenuHandler_HUD::SetRadioMessage( bool show ) {}

/*
================================================
idMenuHandler_Scoreboard
================================================
*/
idMenuHandler_Scoreboard::idMenuHandler_Scoreboard() {}
idMenuHandler_Scoreboard::~idMenuHandler_Scoreboard() {}

void idMenuHandler_Scoreboard::Update() {}
void idMenuHandler_Scoreboard::ActivateMenu( bool show ) {}
void idMenuHandler_Scoreboard::Initialize( const char* swfFile, idSoundWorld* sw ) {}
void idMenuHandler_Scoreboard::UpdateScoreboard( idList< mpScoreboardInfo >& data, idStr gameInfo ) {}
void idMenuHandler_Scoreboard::UpdateSpectating( idStr spectate, idStr follow ) {}
void idMenuHandler_Scoreboard::SetTeamScores( int r, int b ) {}
void idMenuHandler_Scoreboard::SetActivationScreen( int screen, int trans ) {}
void idMenuHandler_Scoreboard::UpdateScoreboardSelection() {}


