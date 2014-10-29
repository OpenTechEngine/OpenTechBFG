cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake/modules)

project(oggvorbis)

message(STATUS CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE})

## Compiler specific options
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  # GCC includes MinGW
  include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/gcc.cmake)
elseif(MSVC)
  include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/msvc.cmake)
endif() # MSVC

include(oggvorbis.cmake)
