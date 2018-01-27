#idtools########################################################################

file(GLOB COMPILER_INCLUDES tools/compilers/*.h)

file(GLOB COMPILER_AAS_INCLUDES tools/compilers/aas/*.h)
file(GLOB COMPILER_AAS_SOURCES tools/compilers/aas/*.cpp)

file(GLOB COMPILER_DMAP_INCLUDES tools/compilers/dmap/*.h)
file(GLOB COMPILER_DMAP_SOURCES tools/compilers/dmap/*.cpp)

file(GLOB COMPILER_DFONT_INCLUDES tools/compilers/fontcomp/*.h)
file(GLOB COMPILER_DFONT_SOURCES tools/compilers/fontcomp/*.cpp)

set(TOOLS_INCLUDES tools/edit_public.h)

set(TOOLS_COMMON_INCLUDES
  tools/Tools.h)

set(TOOLS_COMMON_SOURCES
  tools/ToolGui.cpp)

file(GLOB EDITOR_INCLUDES tools/editors/*.h)
file(GLOB EDITOR_SOURCES tools/editors/*.cpp)

source_group("tools\\compilers" FILES ${COMPILER_INCLUDES})

source_group("tools\\compilers\\aas" FILES ${COMPILER_AAS_INCLUDES})
source_group("tools\\compilers\\aas" FILES ${COMPILER_AAS_SOURCES})

source_group("tools\\compilers\\dmap" FILES ${COMPILER_DMAP_INCLUDES})
source_group("tools\\compilers\\dmap" FILES ${COMPILER_DMAP_SOURCES})

source_group("tools\\compilers\\fontcomp" FILES ${COMPILER_DFONT_INCLUDES})
source_group("tools\\compilers\\fontcomp" FILES ${COMPILER_DFONT_SOURCES})

source_group("tools\\editors" FILES ${EDITOR_INCLUDES})
source_group("tools\\editors" FILES ${EDITOR_SOURCES})


set(IDTOOLS_INCLUDES
  ${TOOLS_COMMON_INCLUDES}
  ${COMPILER_INCLUDES}
  ${COMPILER_AAS_INCLUDES} # ${COMPILER_AAS_SOURCES}
  ${COMPILER_DMAP_INCLUDES} # ${COMPILER_DMAP_SOURCES}
  ${COMPILER_DFONT_INCLUDES}
  ${EDITOR_INCLUDES}
  )

set(IDTOOLS_SOURCES
  ${TOOLS_COMMON_SOURCES}
  ${COMPILER_AAS_SOURCES}
  ${COMPILER_DMAP_SOURCES}
  ${COMPILER_DFONT_SOURCES}
  ${EDITOR_SOURCES}
  )
