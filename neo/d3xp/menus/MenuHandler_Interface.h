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
#ifndef __MENUHANDLERINTERFACE_H__
#define __MENUHANDLERINTERFACE_H__

#include "../sys/sys_session.h" // for voiceStateDisplay_t

#include "../d3xp/menus/MenuState.h"

class mpScoreboardInfo;
class idSoundWorld;
class idMenuScreen_HUD;

/*
================================================
idMenuHandler_Interface
================================================
*/
class idMenuHandler_Interface
{
public:
	virtual					~idMenuHandler_Interface() {};
	
	virtual bool IsActive() = 0;
	virtual void ClearWidgetActionRepeater() = 0;
	virtual bool HandleGuiEvent( const sysEvent_t* sev ) = 0;
};

/*
================================================
idMenuHandler_Shell_Interface
================================================
 */
class idMenuHandler_Shell_Interface : public virtual idMenuHandler_Interface
{
public:
	virtual ~idMenuHandler_Shell_Interface() {};
	virtual void Update() = 0;
	virtual void ActivateMenu( bool show ) = 0;
	virtual void Initialize( const char* swfFile, idSoundWorld* sw ) = 0;
	virtual bool HandleGuiEvent( const sysEvent_t* sev ) = 0;
	
	virtual void UpdateSavedGames() = 0;
	virtual void SetShellState( shellState_t s ) = 0;
	virtual void SetNextScreen( int screen, int trans ) = 0;

	virtual void SetInGame( bool val ) = 0;
	virtual void UpdateLeaderboard( const idLeaderboardCallback* callback ) = 0;
	virtual void SetCanContinue( bool valid ) = 0;
	virtual void SetGameComplete() = 0;
	virtual bool GetGameComplete() = 0;
	virtual void SetTimeRemaining( int time ) = 0;
};

/*
================================================
idMenuHandler_PDA_Interface
================================================
*/
class idMenuHandler_PDA_Interface : public virtual idMenuHandler_Interface
{
public:
	virtual ~idMenuHandler_PDA_Interface() {};
	
	virtual void			Update() = 0;
	virtual void			ActivateMenu( bool show ) = 0;
	virtual void			Initialize( const char* swfFile, idSoundWorld* sw ) = 0;
};

/*
================================================
idMenuHandler_HUD_Interface
================================================
*/
class idMenuHandler_HUD_Interface : public virtual idMenuHandler_Interface
{
public:
	virtual ~idMenuHandler_HUD_Interface() {};
	
	virtual void			Update() = 0;
	virtual void			ActivateMenu( bool show ) = 0;
	virtual void			Initialize( const char* swfFile, idSoundWorld* sw ) = 0;
	
	virtual idMenuScreen_HUD* GetHud() = 0;
	virtual void			ShowTip( const char* title, const char* tip, bool autoHide ) = 0;
	virtual void					HideTip() = 0;
	virtual void					SetRadioMessage( bool show ) = 0;
};

/*
================================================
idMenuHandler_Scoreboard_Interface
================================================
*/
class idMenuHandler_Scoreboard_Interface : public virtual idMenuHandler_Interface
{
public:
	virtual ~idMenuHandler_Scoreboard_Interface() {};
	
	virtual void			Update() = 0;
	virtual void			ActivateMenu( bool show ) = 0;
	virtual void			Initialize( const char* swfFile, idSoundWorld* sw ) = 0;
	virtual void					UpdateScoreboard( idList< mpScoreboardInfo >& data, idStr gameInfo ) = 0;
	virtual void					UpdateSpectating( idStr spectate, idStr follow ) = 0;
	virtual void					SetTeamScores( int r, int b ) = 0;
	virtual void					SetActivationScreen( int screen, int trans ) = 0;
	virtual void					UpdateScoreboardSelection() = 0;
};


#endif //__MENUHANDLERINTERFACE_H__
