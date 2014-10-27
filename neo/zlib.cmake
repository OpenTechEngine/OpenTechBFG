#libz###########################################################################

if(BUNDLED_ZLIB)
  set(ZLIB_INCLUDES
    libs/zlib/crc32.h
    libs/zlib/deflate.h
    libs/zlib/gzguts.h
    libs/zlib/inffast.h
    libs/zlib/inffixed.h
    libs/zlib/inflate.h
    libs/zlib/inftrees.h
    libs/zlib/trees.h
    libs/zlib/zconf.h
    libs/zlib/zlib.h
    libs/zlib/zutil.h)

  set(ZLIB_SOURCES
    libs/zlib/adler32.c
    libs/zlib/compress.c
    libs/zlib/crc32.c
    libs/zlib/deflate.c
    libs/zlib/gzclose.c
    libs/zlib/gzlib.c
    libs/zlib/gzread.c
    libs/zlib/gzwrite.c
    libs/zlib/infback.c
    libs/zlib/inffast.c
    libs/zlib/inflate.c
    libs/zlib/inftrees.c
    libs/zlib/trees.c
    libs/zlib/uncompr.c
    libs/zlib/zutil.c)

  include_directories(libs/zlib)
  add_library(zlib ${ZLIB_SOURCES} ${ZLIB_INCLUDES})
  set(ZLIB_LIBRARY zlib)
else()
  find_package(ZLIB REQUIRED)
  include_directories(${ZLIB_INCLUDE_DIRS})
  set(ZLIB_LIBRARY z)
endif()
