add_definitions(-pipe)
#add_definitions(-Wall)
#add_definitions(-std=gnu++11)
add_definitions(-std=c++03)
#add_definitions(-pedantic)
add_definitions(-Werror=format-security)
add_definitions(-Werror=format)
add_definitions(-mmmx -msse -msse2)

add_definitions(-ftrapv)
# add_definitions(-Wextra)
# add_definitions(-Wfloat-equal)
add_definitions(-Wundef)
add_definitions(-Wpointer-arith)
add_definitions(-Wcast-align)
# add_definitions(-Wstrict-prototypes)
# add_definitions(-Wstrict-overflow=5)
# add_definitions(-Wwrite-strings)
# add_definitions(-Waggregate-return)
# add_definitions(-Wcast-qual)
# add_definitions(-Wswitch-default)
# add_definitions(-Wswitch-enum)
# add_definitions(-Wconversion)
# add_definitions(-Wunreachable-code)

if(NOT UNIX) # MinGW
  # require msvcr70.dll or newer for _aligned_malloc etc
  # I think it is from Visual C++ .NET 2002, so it should be available on any remotely modern system.
  add_definitions(-D__MSVCRT_VERSION__=0x0700)
  
#  find_package(DirectX REQUIRED) # KORTEMIK TEMP
#  include_directories(libs/mingw-hacks)
#  include_directories(${DirectX_INCLUDE_DIR}) # KORTEMIK TEMP
  add_definitions(-DUSE_XINPUT)

  if(OPENAL)
    add_definitions(-DUSE_OPENAL)
    include_directories(libs/openal-soft/include)
  endif()
endif()	# NOT UNIX

#if(NOT ANDROID)
add_definitions(-DUSE_EXCEPTIONS)
#endif()

# the warnings are used for every profile anyway, so put them in a variable
set(my_warn_flags "-Wno-pragmas -Wno-unused-variable -Wno-unused-but-set-variable -Wno-switch -Wno-unused-value -Winvalid-pch -Wno-multichar")

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
  # append clang-specific settings for warnings (the second one make sure clang doesn't complain
  # about unknown -W flags, like -Wno-unused-but-set-variable)
  set(my_warn_flags "${my_warn_flags} -Wno-local-type-template-args -Wno-unknown-warning-option -Wno-inline-new-delete")
endif() # CLANG

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG -O0 -ggdb -fno-strict-aliasing ${my_warn_flags}")
#set(CMAKE_C_FLAGS_DEBUGALL "${CMAKE_C_FLAGS_DEBUGALL} -g -ggdb -D_DEBUG -fno-strict-aliasing ${my_warn_flags}")
#set(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_PROFILE} -g -ggdb -D_DEBUG -O1 -fno-omit-frame-pointer -fno-strict-aliasing ${my_warn_flags}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math -fno-unsafe-math-optimizations -fomit-frame-pointer -fno-strict-aliasing 
${my_warn_flags}")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -g -O3 -ffast-math -fno-unsafe-math-optimizations -fomit-frame-pointer 
-fno-strict-aliasing ${my_warn_flags}")
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -Os -ffast-math -fno-unsafe-math-optimizations -fomit-frame-pointer 
-fno-strict-aliasing ${my_warn_flags}")

set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
#set(CMAKE_CXX_FLAGS_DEBUGALL ${CMAKE_C_FLAGS_DEBUGALL})
#set(CMAKE_CXX_FLAGS_PROFILE ${CMAKE_C_FLAGS_PROFILE})
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO})
set(CMAKE_CXX_FLAGS_MINSIZEREL ${CMAKE_C_FLAGS_MINSIZEREL})
