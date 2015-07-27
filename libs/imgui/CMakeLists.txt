cmake_minimum_required(VERSION 2.8)

project(imgui)

message(STATUS CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE})

## Compiler specific options
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  # GCC includes MinGW
  add_definitions(-pipe)
  add_definitions(-mmmx -msse -msse2)
  
  add_definitions(-fno-strict-aliasing)
endif()

file(GLOB IMGUI_INCLUDES *.h)
file(GLOB IMGUI_SOURCES *.cpp)

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_INCLUDES})
