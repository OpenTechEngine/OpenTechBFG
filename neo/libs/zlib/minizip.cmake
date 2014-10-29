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

  add_library(minizip ${MINIZIP_SOURCES} ${MINIZIP_INCLUDES})
endif()
