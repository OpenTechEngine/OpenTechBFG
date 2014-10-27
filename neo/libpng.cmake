#libpng#########################################################################

if(BUNDLED_PNG)	
  set(PNG_INCLUDES
    libs/png/pngconf.h
    libs/png/png.h)

  set(PNG_SOURCES
    #libs/png/example.c
    libs/png/png.c
    libs/png/pngerror.c
    libs/png/pnggccrd.c
    libs/png/pngget.c
    libs/png/pngmem.c
    libs/png/pngpread.c
    libs/png/pngread.c
    libs/png/pngrio.c
    libs/png/pngrtran.c
    libs/png/pngrutil.c
    libs/png/pngset.c
    libs/png/pngtrans.c
    libs/png/pngvcrd.c
    libs/png/pngwio.c
    libs/png/pngwrite.c
    libs/png/pngwtran.c
    libs/png/pngwutil.c)

  include_directories(libs/png)
  add_library(png ${PNG_SOURCES} ${PNG_INCLUDES})
  set(PNG_LIBRARY png)
else()
  find_package(PNG REQUIRED)
  include_directories(${PNG_INCLUDE_DIRS})
  set(PNG_LIBRARY png)
endif()
