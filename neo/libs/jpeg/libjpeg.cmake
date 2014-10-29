#libjpeg########################################################################

if(BUNDLED_JPEG)
  set(JPEG_INCLUDES
    jpeg-6b/jchuff.h
    jpeg-6b/jconfig.h
    jpeg-6b/jdct.h
    jpeg-6b/jdhuff.h
    jpeg-6b/jerror.h
    jpeg-6b/jinclude.h
    jpeg-6b/jmemsys.h
    jpeg-6b/jmorecfg.h
    jpeg-6b/jpegint.h
    jpeg-6b/jpeglib.h
    jpeg-6b/jversion.h)



  set(JPEG_SOURCES
    jpeg-6b/jcapimin.c
    jpeg-6b/jcapistd.c
    jpeg-6b/jctrans.c
    jpeg-6b/jcparam.c
    jpeg-6b/jdatadst.c
    jpeg-6b/jcinit.c
    jpeg-6b/jcmaster.c
    jpeg-6b/jcmarker.c
    jpeg-6b/jcmainct.c
    jpeg-6b/jcprepct.c
    jpeg-6b/jccoefct.c
    jpeg-6b/jccolor.c
    jpeg-6b/jcsample.c
    jpeg-6b/jchuff.c
    jpeg-6b/jcphuff.c
    jpeg-6b/jcdctmgr.c
    jpeg-6b/jfdctfst.c
    jpeg-6b/jfdctflt.c
    jpeg-6b/jfdctint.c
    jpeg-6b/jdapimin.c
    jpeg-6b/jdapistd.c
    jpeg-6b/jdtrans.c
    jpeg-6b/jdatasrc.c
    jpeg-6b/jdmaster.c
    jpeg-6b/jdinput.c
    jpeg-6b/jdmarker.c
    jpeg-6b/jdhuff.c
    jpeg-6b/jdphuff.c
    jpeg-6b/jdmainct.c
    jpeg-6b/jdcoefct.c
    jpeg-6b/jdpostct.c
    jpeg-6b/jddctmgr.c
    jpeg-6b/jidctfst.c
    jpeg-6b/jidctflt.c
    jpeg-6b/jidctint.c
    jpeg-6b/jidctred.c
    jpeg-6b/jdsample.c
    jpeg-6b/jdcolor.c
    jpeg-6b/jquant1.c
    jpeg-6b/jquant2.c
    jpeg-6b/jdmerge.c
    jpeg-6b/jcomapi.c
    jpeg-6b/jutils.c
    jpeg-6b/jerror.c
    jpeg-6b/jmemmgr.c
    jpeg-6b/jmemnobs.c)

  add_library(jpeg ${JPEG_SOURCES} ${JPEG_INCLUDES})
endif()
