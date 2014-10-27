#minizip########################################################################

if(BUNDLED_MINIZIP)
  set(MINIZIP_INCLUDES
    libs/zlib/minizip/ioapi.h
    libs/zlib/minizip/unzip.h
    libs/zlib/minizip/zip.h)

  set(MINIZIP_SOURCES
    libs/zlib/minizip/ioapi.c
    libs/zlib/minizip/unzip.cpp
    libs/zlib/minizip/zip.cpp)

  include_directories(libs/zlib)
  add_library(minizip ${MINIZIP_SOURCES} ${MINIZIP_INCLUDES})
  set(MINIZIP_LIBRARY minizip)
else()
  #find_package(MINIZIP REQUIRED)
  #include_directories(${MINIZIP_INCLUDE_DIRS})
  include_directories(/usr/include)
  set(MINIZIP_LIBRARY minizip)
endif()
