/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 BFG Edition GPL Source Code ("Doom 3 BFG Edition Source Code").

Doom 3 BFG Edition Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 BFG Edition Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 BFG Edition Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 BFG Edition Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 BFG Edition Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
#ifndef __MENUHANDLERCEGUI_H__
#define __MENUHANDLERCEGUI_H__

#include "../sys/sys_session.h" // for voiceStateDisplay_t

#include "../d3xp/menus/MenuHandler_Interface.h" // for Interfaces
#include "../d3xp/menus/MenuState.h"

#include "../d3xp/menus/mpScoreboardInfo.h"

/*
================================================
idMenuHandler
================================================
*/
class idMenuHandler : public idMenuHandler_Interface
{
public:
	idMenuHandler();
	~idMenuHandler();
	
	virtual bool IsActive();
	virtual void ClearWidgetActionRepeater();
	virtual bool HandleGuiEvent( const sysEvent_t* sev );
	
protected:
	struct MenuVars;
	MenuVars* ourVars;
};

/*
================================================
idMenuHandler_Shell
================================================
 */
class idMenuHandler_Shell : public idMenuHandler_Shell_Interface, public idMenuHandler
{
public:
	idMenuHandler_Shell();
	~idMenuHandler_Shell();
	
	virtual bool IsActive()
	{
		return idMenuHandler::IsActive();
	}
	virtual void ClearWidgetActionRepeater()
	{
		idMenuHandler::ClearWidgetActionRepeater();
	}
	virtual bool HandleGuiEvent( const sysEvent_t* sev )
	{
		return idMenuHandler::HandleGuiEvent( sev );
	}
	
	virtual void Update();
	virtual void ActivateMenu( bool show );
	virtual void Initialize( const char* swfFile, idSoundWorld* sw );
	
	virtual void UpdateSavedGames();
	virtual void SetShellState( shellState_t s );
	virtual void SetNextScreen( int screen, int trans );
	
	virtual void SetInGame( bool val );
	virtual void UpdateLeaderboard( const idLeaderboardCallback* callback );
	virtual void SetCanContinue( bool valid );
	virtual void SetGameComplete();
	virtual bool GetGameComplete();
	virtual void SetTimeRemaining( int time );
	
private:
	shellState_t state;
};

/*
================================================
idMenuHandler_PDA
================================================
*/
class idMenuHandler_PDA : public idMenuHandler_PDA_Interface,  public idMenuHandler
{
public:
	idMenuHandler_PDA();
	~idMenuHandler_PDA();
	
	virtual bool IsActive()
	{
		return idMenuHandler::IsActive();
	}
	virtual void ClearWidgetActionRepeater()
	{
		idMenuHandler::ClearWidgetActionRepeater();
	}
	virtual bool HandleGuiEvent( const sysEvent_t* sev )
	{
		return idMenuHandler::HandleGuiEvent( sev );
	}
	
	virtual void Update();
	virtual void ActivateMenu( bool show );
	virtual void Initialize( const char* swfFile, idSoundWorld* sw );
	
};

/*
================================================
idMenuHandler_HUD
================================================
*/
class idMenuHandler_HUD : public idMenuHandler_HUD_Interface, public idMenuHandler
{
public:
	idMenuHandler_HUD();
	~idMenuHandler_HUD();
	
	virtual bool IsActive()
	{
		return idMenuHandler::IsActive();
	}
	virtual void ClearWidgetActionRepeater()
	{
		idMenuHandler::ClearWidgetActionRepeater();
	}
	virtual bool HandleGuiEvent( const sysEvent_t* sev )
	{
		return idMenuHandler::HandleGuiEvent( sev );
	}
	
	virtual void Update();
	virtual void ActivateMenu( bool show );
	virtual void Initialize( const char* swfFile, idSoundWorld* sw );
	
	virtual idMenuScreen_HUD* GetHud();
	virtual void ShowTip( const char* title, const char* tip, bool autoHide );
	virtual void HideTip();
	virtual void SetRadioMessage( bool show );
};

/*
================================================
idMenuHandler_Scoreboard
================================================
*/
class idMenuHandler_Scoreboard : public idMenuHandler_Scoreboard_Interface, public idMenuHandler
{
public:
	idMenuHandler_Scoreboard();
	~idMenuHandler_Scoreboard();
	
	virtual bool IsActive()
	{
		return idMenuHandler::IsActive();
	}
	virtual void ClearWidgetActionRepeater()
	{
		idMenuHandler::ClearWidgetActionRepeater();
	}
	virtual bool			HandleGuiEvent( const sysEvent_t* sev )
	{
		return idMenuHandler::HandleGuiEvent( sev );
	}
	
	virtual void Update();
	virtual void ActivateMenu( bool show );
	virtual void Initialize( const char* swfFile, idSoundWorld* sw );
	virtual void UpdateScoreboard( idList< mpScoreboardInfo >& data, idStr gameInfo );
	virtual void UpdateSpectating( idStr spectate, idStr follow );
	virtual void SetTeamScores( int r, int b );
	virtual void SetActivationScreen( int screen, int trans );
	virtual void UpdateScoreboardSelection();
};


#endif //__MENUHANDLERCEGUI_H__
