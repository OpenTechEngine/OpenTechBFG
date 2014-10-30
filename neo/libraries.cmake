# libjpeg
if(BUNDLED_JPEG)
  include_directories(../libs/jpeg/jpeg-6b)
else()
  find_package(JPEG REQUIRED)
  include_directories(${JPEG_INCLUDE_DIRS})
endif()
set(JPEG_LIBRARY jpeg)

# zlib and minizip
if(BUNDLED_ZLIB)
  include_directories(../libs/zlib/zlib)
  set(ZLIB_LIBRARY zlib)
else()
  find_package(ZLIB REQUIRED)
  include_directories(${ZLIB_INCLUDE_DIRS})
  include_directories(/usr/include) # for minizip
  set(ZLIB_LIBRARY z)
endif()
set(MINIZIP_LIBRARY minizip)

# libpng
if(BUNDLED_PNG)	
  include_directories(../libs/png/png)
else()
  find_package(PNG REQUIRED)
  include_directories(${PNG_INCLUDE_DIRS})
endif()
set(PNG_LIBRARY png)

# glew
if(BUNDLED_GLEW)
  add_definitions(-DGLEW_STATIC)
  include_directories(../libs/glew/glew/include)
  set(GLEW_LIBRARY glew)
else()
  find_package(GLEW REQUIRED)
  include_directories(${GLEW_INCLUDE_DIRS})
  set(GLEW_LIBRARY GLEW)
endif()
