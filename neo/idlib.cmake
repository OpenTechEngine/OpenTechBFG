#idlib##########################################################################

file(GLOB ID__INCLUDES idlib/*.h)
file(GLOB ID__SOURCES idlib/*.cpp)

file(GLOB ID_BV_INCLUDES idlib/bv/*.h)
file(GLOB ID_BV_SOURCES idlib/bv/*.cpp)

file(GLOB ID_CONTAINERS_INCLUDES idlib/containers/*.h)
file(GLOB ID_CONTAINERS_SOURCES idlib/containers/*.cpp)

file(GLOB ID_GEOMETRY_INCLUDES idlib/geometry/*.h)
file(GLOB ID_GEOMETRY_SOURCES idlib/geometry/*.cpp)

file(GLOB ID_HASHING_INCLUDES idlib/hashing/*.h)
file(GLOB ID_HASHING_SOURCES idlib/hashing/*.cpp)

file(GLOB ID_MATH_INCLUDES idlib/math/*.h)
file(GLOB ID_MATH_SOURCES idlib/math/*.cpp)

file(GLOB ID_SYS_INCLUDES idlib/sys/*.h)
file(GLOB ID_SYS_SOURCES idlib/sys/*.cpp)

if(UNIX)
  file(GLOB ID_SYS_POSIX_INCLUDES idlib/sys/posix/*.h)
  file(GLOB ID_SYS_POSIX_SOURCES idlib/sys/posix/*.cpp)
elseif(WIN32)
  file(GLOB ID_SYS_WIN32_INCLUDES idlib/sys/win32/*.h)
  file(GLOB ID_SYS_WIN32_SOURCES idlib/sys/win32/*.cpp)
else()
  message(FATAL_ERROR, "Unsupported platform!")
endif()

set(ID_INCLUDES_ALL
  ${ID__INCLUDES}
  ${ID_BV_INCLUDES}
  ${ID_CONTAINERS_INCLUDES}
  ${ID_GEOMETRY_INCLUDES}
  ${ID_HASHING_INCLUDES}
  ${ID_MATH_INCLUDES}
  ${ID_SYS_INCLUDES}
  )

set(ID_SOURCES_ALL
  ${ID__SOURCES}
  ${ID_BV_SOURCES}
  ${ID_CONTAINERS_SOURCES}
  ${ID_GEOMETRY_SOURCES}
  ${ID_HASHING_SOURCES}
  ${ID_MATH_SOURCES}
  ${ID_SYS_SOURCES}
  )

if(UNIX)
  list(APPEND ID_INCLUDES_ALL ${ID_SYS_POSIX_INCLUDES})
  list(APPEND ID_SOURCES_ALL ${ID_SYS_POSIX_SOURCES})
elseif(WIN32)
  list(APPEND ID_INCLUDES_ALL ${ID_SYS_WIN32_INCLUDES})
  list(APPEND ID_SOURCES_ALL ${ID_SYS_WIN32_SOURCES})
else()
  message(FATAL_ERROR, "Unsupported platform!")
endif()

source_group("idlib" FILES ${ID__INCLUDES})
source_group("idlib" FILES ${ID__SOURCES})
source_group("idlib_bv" FILES ${ID_BV_INCLUDES})
source_group("idlib_bv" FILES ${ID_BV_SOURCES})
source_group("idlib_containers" FILES ${ID_CONTAINERS_INCLUDES})
source_group("idlib_containers" FILES ${ID_CONTAINERS_SOURCES})
source_group("idlib_geometry" FILES ${ID_GEOMETRY_INCLUDES})
source_group("idlib_geometry" FILES ${ID_GEOMETRY_SOURCES})
source_group("idlib_hashing" FILES ${ID_HASHING_INCLUDES})
source_group("idlib_hashing" FILES ${ID_HASHING_SOURCES})
source_group("idlib_math" FILES ${ID_MATH_INCLUDES})
source_group("idlib_math" FILES ${ID_MATH_SOURCES})
source_group("idlib_sys" FILES ${ID_SYS_INCLUDES})
source_group("idlib_sys" FILES ${ID_SYS_SOURCES})

if(UNIX)
  source_group("idlib_sys\\posix" FILES ${ID_SYS_POSIX_INCLUDES})
  source_group("idlib_sys\\posix" FILES ${ID_SYS_POSIX_SOURCES})
elseif(WIN32)
  source_group("idlib_sys\\win32" FILES ${ID_SYS_WIN32_INCLUDES})
  source_group("idlib_sys\\win32" FILES ${ID_SYS_WIN32_SOURCES})
else()
  message(FATAL_ERROR, "Unsupported platform!")
endif()

add_library(idlib ${ID_SOURCES_ALL} ${ID_INCLUDES_ALL})

#libraries######################################################################
