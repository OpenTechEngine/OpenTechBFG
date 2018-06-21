# libjpeg
if(BUNDLED_JPEG)
  include_directories(../libs/jpeg/libjpeg-turbo-1.3.1)
else()
  find_package(JPEG REQUIRED)
  include_directories(${JPEG_INCLUDE_DIRS})
endif()
set(JPEG_LIBRARY jpeg)

# zlib and minizip
if(BUNDLED_ZLIB)
  include_directories(../libs/zlib/zlib)
  set(ZLIB_LIBRARY zlib)
else()
  find_package(ZLIB REQUIRED)
  include_directories(${ZLIB_INCLUDE_DIRS})
  include_directories(/usr/include) # for minizip
  set(ZLIB_LIBRARY z)
endif()
set(MINIZIP_LIBRARY minizip)

# libpng
if(BUNDLED_PNG)	
  include_directories(../libs/png/png)
else()
  find_package(PNG REQUIRED)
  include_directories(${PNG_INCLUDE_DIRS})
endif()
set(PNG_LIBRARY png)

# glew
if(BUNDLED_GLEW)
  add_definitions(-DGLEW_STATIC)
  include_directories(../libs/glew/glew/include)
  set(GLEW_LIBRARY glew)
else()
  find_package(GLEW REQUIRED)
  include_directories(${GLEW_INCLUDE_DIRS})
  set(GLEW_LIBRARY GLEW)
endif()

# openal
if(BUNDLED_OPENAL)	
  include_directories(../libs/openal/openal-soft.git/include)
  set(OPENAL_LIBRARY ../libs/openal/openal-soft.git/lib/openal.a) # need to check where it builds to
else()
# TODO: OS specific code handles currently, should we have it here?
endif()


# sdl
if(BUNDLED_SDL)	
  include_directories(../libs/sdl/SDL.git/include)
  set(SDLx_LIBRARY ../libs/sdl/SDL.git/lib/SDL2.a) # need to check where it builds to
else()
# TODO: OS specific code handles currently, should we have it here?
endif()

# rapidXML
if(BUNDLED_RAPIDXML)
  #add_definitions(-DGLEW_STATIC)
  #include_directories(../libs/rapidxml/rapidxml-1.13)
  set(RAPIDXML_LIBRARY rapidxml)
else()
  #find_package(RAPIDXML REQUIRED)
  #find_package(rapidXML REQUIRED)
  find_package(librapidxml REQUIRED)
  #include_directories(${RAPIDXML_INCLUDE_DIRS})
  set(RAPIDXML_LIBRARY RAPIDXML)
endif()

if(CEGUI)
  add_definitions(-DUSE_CEGUI)

  if(BUNDLED_CEGUI)
    set(CEGUI_LIBRARY CEGUIBase-0)
    set(CEGUIGLR_LIBRARY CEGUIOpenGLRenderer-0)
    include_directories(${CMAKE_BINARY_DIR}/libs/cegui/CEGUI.git/cegui/include) # cegui installs Config here
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/cegui/CEGUI.git/cegui/include)
    link_directories(${CMAKE_BINARY_DIR}/lib) # cegui installs libs here
  else()
    find_package(CEGUI REQUIRED)
    include_directories(${CEGUI_INCLUDE_DIRS})
    set(CEGUI_LIBRARY CEGUIBase)
    set(CEGUIGLR_LIBRARY CEGUIOpenGLRenderer)
  endif()
endif()
