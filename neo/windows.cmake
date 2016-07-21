if(CMAKE_HOST_WIN32)
  if(MSVC) # mingw does not work with directx headers
    find_package(DirectX REQUIRED)
    include_directories(${DirectX_INCLUDE_DIR})
  endif() 
endif()

add_definitions(-DUSE_XINPUT)

if(OPENAL)
  add_definitions(-DUSE_OPENAL)
  
  if(BUNDLED_OPENAL)
    include_directories(${CMAKE_SOURCE_DIR}/libs/openal-soft/openal-soft.git/include)
    set(OPENAL-SOFT_LIBRARY OpenAL32)
    list(APPEND OpenTechBFG_INCLUDES ${OPENAL_INCLUDES})
    list(APPEND OpenTechBFG_SOURCES ${OPENAL_SOURCES})
    install(FILES "${CMAKE_BINARY_DIR}/libs/openal-soft/openal-soft.git/OpenAL32.dll" DESTINATION bin COMPONENT OpenTechEngine)
  endif()
  
else() # XAUDIO2
  list(APPEND OpenTechBFG_INCLUDES ${XAUDIO2_INCLUDES})
  list(APPEND OpenTechBFG_SOURCES ${XAUDIO2_SOURCES})
endif()

if(FFMPEG)
  add_definitions(-DUSE_FFMPEG)

  if(PROCESSOR_ARCHITECTURE STREQUAL "x86")
    include_directories(../libs/ffmpeg/ffmpeg-win32/include)
    include_directories(../libs/ffmpeg/ffmpeg-win32/include/libswscale)
    include_directories(../libs/ffmpeg/ffmpeg-win32/include/libavformat)
    include_directories(../libs/ffmpeg/ffmpeg-win32/include/libavdevice)
    include_directories(../libs/ffmpeg/ffmpeg-win32/include/libavcodec)
    
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/ffmpeg/ffmpeg-win32/lib)
  else()
    include_directories(../libs/ffmpeg/ffmpeg-win64/include)
    include_directories(../libs/ffmpeg/ffmpeg-win64/include/libswscale)
    include_directories(../libs/ffmpeg/ffmpeg-win64/include/libavformat)
    include_directories(../libs/ffmpeg/ffmpeg-win64/include/libavdevice)
    include_directories(../libs/ffmpeg/ffmpeg-win64/include/libavcodec)
    
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/ffmpeg/ffmpeg-win64/lib)
  endif()
  
  set(FFmpeg_LIBRARIES
    avcodec
    avformat
    avutil
    swscale)
  
endif() # FFMPEG

if(USE_MFC_TOOLS)
  
  include_directories(../libs/atlmfc/include)
  if(CMAKE_CL_64)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/atlmfc/lib/AMD64)
  else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/atlmfc/lib)
  endif()
  
  add_definitions(-DUSE_MFC_TOOLS)
  
  list(APPEND OpenTechBFG_SOURCES
    ${TOOLS_INCLUDES}
    ${TOOLS_COMAFX_INCLUDES} ${TOOLS_COMAFX_SOURCES}
    ${TOOLS_COMMON_INCLUDES} ${TOOLS_COMMON_SOURCES}
    ${TOOLS_COMMON_PROPTREE_INCLUDES} ${TOOLS_COMMON_PROPTREE_SOURCES}
    
    ${EDITOR_AF_INCLUDES} ${EDITOR_AF_SOURCES}
    ${EDITOR_DEBUGGER_INCLUDES} ${EDITOR_DEBUGGER_SOURCES}
    ${EDITOR_DECL_INCLUDES} ${EDITOR_DECL_SOURCES}
    ${EDITOR_GUIED_INCLUDES} ${EDITOR_GUIED_SOURCES}
    ${EDITOR_MATERIALEDITOR_INCLUDES} ${EDITOR_MATERIALEDITOR_SOURCES}
    ${EDITOR_PARTICLE_INCLUDES} ${EDITOR_PARTICLE_SOURCES}
    ${EDITOR_PDA_INCLUDES} ${EDITOR_PDA_SOURCES}
    ${EDITOR_RADIANT_INCLUDES} ${EDITOR_RADIANT_SOURCES}
    ${EDITOR_SCRIPT_INCLUDES} ${EDITOR_SCRIPT_SOURCES}
    ${EDITOR_SOUND_INCLUDES} ${EDITOR_SOUND_SOURCES})
endif() # USE_MFC_TOOLS

list(APPEND OpenTechBFG_INCLUDES
  ${SYS_INCLUDES} 
  ${WIN32_INCLUDES})

list(APPEND OpenTechBFG_SOURCES
  ${SYS_SOURCES}
  ${WIN32_SOURCES})

list(REMOVE_DUPLICATES OpenTechBFG_SOURCES)

list(APPEND OpenTechBFG_SOURCES ${WIN32_RESOURCES})

# icon
list(APPEND OpenTechBFG_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/OpenTechEngine.rc")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(OpenTechEngine WIN32 ${OpenTechBFG_INCLUDES} ${OpenTechBFG_SOURCES})

list(APPEND DIRECTX_LIBRARIES
  dxguid
  dinput8
  #d3d9
  #d3dx9
  dbghelp
  #eaxguid
  iphlpapi
  winmm
  wsock32.lib
  )

if(MSVC)
  list(APPEND DIRECTX_LIBRARIES
    #XInput
    xinput9_1_0
    )
elseif(CMAKE_HOST_WIN32) # mingw on windows has only xinput library
  list(APPEND DIRECTX_LIBRARIES
    xinput
    )
else() # mingw on linux
  list(APPEND DIRECTX_LIBRARIES
    #XInput
    xinput9_1_0
    )

  if(EXISTS "/usr/x86_64-w64-mingw32/sys-root/mingw/bin/libgcc_s_seh-1.dll")
    install(FILES "/usr/x86_64-w64-mingw32/sys-root/mingw/bin/libgcc_s_seh-1.dll" DESTINATION bin COMPONENT OpenTechEngine)
    install(FILES "/usr/x86_64-w64-mingw32/sys-root/mingw/bin/libwinpthread-1.dll" DESTINATION bin COMPONENT OpenTechEngine)
    install(FILES "/usr/x86_64-w64-mingw32/sys-root/mingw/bin/libstdc++-6.dll" DESTINATION bin COMPONENT OpenTechEngine)
  elseif(EXISTS "/usr/lib/gcc/x86_64-w64-mingw32/4.8/libgcc_s_sjlj-1.dll")
    install(FILES "/usr/lib/gcc/x86_64-w64-mingw32/4.8/libgcc_s_sjlj-1.dll" DESTINATION bin COMPONENT OpenTechEngine)
    install(FILES "/usr/lib/gcc/x86_64-w64-mingw32/4.8/libstdc++-6.dll" DESTINATION bin COMPONENT OpenTechEngine)
    install(FILES "/usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll" DESTINATION bin COMPONENT OpenTechEngine)
  else()
    install(FILES "${CMAKE_BINARY_DIR}/libgcc_s_seh-1.dll" DESTINATION bin COMPONENT OpenTechEngine)
    install(FILES "${CMAKE_BINARY_DIR}/libwinpthread-1.dll" DESTINATION bin COMPONENT OpenTechEngine)
    install(FILES "${CMAKE_BINARY_DIR}/libstdc++-6.dll" DESTINATION bin COMPONENT OpenTechEngine)
  endif()
endif()

target_link_libraries(OpenTechEngine
  idlib
  ${JPEG_LIBRARY}
  ${PNG_LIBRARY}
  ${ZLIB_LIBRARY}
  ${MINIZIP_LIBRARY}
  ${IRRXML_LIBRARY}
  ${GLEW_LIBRARY}
  ${OGGVORBIS_LIBRARY}
  ${DIRECTX_LIBRARIES}
  opengl32
  glu32
  ${OPENAL-SOFT_LIBRARY}
  ${FFMPEG_LIBRARIES}
  ${CEGUI_LIBRARY}
  ${CEGUIGLR_LIBRARY}
  )
  
#CMAKE_BINARY_DIR
install(TARGETS OpenTechEngine
  RUNTIME DESTINATION bin COMPONENT OpenTechEngine)
