if(0) # KORTEMIK TEMP
  find_package(DirectX REQUIRED)
  include_directories(${DirectX_INCLUDE_DIR})
endif()

if(OPENAL)
  add_definitions(-DUSE_OPENAL)

  include_directories(libs/openal-soft/include)
  
  #if(CMAKE_CL_64)
  if(OPENAL) # KORTEMIK TEMP
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/openal-soft/libs/Win64)
  else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/openal-soft/libs/Win32)
  endif()
  
  list(APPEND OpenTechBFG_INCLUDES ${OPENAL_INCLUDES})
  list(APPEND OpenTechBFG_SOURCES ${OPENAL_SOURCES})

  set(OPENAL_LIBRARY OpenAL32)
  
  if(CMAKE_CL_64)
    install(FILES libs/openal-soft/lib/win64/OpenAL64.dll DESTINATION .)
  else()
    install(FILES libs/openal-soft/lib/win32/OpenAL32.dll DESTINATION .)
    install(FILES libs/openal-soft/lib/win32/OpenAL32.pdb DESTINATION .)
  endif()
else() # XAUDIO2
  list(APPEND OpenTechBFG_INCLUDES ${XAUDIO2_INCLUDES})
  list(APPEND OpenTechBFG_SOURCES ${XAUDIO2_SOURCES})
endif()

if(FFMPEG)
  add_definitions(-DUSE_FFMPEG)

  if(CMAKE_CL_64)
    include_directories(libs/ffmpeg-win64/include)
    include_directories(libs/ffmpeg-win64/include/libswscale)
    include_directories(libs/ffmpeg-win64/include/libavformat)
    include_directories(libs/ffmpeg-win64/include/libavdevice)
    include_directories(libs/ffmpeg-win64/include/libavcodec)
    
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/ffmpeg-win64/lib)
  else()
    include_directories(libs/ffmpeg-win32/include)
    include_directories(libs/ffmpeg-win32/include/libswscale)
    include_directories(libs/ffmpeg-win32/include/libavformat)
    include_directories(libs/ffmpeg-win32/include/libavdevice)
    include_directories(libs/ffmpeg-win32/include/libavcodec)
    
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/ffmpeg-win32/lib)
  endif()
  
  set(FFmpeg_LIBRARIES
    avcodec
    avformat
    avutil
    swscale)
  
endif() # FFMPEG

if(USE_MFC_TOOLS)
  
  include_directories(libs/atlmfc/include)
  if(CMAKE_CL_64)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/atlmfc/lib/amd64)
  else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/atlmfc/lib)
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

if(0) # KORTEMIK TEMP
  list(APPEND DIRECTX_LIBRARIES
  XInput
  )
else()
  list(APPEND DIRECTX_LIBRARIES
    xinput9_1_0
  )
endif()

target_link_libraries(OpenTechEngine
  idlib
  ${JPEG_LIBRARY}
  ${PNG_LIBRARY}
  ${ZLIB_LIBRARY}
  ${MINIZIP_LIBRARY}
  ${IRRXML_LIBRARY}
  ${GLEW_LIBRARY}
  ${FREETYPE_LIBRARY}
  ${OGGVORBIS_LIBRARY}
  ${DIRECTX_LIBRARIES}
  opengl32
  glu32
  ${OPENAL_LIBRARY}
  ${FFMPEG_LIBRARIES}
  )

#CMAKE_BINARY_DIR
if(CMAKE_CL_64)
  install(TARGETS OpenTechEngine
    RUNTIME DESTINATION .)
else()
  install(TARGETS OpenTechEngine
    RUNTIME DESTINATION .)
endif()
