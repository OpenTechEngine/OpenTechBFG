#irrxml#########################################################################

file(GLOB IRRXML_INCLUDES libs/irrxml/src/*.h)
file(GLOB IRRXML_SOURCES libs/irrxml/src/*.cpp)

if(BUNDLED_IRRXML)
  add_library(irrxml ${IRRXML_SOURCES} ${IRRXML_INCLUDES})
  set(IRRXML_LIBRARY irrxml)
endif()
