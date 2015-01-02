#libz###########################################################################

if(BUNDLED_ZLIB)
  set(ZLIB_INCLUDES
    zlib/crc32.h
    zlib/deflate.h
    zlib/gzguts.h
    zlib/inffast.h
    zlib/inffixed.h
    zlib/inflate.h
    zlib/inftrees.h
    zlib/trees.h
    zlib/zconf.h
    zlib/zlib.h
    zlib/zutil.h)

  set(ZLIB_SOURCES
    zlib/adler32.c
    zlib/compress.c
    zlib/crc32.c
    zlib/deflate.c
    zlib/gzclose.c
    zlib/gzlib.c
    zlib/gzread.c
    zlib/gzwrite.c
    zlib/infback.c
    zlib/inffast.c
    zlib/inflate.c
    zlib/inftrees.c
    zlib/trees.c
    zlib/uncompr.c
    zlib/zutil.c)
	
  add_library(zlib ${ZLIB_SOURCES} ${ZLIB_INCLUDES})
  
  if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wno-implicit-function-declaration)
  endif()
  
endif()
