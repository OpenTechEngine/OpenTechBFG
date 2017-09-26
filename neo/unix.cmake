


list(APPEND OpenTechBFG_SOURCES
  ${SYS_INCLUDES} ${SYS_SOURCES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

#if(UNIX)
if(FFMPEG)
  find_package(FFMPEG REQUIRED)
  add_definitions(-DUSE_FFMPEG)
  
  include_directories(${FFMPEG_INCLUDE_DIR})
  link_directories(${FFMPEG_LIBRARIES_DIRS})
endif()

if(SDL2)
  if(BUNDLED_SDL)
    include_directories(${CMAKE_SOURCE_DIR}/libs/sdl/SDL.git/include)
    link_directories(${CMAKE_BINARY_DIR}/libs/sdl/SDL.git)
    set(SDLx_LIBRARY "SDL2")
    set(SDLxMAIN_LIBRARY "SDL2main")
  else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
    set(SDLx_LIBRARY ${SDL2_LIBRARY})
  endif()
else()
  find_package(SDL REQUIRED)
  include_directories(${SDL_INCLUDE_DIR})
  set(SDLx_LIBRARY ${SDL_LIBRARY})
endif()

if(BUNDLED_CEGUI)
  # set RPATH for Unix-y systems (except for OS X), so they can find the cegui libs.
  # must be done here so it's used for both the OpenTech executable and the cegui libs
  if(UNIX AND NOT APPLE AND NOT WIN32)
    # use $ORIGIN/lib as RPATH to have a relative rpath (lib/ should always be next to the executable)
    set(CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")
    # this RPATH should be used immediately, not only after installing
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
  endif()
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  list(REMOVE_ITEM POSIX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sys/posix/platform_linux.cpp)
else()
  list(REMOVE_ITEM POSIX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sys/posix/platform_osx.cpp)
endif()

list(APPEND OpenTechBFG_SOURCES
  ${POSIX_INCLUDES} ${POSIX_SOURCES}
  ${SDL_INCLUDES} ${SDL_SOURCES})

if(OPENAL)
  add_definitions(-DUSE_OPENAL)
  if(BUNDLED_OPENAL)
    include_directories(${CMAKE_SOURCE_DIR}/libs/openal-soft/openal-soft.git/include)
  else()
    find_package(OpenAL REQUIRED)
  endif()
  set(OPENAL_LIBRARY openal)
  list(APPEND OpenTechBFG_INCLUDES ${OPENAL_INCLUDES})
  list(APPEND OpenTechBFG_SOURCES ${OPENAL_SOURCES})
else()
  list(APPEND OpenTechBFG_INCLUDES ${STUBAUDIO_INCLUDES})
  list(APPEND OpenTechBFG_SOURCES ${STUBAUDIO_SOURCES})
endif()

if(BREAKPAD)
  add_definitions(-DUSE_BREAKPAD)
  include_directories(${CMAKE_SOURCE_DIR}/libs/breakpad/breakpad.git/src)
  include_directories(${CMAKE_SOURCE_DIR}/libs/breakpad/include)
  set(BREAKPAD_LIBRARY breakpad)
  link_directories(${CMAKE_BINARY_DIR}/libs/breakpad)
endif()
#endif()

list(REMOVE_DUPLICATES OpenTechBFG_SOURCES)

GET_DIRECTORY_PROPERTY(_directory_flags DEFINITIONS)
LIST(APPEND _compiler_FLAGS ${_directory_flags})
SEPARATE_ARGUMENTS(_compiler_FLAGS)

# if("${CMAKE_SYSTEM}" MATCHES "Darwin")
if(0)
  add_executable(OpenTechEngine MACOSX_BUNDLE ${OpenTechBFG_SOURCES})
else()
  add_executable(OpenTechEngine ${OpenTechBFG_SOURCES})
endif()

if(NOT "${CMAKE_SYSTEM}" MATCHES "Darwin")
  set(RT_LIBRARY rt)
endif()

if(NOT "${CMAKE_SYSTEM}" MATCHES "FreeBSD")
  set(DL_LIBRARY dl)
endif()

target_link_libraries(OpenTechEngine
  idlib
  ${JPEG_LIBRARY}
  ${PNG_LIBRARY}
  ${ZLIB_LIBRARY}
  ${MINIZIP_LIBRARY}
  ${IRRXML_LIBRARY}
  ${GLEW_LIBRARY}
  ${OGGVORBIS_LIBRARY}
  ${OPENGL_LIBRARIES}
  pthread
  ${DL_LIBRARY}
  ${RT_LIBRARY}
  ${SDLx_LIBRARY}
  ${SDLxMAIN_LIBRARY}
  ${OPENAL_LIBRARY}
  ${BREAKPAD_LIBRARY}
  ${FFMPEG_LIBRARIES}
  ${CEGUI_LIBRARY}
  ${CEGUIGLR_LIBRARY}
  imgui
  )
#endif()

install (TARGETS OpenTechEngine RUNTIME DESTINATION bin COMPONENT OpenTechEngine)
