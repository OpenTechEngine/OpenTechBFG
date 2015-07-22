/*
 * Wrapper for CEGUI/CEGUI.h to prevent some name collusions between d3bfg macros
 * and cegui/c++ headers and to suppress some warnings (e.g. about missing virtual
 * destructors) in the cegui headers.
 *
 * (C) 2015 Daniel Gibson, do whatever you want with this file.
 */

#ifndef NEO_CEGUI_WRAP_CEGUI_H_
#define NEO_CEGUI_WRAP_CEGUI_H_

#ifdef USE_CEGUI

// gcc and clang - ignore some warnings in cegui code
#ifdef __GNUC__
#pragma GCC diagnostic push // save old warning settings
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor" // yeah, this might be bad, but we're not gonna change their code
#pragma GCC diagnostic ignored "-Wundef" // (clan)g++ doesn't define __STDC_VERSION__, whatever.
#endif // __GNUC__

// ****************************************************************************
// get rid of some macros that collide with symbols used by cegui (or headers included by it)

#pragma push_macro("strcmp") // "save" current strcmp #define
#undef strcmp // remove that #define so <cstring> included by cegui doesn't fuck up

#pragma push_macro("strncmp")
#undef strncmp

#pragma push_macro("strcasecmp")
#undef strcasecmp

#pragma push_macro("strnicmp")
#undef strnicmp

#pragma push_macro("_mm_nmsub_ps")
#undef _mm_nmsub_ps

#pragma push_macro("assert")
#undef assert

// ****************************************************************************

// look: the actual include!
#include <cassert>
#include <CEGUI/CEGUI.h>


// ****************************************************************************
// restore the d3bfg macros

#pragma pop_macro("strcmp") // restore d3bfg  strcmp #define
#pragma pop_macro("strncmp")
#pragma pop_macro("strcasecmp")
#pragma pop_macro("strnicmp")
#pragma pop_macro("_mm_nmsub_ps")
#pragma pop_macro("assert")

// ****************************************************************************

// gcc/clang: restore old warning settings
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif // __GNUC__


#endif // USE_CEGUI

#endif /* NEO_CEGUI_WRAP_CEGUI_H_ */
