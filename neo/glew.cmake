#glew###########################################################################

if(BUNDLED_GLEW)
  set(GLEW_INCLUDES
      libs/glew/include/GL/glew.h)

  if(WIN32)
      set(GLEW_INCLUDES ${GLEW_INCLUDES} libs/glew/include/GL/wglew.h)
  else()
      set(GLEW_INCLUDES ${GLEW_INCLUDES} libs/glew/include/GL/glxew.h)
  endif()

  set(GLEW_SOURCES
      libs/glew/src/glew.c)

  include_directories(libs/glew/include)
  add_library(glew ${GLEW_SOURCES} ${GLEW_INCLUDES})
  set(GLEW_LIBRARY glew)

  add_definitions(-DGLEW_STATIC)
else()
  find_package(GLEW REQUIRED)
  include_directories(${GLEW_INCLUDE_DIRS})
  set(GLEW_LIBRARY GLEW)
endif()
