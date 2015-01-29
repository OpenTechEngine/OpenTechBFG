/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2014-2015 Daniel Gibson and Mikko Kortelainen (OpenTechBFG)

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

// hooks to pass engine events (key, mouse, ...) into CEGUI

#ifdef USE_CEGUI

#ifndef NEO_CEGUI_CEGUI_HOOKS_H_
#define NEO_CEGUI_CEGUI_HOOKS_H_

#include "../sys/sys_public.h"

namespace idCEGUI
{
	bool Init();

	// tell cegui that the (game) window size has changed
	void NotifyDisplaySizeChanged(int width, int height);

	// inject a sys event (keyboard, mouse, unicode character)
	bool InjectSysEvent(const BFG::sysEvent_t *keyEvent);

	// inject the current mouse wheel delta for scrolling
	bool InjectMouseWheel(int delta);

	// call this once per frame (at the end) - it'll inject the time pulse and render
	void Update();
	// TODO: or is there a good reason to update the timepulse at another time (maybe at the beginning of a frame)?
}


#endif /* NEO_CEGUI_CEGUI_HOOKS_H_ */

#endif // USE_CEGUI
