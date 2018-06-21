#rapidxml#######################################################################

if(BUNDLED_RAPIDXML)

  set(RAPIDXML_SOURCES
    rapidxml-1.13/rapidxml.hpp
    rapidxml-1.13/rapidxml_utils.hpp
    rapidxml-1.13/rapidxml_print.hpp
    rapidxml-1.13/rapidxml_iterators.hpp)

  #add_definitions(-DRAPIDXML_STATIC)
  #add_library(rapidxml ${RAPIDXML_SOURCES} ${RAPIDXML_INCLUDES})
  add_library(rapidxml ${RAPIDXML_SOURCES})
  set_target_properties(rapidxml PROPERTIES LINKER_LANGUAGE CXX)
endif()
