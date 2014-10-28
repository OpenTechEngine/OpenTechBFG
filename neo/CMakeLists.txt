cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project(OpenTechEngine)

################################################################################

option(USE_MFC_TOOLS
  "Compile the built-in MFC based tools" OFF)

option(MONOLITH
  "Embed game logic into main executable" ON)

option(SDL2
  "Use SDL2 instead of SDL1.2" OFF)

option(OPENAL
  "Use OpenAL soft instead of XAudio2" ON)

option(FFMPEG
  "Use FMPEG to render Bink videos" OFF)

option(IDTOOLS
  "Compile the built-in game tools" ON)

#options########################################################################

# FIXME: should autodetect if there is a version available by CMake and use that if yes?

option(BUNDLED_JPEG
  "Use bundled libjpeg" ON)

option(BUNDLED_PNG
  "Use bundled libpng" ON)

option(BUNDLED_ZLIB
  "Use bundled zlib" ON)

option(BUNDLED_MINIZIP
  "Use bundled minizip" ON)

option(BUNDLED_IRRXML
  "Use bundled irrxml" OFF)

option(BUNDLED_GLEW
  "Use bundled glew" ON)

option(BUNDLED_FREETYPE
  "Use bundled freetype" OFF)

option(BUNDLED_OGGVORBIS
  "Use bundled oggvorbis" OFF)

################################################################################

message(STATUS CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE})

## Compiler specific options
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  # GCC includes MinGW
  include(${CMAKE_CURRENT_SOURCE_DIR}/gcc.cmake)
elseif(MSVC)
  include(${CMAKE_CURRENT_SOURCE_DIR}/msvc.cmake)
endif() # MSVC

#if(STANDALONE)
#	add_definitions(-DSTANDALONE)
#endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/common.cmake)

## TARGETS

if(NOT UNIX) # Windows (MSVC and MinGW)
  include(${CMAKE_CURRENT_SOURCE_DIR}/windows.cmake)
else() # UNIX
  include(${CMAKE_CURRENT_SOURCE_DIR}/unix.cmake)
endif()
