cmake_minimum_required(VERSION 2.8)

project(imgui)

message(STATUS CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE})

## Compiler specific options
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  # GCC includes MinGW
  add_definitions(-pipe)
  add_definitions(-mmmx -msse -msse2)
  
  add_definitions(-fno-strict-aliasing)

  if(MINGW)
    # otherwise imgui will try to use ime32 functions and linking against ime32 seems to  fail
    # we don't need IME in the tools anyway.
    add_definitions(-DIMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCS)
  endif()

elseif(MSVC) # TODO: or Windows in general?

  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /D _DEBUG /MP /MTd")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MP /Oi /Oy /MT")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /MP /Oi /MTd")
  set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} /MP /Oi /Oy /MT")
  
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP /MTd")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP /Oi /Oy /MT")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MP /MTd")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MP /Oi /Oy /MT")
  
  # RB: without /SAFESEH:NO we can't link against ffmpeg libs and VS2013 or we have to build our own
  # libs for newer compilers
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
  set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} /SAFESEH:NO")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SAFESEH:NO")
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} /SAFESEH:NO")
  
endif()

file(GLOB IMGUI_INCLUDES *.h)
file(GLOB IMGUI_SOURCES *.cpp)

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_INCLUDES})
