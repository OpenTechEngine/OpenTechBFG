
#include "MenuScreen_CEGUI.h"

//*
//================================================
//idMenuScreen_HUD
//================================================
//*/
idMenuScreen_HUD::idMenuScreen_HUD() {}
idMenuScreen_HUD::~idMenuScreen_HUD() {}

void idMenuScreen_HUD::UpdateHealthArmor( idPlayer* player ) {}
void idMenuScreen_HUD::UpdateStamina( idPlayer* player ) {}
void idMenuScreen_HUD::UpdateLocation( idPlayer* player ) {}
void idMenuScreen_HUD::UpdateWeaponInfo( idPlayer* player ) {}
void idMenuScreen_HUD::UpdateWeaponStates( idPlayer* player, bool weaponChanged ) {}

void idMenuScreen_HUD::DownloadVideo() {}
void idMenuScreen_HUD::DownloadPDA( const idDeclPDA* pda, bool newSecurity ) {}
void idMenuScreen_HUD::UpdatedSecurity() {}

void idMenuScreen_HUD::ClearNewPDAInfo() {}

void idMenuScreen_HUD::UpdateOxygen( bool show, int val ) {}
void idMenuScreen_HUD::SetupObjective( const idStr& title, const idStr& desc, const idMaterial* screenshot ) {}
void idMenuScreen_HUD::SetupObjectiveComplete( const idStr& title ) {}
void idMenuScreen_HUD::ShowObjective( bool complete ) {}
void idMenuScreen_HUD::HideObjective( bool complete ) {}
void idMenuScreen_HUD::GiveWeapon( idPlayer* player, int weaponIndex ) {}
void idMenuScreen_HUD::UpdatePickupInfo( int index, const idStr& name ) {}
bool idMenuScreen_HUD::IsPickupListReady()
{
	return true;
}
void idMenuScreen_HUD::ShowPickups() {}
void idMenuScreen_HUD::SetCursorState( idPlayer* player, cursorState_t state, int set ) {}
void idMenuScreen_HUD::SetCursorText( const idStr& action, const idStr& focus ) {}
void idMenuScreen_HUD::UpdateCursorState() {}
void idMenuScreen_HUD::CombatCursorFlash() {}
void idMenuScreen_HUD::UpdateSoulCube( bool ready ) {}
void idMenuScreen_HUD::ShowRespawnMessage( bool show ) {}
void idMenuScreen_HUD::SetShowSoulCubeOnLoad( bool show ) {}

// MULTIPLAYER

void idMenuScreen_HUD::ToggleMPInfo( bool show, bool showTeams, bool isCTF ) {}
void idMenuScreen_HUD::SetFlagState( int team, int state ) {}
void idMenuScreen_HUD::SetTeamScore( int team, int score ) {}
void idMenuScreen_HUD::SetTeam( int team ) {}
void idMenuScreen_HUD::TriggerHitTarget( bool show, const idStr& target, int color ) {}
void idMenuScreen_HUD::ToggleLagged( bool show ) {}
void idMenuScreen_HUD::UpdateGameTime( const char* time ) {}
void idMenuScreen_HUD::UpdateMessage( bool show, const idStr& message ) {}
void idMenuScreen_HUD::ShowNewItem( const char* name, const char* icon ) {}
void idMenuScreen_HUD::UpdateFlashlight( idPlayer* player ) {}
void idMenuScreen_HUD::UpdateChattingHud( idPlayer* player ) {}
