#glew###########################################################################

if(BUNDLED_GLEW)
  set(GLEW_INCLUDES
    glew/include/GL/glew.h)

  if(WIN32)
    set(GLEW_INCLUDES ${GLEW_INCLUDES} glew/include/GL/wglew.h)
  else()
    set(GLEW_INCLUDES ${GLEW_INCLUDES} glew/include/GL/glxew.h)
  endif()

  set(GLEW_SOURCES
    glew/src/glew.c)

  add_library(glew ${GLEW_SOURCES} ${GLEW_INCLUDES})
endif()
