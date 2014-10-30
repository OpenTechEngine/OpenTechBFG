#libpng#########################################################################

if(BUNDLED_PNG)	
  set(PNG_INCLUDES
    png/pngconf.h
    png/png.h)

  set(PNG_SOURCES
    #png/example.c
    png/png.c
    png/pngerror.c
    png/pnggccrd.c
    png/pngget.c
    png/pngmem.c
    png/pngpread.c
    png/pngread.c
    png/pngrio.c
    png/pngrtran.c
    png/pngrutil.c
    png/pngset.c
    png/pngtrans.c
    png/pngvcrd.c
    png/pngwio.c
    png/pngwrite.c
    png/pngwtran.c
    png/pngwutil.c)

  add_library(png ${PNG_SOURCES} ${PNG_INCLUDES})
endif()

