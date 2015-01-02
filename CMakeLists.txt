cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

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
  
option(BUNDLED_OPENAL
  "Use bundled openal" OFF)

option(BUNDLED_SDL
  "Use bundled SDL" OFF)

  
################################################################################

message(STATUS CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE})

###############

# libjpeg
if(BUNDLED_JPEG)
  add_subdirectory(libs/jpeg)
endif()

# zlib and minizip
if(BUNDLED_ZLIB)
  add_subdirectory(libs/zlib)
endif()

# libpng
if(BUNDLED_PNG)	
  add_subdirectory(libs/png)
endif()

# glew
if(BUNDLED_GLEW)
  add_subdirectory(libs/glew)
endif()

# openal
if(BUNDLED_OPENAL)
  add_subdirectory(libs/openal)
endif()

# openal
if(BUNDLED_SDL)
  add_subdirectory(libs/sdl)
endif()
####

add_subdirectory(neo)
