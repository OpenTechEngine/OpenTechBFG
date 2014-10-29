#minizip########################################################################

if(BUNDLED_MINIZIP)
  set(MINIZIP_INCLUDES
    zlib/minizip/ioapi.h
    zlib/minizip/unzip.h
    zlib/minizip/zip.h)

  set(MINIZIP_SOURCES
    zlib/minizip/ioapi.c
    zlib/minizip/unzip.cpp
    zlib/minizip/zip.cpp)

# bundled version uses idlibs Heap and String handling
  include_directories(
	../../neo
	../../neo/idlib
  )
  add_library(minizip ${MINIZIP_SOURCES} ${MINIZIP_INCLUDES})
endif()
