cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

project(OpenTechEngine LANGUAGES CXX C)

################################################################################

option(USE_MFC_TOOLS
  "Compile the built-in MFC based tools" OFF)

option(MONOLITH
  "Embed game logic into main executable" ON)

option(SDL2
  "Use SDL2 instead of SDL1.2" OFF)

option(OPENAL
  "Use OpenAL soft instead of XAudio2" OFF)

if(NOT MSVC)
  # on other platforms we must use openal because they don't have xaudio - and mingw is missing XAudio2.h
  # FIXME: can we somehow have it default to OFF on windows and ON everywhere else?
  set(OPENAL TRUE)
endif()

option(FFMPEG
  "Use FMPEG to render Bink videos" OFF)

option(IDTOOLS
  "Compile the built-in game tools" ON)

option(CEGUI
  "Use cegui" ON)

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

option(BUNDLED_OGGVORBIS
  "Use bundled oggvorbis" OFF)
  
option(BUNDLED_OPENAL
  "Use bundled openal")

option(BUNDLED_SDL
  "Use bundled SDL" OFF)

option(BUNDLED_CEGUI
  "Use bundled CEGUI" ON)

  
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

# oggvorbis
if(BUNDLED_OGGVORBIS)
  add_subdirectory(libs/oggvorbis)
endif()

# openal
if(BUNDLED_OPENAL)
#  add_subdirectory(libs/openal)
endif()

# sdl
if(BUNDLED_SDL)
#  add_subdirectory(libs/sdl)
endif()

# cegui
if(BUNDLED_CEGUI)

  # freetype, if not found, we build ours
  find_package(Freetype)
  
  if(NOT FREETYPE_FOUND)
    add_subdirectory(libs/freetype)
    set(BUNDLED_FREETYPE ON CACHE BOOL "Select BUNDLED_FREETYPE for cegui" FORCE)
  endif()
  
  add_subdirectory(libs/cegui)
endif()

####

add_subdirectory(neo)

# cpack
set(CPACK_PACKAGE_NAME "OpenTechBFG")
set(CPACK_PACKAGE_VENDOR "OpenTechEngine")
set(CPACK_PACKAGE_CONTACT "https://github.com/OpenTechEngine/OpenTechBFG")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Engine based on Doom 3 BFG aiming to allow the creation of standalone games")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "/opt/OpenTechEngine/OpenTechBFG")

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(CPACK_GENERATOR RPM DEB)
  set(CPACK_DEB_COMPONENT_INSTALL ON)
  set(CPACK_RPM_COMPONENT_INSTALL ON)
  set(CPACK_COMPONENTS_ALL OpenTechEngine)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  set(CPACK_GENERATOR BUNDLE)
  set(CPACK_BUNDLE_COMPONENT_INSTALL ON)
  set(CPACK_COMPONENTS_ALL OpenTechEngine)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(CPACK_GENERATOR NSIS)
  set(CPACK_NSIS_COMPONENT_INSTALL ON)
  set(CPACK_COMPONENTS_ALL OpenTechEngine)
else()
  set(CPACK_GENERATOR TGZ)
  set(CPACK_TGZ_COMPONENT_INSTALL ON)
  set(CPACK_COMPONENTS_ALL OpenTechEngine)
endif()



include(CPack)
