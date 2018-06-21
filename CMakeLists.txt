cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

project(OpenTechEngine)

################################################################################

option(USE_MFC_TOOLS
  "Compile the built-in MFC based tools" OFF)

option(MONOLITH
  "Embed game logic into main executable" ON)

option(SDL2
  "Use SDL2 instead of SDL1.2" ON)
  
option(RAPIDXML
  "use RapidXML" ON)

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

if((WIN32 AND (CMAKE_COMPILER_IS_GNUCC OR NOT $ENV{VSINSTALLDIR})) OR
${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # breakpad doesn't work on mingw out of the box
  # and it requires DIA SDK which is under VSINSTALLDIR
  option(BREAKPAD
    "Use breakpad" OFF)
else()
  option(BREAKPAD
    "Use breakpad" ON)
endif()

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
  "Use bundled openal" OFF)

if(NOT MSVC)
  # on other platforms we must use openal because they don't have xaudio - and mingw is missing XAudio2.h
  # FIXME: can we somehow have it default to OFF on windows and ON everywhere else?
  set(BUNDLED_OPENAL TRUE)
endif()

option(BUNDLED_SDL
  "Use bundled SDL" OFF)
  
option(BUNDLED_RAPIDXML
  "Use bundled RapidXML" ON)

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
  add_subdirectory(libs/openal-soft)
endif()

# sdl
if(BUNDLED_SDL)
#  add_subdirectory(libs/sdl)
endif()

# RapidXML
if(BUNDLED_RAPIDXML)
  add_subdirectory(libs/rapidxml)
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

# breakpad
if(BREAKPAD)
  add_subdirectory(libs/breakpad)
endif()

####

# imgui is always bundled
add_subdirectory(libs/imgui)

add_subdirectory(neo)

#### install and packaging

if(UNIX)
  install(DIRECTORY "base" DESTINATION "bin" COMPONENT Assets)
elseif(WIN32)
  install(DIRECTORY "base" DESTINATION "." COMPONENT Assets)
else()
  install(DIRECTORY "base" DESTINATION "bin" COMPONENT Assets)
endif()

#### create symlinks for unix so game can be run from build
if(UNIX)
  add_custom_target(
    "OpenTechEngine_symlinks" ALL
    COMMAND ln -sf "${CMAKE_SOURCE_DIR}/base" "${CMAKE_BINARY_DIR}/base"
    COMMAND ln -sf "${CMAKE_SOURCE_DIR}/base" "${CMAKE_BINARY_DIR}/neo/base"
    COMMAND ln -sf "${CMAKE_BINARY_DIR}/neo/OpenTechEngine" "${CMAKE_BINARY_DIR}/OpenTechEngine"
    )
  if(BUNDLED_CEGUI)
    add_custom_target(
      "CEGUI_lib_symlinks" ALL
      COMMAND ln -sf "${CMAKE_BINARY_DIR}/libs/cegui/CEGUI.git/lib" "${CMAKE_BINARY_DIR}/lib"
      )
  endif()
endif()

# cpack
include(${CMAKE_CURRENT_SOURCE_DIR}/CPackConfig.cmake)
include(CPack)
