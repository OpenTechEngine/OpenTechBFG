
add_definitions(-pipe)
add_definitions(-std=c++03)

#add_definitions(-pedantic) 
add_definitions(-mmmx -msse -msse2)

# https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html#C_002b_002b-Dialect-Options

## Functionality
add_definitions(-fno-strict-aliasing)
#add_definitions(-fvtable-verify=preinit)
add_definitions(-fwrapv)
# add_definitions(-ftrapv) # do we really wanna forbid signed int overflows? breaks code in subtle ways..

## Warnings
# Enabling, the order is important
add_definitions(-Wall)
# add_definitions(-Wextra)
add_definitions(-Wundef)
add_definitions(-Winvalid-pch)
add_definitions(-Wpointer-arith)
add_definitions(-Werror=format-security)
add_definitions(-Werror=format)
add_definitions(-Wdelete-non-virtual-dtor)
add_definitions(-Wnon-virtual-dtor)
add_definitions(-Wctor-dtor-privacy)
#add_definitions(-Wold-style-cast)
add_definitions(-Wsign-promo)
add_definitions(-Wliteral-suffix)
add_definitions(-Wnarrowing)
add_definitions(-Wnoexcept)
add_definitions(-Wreorder)
add_definitions(-Wstrict-null-sentinel)
add_definitions(-Woverloaded-virtual)

#add_definitions(-Wfloat-equal)
#add_definitions(-Wcast-align)
#add_definitions(-Wstrict-prototypes)
#add_definitions(-Wstrict-overflow=5)
#add_definitions(-Wwrite-strings)
#add_definitions(-Waggregate-return)
#add_definitions(-Wcast-qual)
#add_definitions(-Wswitch-default)
#add_definitions(-Wswitch-enum)
#add_definitions(-Wconversion)
#add_definitions(-Wunreachable-code)

#add_definitions(-Weffc++)

# Disabling problematic ones
add_definitions(-Wno-unknown-pragmas)
add_definitions(-Wno-switch)
add_definitions(-Wno-sign-compare)
add_definitions(-Wno-invalid-offsetof)

# FIXME: at some point we should just clean up the unused crap!
add_definitions(-Wno-unused-local-typedefs)
add_definitions(-Wno-unused-function)
add_definitions(-Wno-unused-variable)
add_definitions(-Wno-unused-but-set-variable)
add_definitions(-Wno-unused-value) # a were set for debugging?


if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
  # append clang-specific settings for warnings (the second one make sure clang doesn't complain
  # about unknown -W flags, like -Wno-unused-but-set-variable)
  add_definitions(-Wno-unknown-warning-option)
  add_definitions(-Wno-inline-new-delete)
  add_definitions(-Wno-local-type-template-args)
  
  # FIXME: at some point we should just clean up the unused crap!
  add_definitions(-Wno-unused-private-field)

  # prevent png.h including setjmp.h as same declarations are found on pthread.h
  add_definitions(-DPNG_SKIP_SETJMP_CHECK)
endif()

if(MINGW) # MinGW, 32 and 64bit
  # require msvcr70.dll or newer for _aligned_malloc etc
  # I think it is from Visual C++ .NET 2002, so it should be available on any remotely modern system.
  add_definitions(-D__MSVCRT_VERSION__=0x0700)
  add_definitions(-D__USE_MINGW_ANSI_STDIO=1)
endif()	# WIN32

#if(NOT ANDROID)
add_definitions(-DUSE_EXCEPTIONS)
#endif()


set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG -O0 -ggdb ")
#set(CMAKE_C_FLAGS_DEBUGALL "${CMAKE_C_FLAGS_DEBUGALL} -g -ggdb -D_DEBUG")
#set(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_PROFILE} -g -ggdb -D_DEBUG -O1 -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math -fno-unsafe-math-optimizations -fomit-frame-pointer")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -ggdb -O3 -ffast-math -fno-unsafe-math-optimizations -fomit-frame-pointer")
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -Os -ffast-math -fno-unsafe-math-optimizations -fomit-frame-pointer")

set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
#set(CMAKE_CXX_FLAGS_DEBUGALL ${CMAKE_C_FLAGS_DEBUGALL})
#set(CMAKE_CXX_FLAGS_PROFILE ${CMAKE_C_FLAGS_PROFILE})
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO})
set(CMAKE_CXX_FLAGS_MINSIZEREL ${CMAKE_C_FLAGS_MINSIZEREL})
