cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

project(OpenTechBFG)

message(STATUS CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE})

## Compiler specific options
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  # GCC includes MinGW
  include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/gcc.cmake)
  add_definitions(-std=c++03)
  #add_definitions(-pedantic) # KORTEMIK: we perhaps should fix these some day
elseif(MSVC)
  include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/msvc.cmake)
endif() # MSVC

#if(STANDALONE)
#	add_definitions(-DSTANDALONE)
#endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/common.cmake)

## LIBRARIES

include(${CMAKE_CURRENT_SOURCE_DIR}/libraries.cmake)

## TARGETS

if(NOT UNIX) # Windows (MSVC and MinGW)
  include(${CMAKE_CURRENT_SOURCE_DIR}/windows.cmake)
else() # UNIX
  include(${CMAKE_CURRENT_SOURCE_DIR}/unix.cmake)
endif()
