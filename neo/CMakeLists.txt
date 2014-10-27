cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project(OpenTechEngine)

################################################################################

option(USE_MFC_TOOLS
		"Compile the built-in MFC based tools" OFF)
		
option(MONOLITH
		"Embed game logic into main executable" ON)
		
option(SDL2
		"Use SDL2 instead of SDL1.2" OFF)
		
option(OPENAL
		"Use OpenAL soft instead of XAudio2" ON)

option(FFMPEG
		"Use FMPEG to render Bink videos" OFF)

option(IDTOOLS
		"Compile the built-in game tools" ON)

#options########################################################################

option(BUNDLED_JPEG
		"Use bundled libjpeg" ON)

option(BUNDLED_PNG
		"Use bundled libpng" ON)

option(BUNDLED_ZLIB
		"Use bundled zlib" ON)

option(BUNDLED_MINIZIP
		"Use bundled minizip" ON)

option(BUNDLED_IRRXML
		"Use bundled irrxml" OFF)

option(BUNDLED_GLEW
		"Use bundled glew" ON)

option(BUNDLED_FREETYPE
		"Use bundled freetype" OFF)

option(BUNDLED_OGGVORBIS
		"Use bundled oggvorbis" OFF)

################################################################################
		
message(STATUS CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE})

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
	add_definitions(-pipe)
	#add_definitions(-Wall)
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
		
		find_package(DirectX REQUIRED)
		include_directories(libs/mingw-hacks)
		include_directories(${DirectX_INCLUDE_DIR})
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

elseif(MSVC)

		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /D _DEBUG /MP /MTd")
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MP /Oi /Oy /MT")
		set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /MP /Oi /MTd")
		set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} /MP /Oi /Oy /MT")
		
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP /MTd")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP /Oi /Oy /MT")
		set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MP /MTd")
		set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MP /Oi /Oy /MT")
		
		# RB: without /SAFESEH:NO we can't link against ffmpeg libs and VS2013 or we have to build our own
		# libs for newer compilers
		set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
		set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} /SAFESEH:NO")
		set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SAFESEH:NO")
		set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} /SAFESEH:NO")

	

	add_definitions(-DWIN32 
					-D_WINDOWS
					-D_CRT_SECURE_NO_DEPRECATE
					-D_CRT_NONSTDC_NO_DEPRECATE
					-D_CRT_SECURE_NO_WARNINGS
					-D_MBCS
					-DUSE_EXCEPTIONS)
					
	if(NOT CMAKE_CL_64)
		add_definitions(-D_USE_32BIT_TIME_T)
	endif()
					
	if(USE_MFC_TOOLS)
		add_definitions(-D_AFXDLL)
		
		# 0: Use Standard Windows Libraries
		# 1: Use MFC in a Static Library
		# 2: Use MFC in a Shared DLL 
		set(CMAKE_MFC_FLAG 2)
	endif()
endif() # MSVC

#if(STANDALONE)
#	add_definitions(-DSTANDALONE)
#endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/common.cmake)

## TARGETS
			
if(NOT UNIX) # MSVC and MinGW
	find_package(DirectX REQUIRED)
	include_directories(${DirectX_INCLUDE_DIR})

	if(OPENAL)
		add_definitions(-DUSE_OPENAL)
	
		include_directories(libs/openal-soft/include)
		
		#if(CMAKE_CL_64)
		if(OPENAL) # KORTEMIK TEMP
			link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/openal-soft/libs/win64)
		else()
			link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/openal-soft/libs/win32)
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
		XInput
		#d3d9
		#d3dx9
		dbghelp
		#eaxguid
		iphlpapi
		winmm
		wsock32.lib
	)
	
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
	
else() # UNIX

	set(OPENAL_LIBRARY openal)

	list(APPEND OpenTechBFG_SOURCES
		${SYS_INCLUDES} ${SYS_SOURCES})
	
	find_package(OpenGL REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS})

	#if(UNIX)
	if(FFMPEG)
		find_package(FFMPEG REQUIRED)
		add_definitions(-DUSE_FFMPEG)
		
		include_directories(${FFMPEG_INCLUDE_DIR})
		link_directories(${FFMPEG_LIBRARIES_DIRS})
	endif()

	if(SDL2)
		find_package(SDL2 REQUIRED)
		include_directories(${SDL2_INCLUDE_DIR})
		set(SDLx_LIBRARY ${SDL2_LIBRARY})
	else()
		find_package(SDL REQUIRED)
		include_directories(${SDL_INCLUDE_DIR})
		set(SDLx_LIBRARY ${SDL_LIBRARY})
	endif()

	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		list(REMOVE_ITEM POSIX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sys/posix/platform_linux.cpp)
	else()
		list(REMOVE_ITEM POSIX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sys/posix/platform_osx.cpp)
	endif()

	list(APPEND OpenTechBFG_SOURCES
		${POSIX_INCLUDES} ${POSIX_SOURCES}
		${SDL_INCLUDES} ${SDL_SOURCES})
		
	if(OPENAL)
		find_package(OpenAL REQUIRED)
		add_definitions(-DUSE_OPENAL)
		
		list(APPEND OpenTechBFG_INCLUDES ${OPENAL_INCLUDES})
		list(APPEND OpenTechBFG_SOURCES ${OPENAL_SOURCES})
	else()
		list(APPEND OpenTechBFG_INCLUDES ${STUBAUDIO_INCLUDES})
		list(APPEND OpenTechBFG_SOURCES ${STUBAUDIO_SOURCES})
	endif()
			
	#endif()

	list(REMOVE_DUPLICATES OpenTechBFG_SOURCES)
	
	GET_DIRECTORY_PROPERTY(_directory_flags DEFINITIONS)
	LIST(APPEND _compiler_FLAGS ${_directory_flags})
	SEPARATE_ARGUMENTS(_compiler_FLAGS)

	add_executable(OpenTechEngine WIN32 ${OpenTechBFG_SOURCES})

	#if(NOT WIN32)
	if(NOT "${CMAKE_SYSTEM}" MATCHES "Darwin")
		set(RT_LIBRARY rt)
	endif()

	if(NOT "${CMAKE_SYSTEM}" MATCHES "FreeBSD")
		set(DL_LIBRARY dl)
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
	  ${OPENGL_LIBRARIES}
	  pthread
	  ${DL_LIBRARY}
	  ${RT_LIBRARY}
	  ${SDLx_LIBRARY}
	  ${OPENAL_LIBRARY}
	  ${FFMPEG_LIBRARIES}
	  )
	#endif()
endif()
