#libjpeg########################################################################

if(BUNDLED_JPEG)
  set(JPEG_INCLUDES
    libs/jpeg-6b/jchuff.h
    libs/jpeg-6b/jconfig.h
    libs/jpeg-6b/jdct.h
    libs/jpeg-6b/jdhuff.h
    libs/jpeg-6b/jerror.h
    libs/jpeg-6b/jinclude.h
    libs/jpeg-6b/jmemsys.h
    libs/jpeg-6b/jmorecfg.h
    libs/jpeg-6b/jpegint.h
    libs/jpeg-6b/jpeglib.h
    libs/jpeg-6b/jversion.h)



  set(JPEG_SOURCES
    libs/jpeg-6b/jcapimin.c
    libs/jpeg-6b/jcapistd.c
    libs/jpeg-6b/jctrans.c
    libs/jpeg-6b/jcparam.c
    libs/jpeg-6b/jdatadst.c
    libs/jpeg-6b/jcinit.c
    libs/jpeg-6b/jcmaster.c
    libs/jpeg-6b/jcmarker.c
    libs/jpeg-6b/jcmainct.c
    libs/jpeg-6b/jcprepct.c
    libs/jpeg-6b/jccoefct.c
    libs/jpeg-6b/jccolor.c
    libs/jpeg-6b/jcsample.c
    libs/jpeg-6b/jchuff.c
    libs/jpeg-6b/jcphuff.c
    libs/jpeg-6b/jcdctmgr.c
    libs/jpeg-6b/jfdctfst.c
    libs/jpeg-6b/jfdctflt.c
    libs/jpeg-6b/jfdctint.c
    libs/jpeg-6b/jdapimin.c
    libs/jpeg-6b/jdapistd.c
    libs/jpeg-6b/jdtrans.c
    libs/jpeg-6b/jdatasrc.c
    libs/jpeg-6b/jdmaster.c
    libs/jpeg-6b/jdinput.c
    libs/jpeg-6b/jdmarker.c
    libs/jpeg-6b/jdhuff.c
    libs/jpeg-6b/jdphuff.c
    libs/jpeg-6b/jdmainct.c
    libs/jpeg-6b/jdcoefct.c
    libs/jpeg-6b/jdpostct.c
    libs/jpeg-6b/jddctmgr.c
    libs/jpeg-6b/jidctfst.c
    libs/jpeg-6b/jidctflt.c
    libs/jpeg-6b/jidctint.c
    libs/jpeg-6b/jidctred.c
    libs/jpeg-6b/jdsample.c
    libs/jpeg-6b/jdcolor.c
    libs/jpeg-6b/jquant1.c
    libs/jpeg-6b/jquant2.c
    libs/jpeg-6b/jdmerge.c
    libs/jpeg-6b/jcomapi.c
    libs/jpeg-6b/jutils.c
    libs/jpeg-6b/jerror.c
    libs/jpeg-6b/jmemmgr.c
    libs/jpeg-6b/jmemnobs.c)
  include_directories(libs/jpeg-6b)
  add_library(jpeg ${JPEG_SOURCES} ${JPEG_INCLUDES})
  set(JPEG_LIBRARY jpeg)
else()
  find_package(JPEG REQUIRED)
  include_directories(${JPEG_INCLUDE_DIRS})
  set(JPEG_LIBRARY jpeg)
endif()
