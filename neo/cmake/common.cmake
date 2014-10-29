

#idlib##########################################################################

file(GLOB ID__INCLUDES idlib/*.h)
file(GLOB ID__SOURCES idlib/*.cpp)

file(GLOB ID_BV_INCLUDES idlib/bv/*.h)
file(GLOB ID_BV_SOURCES idlib/bv/*.cpp)

file(GLOB ID_CONTAINERS_INCLUDES idlib/containers/*.h)
file(GLOB ID_CONTAINERS_SOURCES idlib/containers/*.cpp)

file(GLOB ID_GEOMETRY_INCLUDES idlib/geometry/*.h)
file(GLOB ID_GEOMETRY_SOURCES idlib/geometry/*.cpp)

file(GLOB ID_HASHING_INCLUDES idlib/hashing/*.h)
file(GLOB ID_HASHING_SOURCES idlib/hashing/*.cpp)

file(GLOB ID_MATH_INCLUDES idlib/math/*.h)
file(GLOB ID_MATH_SOURCES idlib/math/*.cpp)

file(GLOB ID_SYS_INCLUDES idlib/sys/*.h)
file(GLOB ID_SYS_SOURCES idlib/sys/*.cpp)

if(UNIX)
  file(GLOB ID_SYS_POSIX_INCLUDES idlib/sys/posix/*.h)
  file(GLOB ID_SYS_POSIX_SOURCES idlib/sys/posix/*.cpp)
else()
  file(GLOB ID_SYS_WIN32_INCLUDES idlib/sys/win32/*.h)
  file(GLOB ID_SYS_WIN32_SOURCES idlib/sys/win32/*.cpp)
endif()

set(ID_INCLUDES_ALL
  ${ID__INCLUDES}
  ${ID_BV_INCLUDES}
  ${ID_CONTAINERS_INCLUDES}
  ${ID_GEOMETRY_INCLUDES}
  ${ID_HASHING_INCLUDES}
  ${ID_MATH_INCLUDES}
  ${ID_SYS_INCLUDES}
  )

set(ID_SOURCES_ALL
  ${ID__SOURCES}
  ${ID_BV_SOURCES}
  ${ID_CONTAINERS_SOURCES}
  ${ID_GEOMETRY_SOURCES}
  ${ID_HASHING_SOURCES}
  ${ID_MATH_SOURCES}
  ${ID_SYS_SOURCES}
  )

if(UNIX)
  list(APPEND ID_INCLUDES_ALL ${ID_SYS_POSIX_INCLUDES})
  list(APPEND ID_SOURCES_ALL ${ID_SYS_POSIX_SOURCES})
else()
  list(APPEND ID_INCLUDES_ALL ${ID_SYS_WIN32_INCLUDES})
  list(APPEND ID_SOURCES_ALL ${ID_SYS_WIN32_SOURCES})
endif()

source_group("idlib" FILES ${ID__INCLUDES})
source_group("idlib" FILES ${ID__SOURCES})
source_group("idlib_bv" FILES ${ID_BV_INCLUDES})
source_group("idlib_bv" FILES ${ID_BV_SOURCES})
source_group("idlib_containers" FILES ${ID_CONTAINERS_INCLUDES})
source_group("idlib_containers" FILES ${ID_CONTAINERS_SOURCES})
source_group("idlib_geometry" FILES ${ID_GEOMETRY_INCLUDES})
source_group("idlib_geometry" FILES ${ID_GEOMETRY_SOURCES})
source_group("idlib_hashing" FILES ${ID_HASHING_INCLUDES})
source_group("idlib_hashing" FILES ${ID_HASHING_SOURCES})
source_group("idlib_math" FILES ${ID_MATH_INCLUDES})
source_group("idlib_math" FILES ${ID_MATH_SOURCES})
source_group("idlib_sys" FILES ${ID_SYS_INCLUDES})
source_group("idlib_sys" FILES ${ID_SYS_SOURCES})

if(UNIX)
  source_group("idlib_sys\\posix" FILES ${ID_SYS_POSIX_INCLUDES})
  source_group("idlib_sys\\posix" FILES ${ID_SYS_POSIX_SOURCES})
else()
  source_group("idlib_sys\\win32" FILES ${ID_SYS_WIN32_INCLUDES})
  source_group("idlib_sys\\win32" FILES ${ID_SYS_WIN32_SOURCES})
endif()

add_library(idlib ${ID_SOURCES_ALL} ${ID_INCLUDES_ALL})

#libraries######################################################################

#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/libjpeg.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/libpng.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/zlib.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/minizip.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/irrxml.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glew.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/freetype.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/oggvorbis.cmake)

#idtools########################################################################

# not a library, but still optional

file(GLOB COMPILER_INCLUDES tools/compilers/*.h)

file(GLOB COMPILER_AAS_INCLUDES tools/compilers/aas/*.h)
file(GLOB COMPILER_AAS_SOURCES tools/compilers/aas/*.cpp)

file(GLOB COMPILER_DMAP_INCLUDES tools/compilers/dmap/*.h)
file(GLOB COMPILER_DMAP_SOURCES tools/compilers/dmap/*.cpp)

file(GLOB COMPILER_RENDERBUMP_INCLUDES tools/compilers/renderbump/*.h)
file(GLOB COMPILER_RENDERBUMP_SOURCES tools/compilers/renderbump/*.cpp)

file(GLOB COMPILER_ROQVQ_INCLUDES tools/compilers/roqvq/*.h)
file(GLOB COMPILER_ROQVQ_SOURCES tools/compilers/roqvq/*.cpp)

set(TOOLS_INCLUDES tools/edit_public.h)

file(GLOB TOOLS_COMAFX_INCLUDES tools/comafx/*.h)
file(GLOB TOOLS_COMAFX_SOURCES tools/comafx/*.cpp)

set(TOOLS_COMMON_INCLUDES
  tools/common/ColorButton.h
  tools/common/DialogHelpers.h
  tools/common/MaskEdit.h
  tools/common/OpenFileDialog.h
  tools/common/PropertyGrid.h
  tools/common/RegistryOptions.h
  #tools/common/RenderBumpFlatDialog.h
  tools/common/RollupPanel.h
  tools/common/SpinButton.h)

set(TOOLS_COMMON_SOURCES
  tools/common/AlphaPopup.cpp
  tools/common/ColorButton.cpp
  tools/common/MaskEdit.cpp
  tools/common/OpenFileDialog.cpp
  tools/common/PropertyGrid.cpp
  tools/common/RegistryOptions.cpp
  #tools/common/RenderBumpFlatDialog.cpp
  tools/common/RollupPanel.cpp
  tools/common/SpinButton.cpp)

file(GLOB TOOLS_COMMON_PROPTREE_INCLUDES tools/common/PropTree/*.h)
file(GLOB TOOLS_COMMON_PROPTREE_SOURCES tools/common/PropTree/*.cpp)

file(GLOB EDITOR_AF_INCLUDES tools/af/*.h)
file(GLOB EDITOR_AF_SOURCES tools/af/*.cpp)

set(EDITOR_DECL_INCLUDES
  tools/decl/DialogDeclBrowser.h
  tools/decl/DialogDeclEditor.h
  tools/decl/DialogDeclNew.h)

set(EDITOR_DECL_SOURCES
  tools/decl/DialogDeclBrowser.cpp
  tools/decl/DialogDeclEditor.cpp
  tools/decl/DialogDeclNew.cpp)

file(GLOB EDITOR_DEBUGGER_INCLUDES tools/debugger/*.h)
file(GLOB EDITOR_DEBUGGER_SOURCES tools/debugger/*.cpp)

file(GLOB EDITOR_GUIED_INCLUDES tools/guied/*.h)
set(EDITOR_GUIED_SOURCES
  tools/guied/GEApp.cpp
  tools/guied/GECheckInDlg.cpp
  tools/guied/GEDeleteModifier.cpp
  tools/guied/GEHideModifier.cpp
  tools/guied/GEInsertModifier.cpp
  tools/guied/GEItemPropsDlg.cpp
  tools/guied/GEItemScriptsDlg.cpp
  tools/guied/GEKeyValueModifier.cpp
  tools/guied/GEModifier.cpp
  tools/guied/GEModifierGroup.cpp
  tools/guied/GEModifierStack.cpp
  tools/guied/GEMoveModifier.cpp
  tools/guied/GENavigator.cpp
  tools/guied/GEOptions.cpp
  tools/guied/GEOptionsDlg.cpp
  tools/guied/GEProperties.cpp
  tools/guied/GEPropertyPage.cpp
  tools/guied/GESelectionMgr.cpp
  tools/guied/GESizeModifier.cpp
  tools/guied/GEStateModifier.cpp
  tools/guied/GEStatusBar.cpp
  tools/guied/GETransformer.cpp
  tools/guied/GEViewer.cpp
  tools/guied/GEWindowWrapper.cpp
  #tools/guied/GEWindowWrapper_stub.cpp
  tools/guied/GEWorkspace.cpp
  tools/guied/GEWorkspaceFile.cpp
  tools/guied/GEZOrderModifier.cpp
  tools/guied/guied.cpp)

file(GLOB EDITOR_MATERIALEDITOR_INCLUDES tools/materialeditor/*.h)
file(GLOB EDITOR_MATERIALEDITOR_SOURCES tools/materialeditor/*.cpp)

file(GLOB EDITOR_PARTICLE_INCLUDES tools/particle/*.h)
file(GLOB EDITOR_PARTICLE_SOURCES tools/particle/*.cpp)

file(GLOB EDITOR_PDA_INCLUDES tools/pda/*.h)
file(GLOB EDITOR_PDA_SOURCES tools/pda/*.cpp)

file(GLOB EDITOR_RADIANT_INCLUDES tools/radiant/*.h)
file(GLOB EDITOR_RADIANT_SOURCES tools/radiant/*.cpp)

file(GLOB EDITOR_SCRIPT_INCLUDES tools/script/*.h)
file(GLOB EDITOR_SCRIPT_SOURCES tools/script/*.cpp)

file(GLOB EDITOR_SOUND_INCLUDES tools/sound/*.h)
file(GLOB EDITOR_SOUND_SOURCES tools/sound/*.cpp)


source_group("tools\\compilers" FILES ${COMPILER_INCLUDES})

source_group("tools\\compilers\\aas" FILES ${COMPILER_AAS_INCLUDES})
source_group("tools\\compilers\\aas" FILES ${COMPILER_AAS_SOURCES})

source_group("tools\\compilers\\dmap" FILES ${COMPILER_DMAP_INCLUDES})
source_group("tools\\compilers\\dmap" FILES ${COMPILER_DMAP_SOURCES})

source_group("tools\\compilers\\renderbump" FILES ${COMPILER_RENDERBUMP_INCLUDES})
source_group("tools\\compilers\\renderbump" FILES ${COMPILER_RENDERBUMP_SOURCES})

source_group("tools\\compilers\\roqvq" FILES ${COMPILER_ROQVQ_INCLUDES})
source_group("tools\\compilers\\roqvq" FILES ${COMPILER_ROQVQ_SOURCES})

source_group("tools" FILES ${TOOLS_INCLUDES})

source_group("tools\\comafx" FILES ${TOOLS_COMAFX_INCLUDES})
source_group("tools\\comafx" FILES ${TOOLS_COMAFX_SOURCES})

source_group("tools\\common" FILES ${TOOLS_COMMON_INCLUDES})
source_group("tools\\common" FILES ${TOOLS_COMMON_SOURCES})

source_group("tools\\common\\proptree" FILES ${TOOLS_COMMON_PROPTREE_INCLUDES})
source_group("tools\\common\\proptree" FILES ${TOOLS_COMMON_PROPTREE_SOURCES})

source_group("tools\\af" FILES ${EDITOR_AF_INCLUDES})
source_group("tools\\af" FILES ${EDITOR_AF_SOURCES})

source_group("tools\\debugger" FILES ${EDITOR_DEBUGGER_INCLUDES})
source_group("tools\\debugger" FILES ${EDITOR_DEBUGGER_SOURCES})

source_group("tools\\decl" FILES ${EDITOR_DECL_INCLUDES})
source_group("tools\\decl" FILES ${EDITOR_DECL_SOURCES})

source_group("tools\\guied" FILES ${EDITOR_GUIED_INCLUDES})
source_group("tools\\guied" FILES ${EDITOR_GUIED_SOURCES})

source_group("tools\\materialeditor" FILES ${EDITOR_MATERIALEDITOR_INCLUDES})
source_group("tools\\materialeditor" FILES ${EDITOR_MATERIALEDITOR_SOURCES})

source_group("tools\\particle" FILES ${EDITOR_PARTICLE_INCLUDES})
source_group("tools\\particle" FILES ${EDITOR_PARTICLE_SOURCES})

source_group("tools\\pda" FILES ${EDITOR_PDA_INCLUDES})
source_group("tools\\pda" FILES ${EDITOR_PDA_SOURCES})

source_group("tools\\radiant" FILES ${EDITOR_RADIANT_INCLUDES})
source_group("tools\\radiant" FILES ${EDITOR_RADIANT_SOURCES})

source_group("tools\\script" FILES ${EDITOR_SCRIPT_INCLUDES})
source_group("tools\\script" FILES ${EDITOR_SCRIPT_SOURCES})

source_group("tools\\sound" FILES ${EDITOR_SOUND_INCLUDES})
source_group("tools\\sound" FILES ${EDITOR_SOUND_SOURCES})

set(IDTOOLS_INCLUDES
  #${TOOLS_INCLUDES}
  #${TOOLS_COMAFX_INCLUDES}
  #${TOOLS_COMMON_INCLUDES}
  #${TOOLS_COMMON_PROPTREE_INCLUDES}
  #${EDITOR_AF_INCLUDES}
  #${EDITOR_DEBUGGER_INCLUDES}
  #${EDITOR_DECL_INCLUDES}
  #${EDITOR_GUIED_INCLUDES}
  #${EDITOR_MATERIALEDITOR_INCLUDES}
  #${EDITOR_PARTICLE_INCLUDES}
  #${EDITOR_PDA_INCLUDES}
  #${EDITOR_RADIANT_INCLUDES}
  #${EDITOR_SCRIPT_INCLUDES}
  #${EDITOR_SOUND_INCLUDES}
  ${COMPILER_INCLUDES}
  ${COMPILER_AAS_INCLUDES} ${COMPILER_AAS_SOURCES}
  ${COMPILER_DMAP_INCLUDES} ${COMPILER_DMAP_SOURCES}
  #${COMPILER_RENDERBUMP_INCLUDES} ${COMPILER_RENDERBUMP_SOURCES}
  #${COMPILER_ROQVQ_INCLUDES} ${COMPILER_ROQVQ_SOURCES}
  )

set(IDTOOLS_SOURCES
  #${TOOLS_COMAFX_SOURCES}
  #${TOOLS_COMMON_SOURCES}
  #${TOOLS_COMMON_PROPTREE_SOURCES}
  #${EDITOR_AF_SOURCES}
  #${EDITOR_DEBUGGER_SOURCES}
  #${EDITOR_DECL_SOURCES}
  #${EDITOR_GUIED_SOURCES}
  #${EDITOR_MATERIALEDITOR_SOURCES}
  #${EDITOR_PARTICLE_SOURCES}
  #${EDITOR_PDA_SOURCES}
  #${EDITOR_RADIANT_SOURCES}
  #${EDITOR_SCRIPT_SOURCES}
  #${EDITOR_SOUND_SOURCES}
  ${COMPILER_AAS_SOURCES}
  ${COMPILER_DMAP_SOURCES}
  #${COMPILER_RENDERBUMP_SOURCES}
  #${COMPILER_ROQVQ_SOURCES}
  )

################################################################################

file(GLOB AAS_INCLUDES aas/*.h)
file(GLOB AAS_SOURCES aas/*.cpp)

file(GLOB_RECURSE CM_INCLUDES cm/*.h)
file(GLOB_RECURSE CM_SOURCES cm/*.cpp)

file(GLOB FRAMEWORK_INCLUDES framework/*.h)
file(GLOB FRAMEWORK_SOURCES framework/*.cpp)

file(GLOB FRAMEWORK_ASYNC_INCLUDES framework/async/*.h)
file(GLOB FRAMEWORK_ASYNC_SOURCES framework/async/*.cpp)

file(GLOB RENDERER_INCLUDES renderer/*.h)
file(GLOB RENDERER_SOURCES renderer/*.cpp)

file(GLOB RENDERER_COLOR_INCLUDES renderer/Color/*.h)
file(GLOB RENDERER_COLOR_SOURCES renderer/Color/*.cpp)

file(GLOB RENDERER_DXT_INCLUDES renderer/DXT/*.h)
file(GLOB RENDERER_DXT_SOURCES renderer/DXT/*.cpp)

file(GLOB RENDERER_JOBS_INCLUDES renderer/jobs/*.h)
file(GLOB RENDERER_JOBS_SOURCES renderer/jobs/*.cpp)

file(GLOB RENDERER_JOBS_DYNAMICSHADOWVOLUME_INCLUDES renderer/jobs/dynamicshadowvolume/*.h)
file(GLOB RENDERER_JOBS_DYNAMICSHADOWVOLUME_SOURCES renderer/jobs/dynamicshadowvolume/*.cpp)

file(GLOB RENDERER_JOBS_PRELIGHTSHADOWVOLUME_INCLUDES renderer/jobs/prelightshadowvolume/*.h)
file(GLOB RENDERER_JOBS_PRELIGHTSHADOWVOLUME_SOURCES renderer/jobs/prelightshadowvolume/*.cpp)

file(GLOB RENDERER_JOBS_STATICSHADOWVOLUME_INCLUDES renderer/jobs/staticshadowvolume/*.h)
file(GLOB RENDERER_JOBS_STATICSHADOWVOLUME_SOURCES renderer/jobs/staticshadowvolume/*.cpp)

file(GLOB RENDERER_OPENGL_INCLUDES renderer/OpenGL/*.h)
file(GLOB RENDERER_OPENGL_SOURCES renderer/OpenGL/*.cpp)

set(SOUND_INCLUDES
  sound/snd_defines.h
  sound/snd_local.h
  sound/sound.h
  sound/SoundVoice.h
  sound/WaveFile.h)

set(SOUND_SOURCES
  #sound/snd_cache.cpp
  #sound/snd_decoder.cpp
  #sound/snd_efxfile.cpp
  sound/snd_emitter.cpp
  sound/snd_shader.cpp
  sound/snd_system.cpp
  sound/snd_world.cpp
  sound/SoundVoice.cpp
  sound/WaveFile.cpp
  )

set(XAUDIO2_INCLUDES
  sound/XAudio2/XA2_SoundHardware.h
  sound/XAudio2/XA2_SoundSample.h
  sound/XAudio2/XA2_SoundVoice.h)

set(XAUDIO2_SOURCES
  sound/XAudio2/XA2_SoundHardware.cpp
  sound/XAudio2/XA2_SoundSample.cpp
  sound/XAudio2/XA2_SoundVoice.cpp)

set(OPENAL_INCLUDES
  sound/OpenAL/AL_SoundHardware.h
  sound/OpenAL/AL_SoundSample.h
  sound/OpenAL/AL_SoundVoice.h)

set(OPENAL_SOURCES
  sound/OpenAL/AL_SoundHardware.cpp
  sound/OpenAL/AL_SoundSample.cpp
  sound/OpenAL/AL_SoundVoice.cpp)

set(STUBAUDIO_INCLUDES
  sound/stub/SoundStub.h)

set(STUBAUDIO_SOURCES
  sound/stub/SoundSample.cpp)

file(GLOB SYS_INCLUDES sys/*.h)
file(GLOB SYS_SOURCES sys/*.cpp)

file(GLOB UI_INCLUDES ui/*.h)
file(GLOB UI_SOURCES ui/*.cpp)

file(GLOB SWF_INCLUDES swf/*.h)
file(GLOB SWF_SOURCES swf/*.cpp)


set(GAMED3XP_INCLUDES
  d3xp/Achievements.h
  d3xp/Actor.h
  d3xp/AF.h
  d3xp/AFEntity.h
  d3xp/AimAssist.h
  d3xp/BrittleFracture.h
  d3xp/Camera.h
  #d3xp/EndLevel.h
  d3xp/Entity.h
  d3xp/Fx.h
  d3xp/Game.h
  d3xp/GameEdit.h
  d3xp/Game_local.h
  d3xp/Grabber.h
  d3xp/IK.h
  d3xp/Item.h
  d3xp/Leaderboards.h
  d3xp/Light.h
  d3xp/Misc.h
  d3xp/Moveable.h
  d3xp/Mover.h
  d3xp/MultiplayerGame.h
  d3xp/Player.h
  d3xp/PlayerIcon.h
  d3xp/PlayerView.h
  d3xp/PredictedValue.h
  d3xp/Projectile.h
  d3xp/Pvs.h
  d3xp/SecurityCamera.h
  d3xp/SmokeParticles.h
  d3xp/Sound.h
  d3xp/Target.h
  d3xp/Trigger.h
  d3xp/Weapon.h
  d3xp/WorldSpawn.h)

set(GAMED3XP_SOURCES
  d3xp/Achievements.cpp
  d3xp/Actor.cpp
  d3xp/AF.cpp
  d3xp/AFEntity.cpp
  d3xp/AimAssist.cpp
  d3xp/BrittleFracture.cpp
  d3xp/Camera.cpp
  #d3xp/EndLevel.cpp
  d3xp/Entity.cpp
  d3xp/Fx.cpp
  d3xp/GameEdit.cpp
  d3xp/Game_local.cpp
  d3xp/Game_network.cpp
  d3xp/Grabber.cpp
  d3xp/IK.cpp
  d3xp/Item.cpp
  d3xp/Leaderboards.cpp
  d3xp/Light.cpp
  d3xp/Misc.cpp
  d3xp/Moveable.cpp
  d3xp/Mover.cpp
  d3xp/MultiplayerGame.cpp
  d3xp/Player.cpp
  d3xp/PlayerIcon.cpp
  d3xp/PlayerView.cpp
  d3xp/precompiled.cpp
  d3xp/Projectile.cpp
  d3xp/Pvs.cpp
  d3xp/SecurityCamera.cpp
  d3xp/SmokeParticles.cpp
  d3xp/Sound.cpp
  d3xp/Target.cpp
  d3xp/Trigger.cpp
  d3xp/Weapon.cpp
  d3xp/WorldSpawn.cpp)

file(GLOB GAMED3XP_AI_INCLUDES d3xp/ai/*.h)
file(GLOB GAMED3XP_AI_SOURCES d3xp/ai/*.cpp)

file(GLOB GAMED3XP_ANIM_INCLUDES d3xp/anim/*.h)
file(GLOB GAMED3XP_ANIM_SOURCES d3xp/anim/*.cpp)

file(GLOB GAMED3XP_GAMESYS_INCLUDES d3xp/gamesys/*.h)
set(GAMED3XP_GAMESYS_SOURCES
  #d3xp/gamesys/Callbacks.cpp
  d3xp/gamesys/Class.cpp
  #d3xp/gamesys/DebugGraph.cpp
  d3xp/gamesys/Event.cpp
  d3xp/gamesys/SaveGame.cpp
  d3xp/gamesys/SysCmds.cpp
  d3xp/gamesys/SysCvar.cpp
  #d3xp/gamesys/TypeInfo.cpp
  )

file(GLOB GAMED3XP_MENUS_INCLUDES d3xp/menus/*.h)
file(GLOB GAMED3XP_MENUS_SOURCES d3xp/menus/*.cpp)

file(GLOB GAMED3XP_PHYSICS_INCLUDES d3xp/physics/*.h)
file(GLOB GAMED3XP_PHYSICS_SOURCES d3xp/physics/*.cpp)

file(GLOB GAMED3XP_SCRIPT_INCLUDES d3xp/script/*.h)
file(GLOB GAMED3XP_SCRIPT_SOURCES d3xp/script/*.cpp)

file(GLOB_RECURSE WIN32_INCLUDES sys/win32/*.h)
file(GLOB_RECURSE WIN32_SOURCES sys/win32/*.cpp)

#set(WIN32_SOURCES
#	sys/win32/win_glimp.cpp
#	sys/win32/win_input.cpp
#	sys/win32/win_main.cpp
#	sys/win32/win_shared.cpp
#	sys/win32/win_snd.cpp
#	sys/win32/win_syscon.cpp
#	sys/win32/win_taskkeyhook.cpp
#	sys/win32/win_wndproc.cpp
#	sys/win32/win_cpu.cpp # MSVC?
#	)

set(WIN32_RESOURCES
  # sys/win32/rc/res/BEVEL.BMP
  # sys/win32/rc/res/BITMAP2.BMP
  # sys/win32/rc/res/BMP00001.BMP
  # sys/win32/rc/res/BMP0002.BMP
  # sys/win32/rc/res/DEFTEX.WAL
  # sys/win32/rc/res/ENDCAP.BMP
  # sys/win32/rc/res/GetString.htm
  # sys/win32/rc/res/IBEVEL.BMP
  # sys/win32/rc/res/IENDCAP.BMP
  # sys/win32/rc/res/MEFileToolbar.bmp
  # sys/win32/rc/res/MEtoolbar.bmp
  # sys/win32/rc/res/MaterialEditor.ico
  # sys/win32/rc/res/PropTree.rc2
  # sys/win32/rc/res/Q.BMP
  # sys/win32/rc/res/RADIANT3.GIF
  # sys/win32/rc/res/Radiant.ico
  # sys/win32/rc/res/RadiantDoc.ico
  # sys/win32/rc/res/TOOLBAR1.BMP
  # sys/win32/rc/res/TOOLBAR2.BMP
  # sys/win32/rc/res/Toolbar.bmp
  # sys/win32/rc/res/VIEWDEFA.BMP
  # sys/win32/rc/res/VIEWOPPO.BMP
  # sys/win32/rc/res/bmp00002.bmp
  # sys/win32/rc/res/bmp00003.bmp
  # sys/win32/rc/res/bmp00004.bmp
  # sys/win32/rc/res/bmp00005.bmp
  # sys/win32/rc/res/cchsb.bmp
  # sys/win32/rc/res/ccrgb.bmp
  # sys/win32/rc/res/dbg_back.bmp
  # sys/win32/rc/res/dbg_breakpoint.ico
  # sys/win32/rc/res/dbg_current.ico
  # sys/win32/rc/res/dbg_currentline.ico
  # sys/win32/rc/res/dbg_empty.ico
  # sys/win32/rc/res/dbg_open.bmp
  # sys/win32/rc/res/dbg_toolbar.bmp
  sys/win32/rc/res/doom.ico
  # sys/win32/rc/res/fpoint.cur
  # sys/win32/rc/res/fxed_link.ico
  # sys/win32/rc/res/fxed_toolbar.bmp
  # sys/win32/rc/res/fxeditor.ico
  # sys/win32/rc/res/guied.ico
  # sys/win32/rc/res/guied_collapse.ico
  # sys/win32/rc/res/guied_expand.ico
  # sys/win32/rc/res/guied_hand.cur
  # sys/win32/rc/res/guied_nav_visible.ico
  # sys/win32/rc/res/guied_nav_visibledisabled.ico
  # sys/win32/rc/res/guied_scripts.ico
  # sys/win32/rc/res/guied_scripts_white.ico
  # sys/win32/rc/res/guied_viewer_toolbar.bmp
  # sys/win32/rc/res/icon2.ico
  # sys/win32/rc/res/logo_sm3dfx.bmp
  # sys/win32/rc/res/matedtree.bmp
  # sys/win32/rc/res/me_disabled_icon.ico
  # sys/win32/rc/res/me_enabled.ico
  # sys/win32/rc/res/me_off_icon.ico
  # sys/win32/rc/res/me_on_icon.ico
  # sys/win32/rc/res/qe3.ico
  # sys/win32/rc/res/shaderbar.bmp
  # sys/win32/rc/res/shaderdoc.ico
  # sys/win32/rc/res/shaderframe.ico
  # sys/win32/rc/res/spliter.cur
  )

if(NOT UNIX)
  if(USE_MFC_TOOLS)
    list(APPEND WIN32_RESOURCES sys/win32/rc/doom.rc)
    #else()
    #	list(APPEND WIN32_RESOURCES sys/win32/rc/doom_nomfc.rc)
  endif()
endif()


file(GLOB POSIX_INCLUDES sys/posix/*.h)
file(GLOB POSIX_SOURCES sys/posix/*.cpp)

file(GLOB COMMON_INCLUDES sys/common/*.h)
file(GLOB COMMON_SOURCES sys/common/*.cpp)

file(GLOB SDL_INCLUDES sys/sdl/*.h)
file(GLOB SDL_SOURCES sys/sdl/*.cpp)


source_group("aas" FILES ${AAS_INCLUDES})
source_group("aas" FILES ${AAS_SOURCES})

source_group("cm" FILES ${CM_INCLUDES})
source_group("cm" FILES ${CM_SOURCES})

source_group("framework" FILES ${FRAMEWORK_INCLUDES})
source_group("framework" FILES ${FRAMEWORK_SOURCES})

source_group("framework\\async" FILES ${FRAMEWORK_ASYNC_INCLUDES})
source_group("framework\\async" FILES ${FRAMEWORK_ASYNC_SOURCES})

source_group("renderer" FILES ${RENDERER_INCLUDES})
source_group("renderer" FILES ${RENDERER_SOURCES})

source_group("renderer\\Color" FILES ${RENDERER_COLOR_INCLUDES})
source_group("renderer\\Color" FILES ${RENDERER_COLOR_SOURCES})

source_group("renderer\\DXT" FILES ${RENDERER_DXT_INCLUDES})
source_group("renderer\\DXT" FILES ${RENDERER_DXT_SOURCES})

source_group("renderer\\jobs" FILES ${RENDERER_JOBS_INCLUDES})
source_group("renderer\\jobs" FILES ${RENDERER_JOBS_SOURCES})

source_group("renderer\\jobs\\dynamicshadowvolume" FILES ${RENDERER_JOBS_DYNAMICSHADOWVOLUME_INCLUDES})
source_group("renderer\\jobs\\dynamicshadowvolume" FILES ${RENDERER_JOBS_DYNAMICSHADOWVOLUME_SOURCES})

source_group("renderer\\jobs\\prelightshadowvolume" FILES ${RENDERER_JOBS_PRELIGHTSHADOWVOLUME_INCLUDES})
source_group("renderer\\jobs\\prelightshadowvolume" FILES ${RENDERER_JOBS_PRELIGHTSHADOWVOLUME_SOURCES})

source_group("renderer\\jobs\\staticshadowvolume" FILES ${RENDERER_JOBS_STATICSHADOWVOLUME_INCLUDES})
source_group("renderer\\jobs\\staticshadowvolume" FILES ${RENDERER_JOBS_STATICSHADOWVOLUME_SOURCES})

source_group("renderer\\OpenGL" FILES ${RENDERER_OPENGL_INCLUDES})
source_group("renderer\\OpenGL" FILES ${RENDERER_OPENGL_SOURCES})

source_group("sound" FILES ${SOUND_INCLUDES})
source_group("sound" FILES ${SOUND_SOURCES})

source_group("sound\\XAudio2" FILES ${XAUDIO2_INCLUDES})
source_group("sound\\XAudio2" FILES ${XAUDIO2_SOURCES})

source_group("sound\\OpenAL" FILES ${OPENAL_INCLUDES})
source_group("sound\\OpenAL" FILES ${OPENAL_SOURCES})

source_group("sound\\stub" FILES ${STUBAUDIO_INCLUDES})
source_group("sound\\stub" FILES ${STUBAUDIO_SOURCES})

source_group("ui" FILES ${UI_INCLUDES})
source_group("ui" FILES ${UI_SOURCES})

source_group("swf" FILES ${SWF_INCLUDES})
source_group("swf" FILES ${SWF_SOURCES})

source_group("sys" FILES ${SYS_INCLUDES})
source_group("sys" FILES ${SYS_SOURCES})

source_group("game-d3xp" FILES ${GAMED3XP_INCLUDES})
source_group("game-d3xp" FILES ${GAMED3XP_SOURCES})

source_group("game-d3xp\\ai" FILES ${GAMED3XP_AI_INCLUDES})
source_group("game-d3xp\\ai" FILES ${GAMED3XP_AI_SOURCES})

source_group("game-d3xp\\anim" FILES ${GAMED3XP_ANIM_INCLUDES})
source_group("game-d3xp\\anim" FILES ${GAMED3XP_ANIM_SOURCES})

source_group("game-d3xp\\gamesys" FILES ${GAMED3XP_GAMESYS_INCLUDES})
source_group("game-d3xp\\gamesys" FILES ${GAMED3XP_GAMESYS_SOURCES})

source_group("game-d3xp\\menus" FILES ${GAMED3XP_MENUS_INCLUDES})
source_group("game-d3xp\\menus" FILES ${GAMED3XP_MENUS_SOURCES})

source_group("game-d3xp\\physics" FILES ${GAMED3XP_PHYSICS_INCLUDES})
source_group("game-d3xp\\physics" FILES ${GAMED3XP_PHYSICS_SOURCES})

source_group("game-d3xp\\script" FILES ${GAMED3XP_SCRIPT_INCLUDES})
source_group("game-d3xp\\script" FILES ${GAMED3XP_SCRIPT_SOURCES})

source_group("sys\\win32" FILES ${WIN32_INCLUDES})
source_group("sys\\win32" FILES ${WIN32_SOURCES})
source_group("sys\\win32\\Resources" FILES ${WIN32_RESOURCES})

source_group("sys\\posix" FILES ${POSIX_INCLUDES})
source_group("sys\\posix" FILES ${POSIX_SOURCES})

source_group("sys\\common" FILES ${COMMON_INCLUDES})
source_group("sys\\common" FILES ${COMMON_SOURCES})

source_group("sys\\sdl" FILES ${SDL_INCLUDES})
source_group("sys\\sdl" FILES ${SDL_SOURCES})

set(OpenTechBFG_INCLUDES
  ${AAS_INCLUDES}
  ${CM_INCLUDES}
  ${FRAMEWORK_INCLUDES}
  ${FRAMEWORK_ASYNC_INCLUDES}
  ${RENDERER_INCLUDES}
  ${RENDERER_COLOR_INCLUDES}
  ${RENDERER_DXT_INCLUDES}
  ${RENDERER_JOBS_INCLUDES}
  ${RENDERER_JOBS_DYNAMICSHADOWVOLUME_INCLUDES}
  ${RENDERER_JOBS_PRELIGHTSHADOWVOLUME_INCLUDES}
  ${RENDERER_JOBS_STATICSHADOWVOLUME_INCLUDES}
  ${RENDERER_OPENGL_INCLUDES}
  ${SOUND_INCLUDES}
  ${UI_INCLUDES}
  ${SWF_INCLUDES}
  ${COMMON_INCLUDES}
  )

set(OpenTechBFG_SOURCES
  ${AAS_SOURCES}
  ${CM_SOURCES}
  ${FRAMEWORK_SOURCES}
  ${FRAMEWORK_ASYNC_SOURCES} 
  ${RENDERER_SOURCES}
  ${RENDERER_COLOR_SOURCES}
  ${RENDERER_DXT_SOURCES}
  ${RENDERER_JOBS_SOURCES}
  ${RENDERER_JOBS_DYNAMICSHADOWVOLUME_SOURCES}
  ${RENDERER_JOBS_PRELIGHTSHADOWVOLUME_SOURCES}
  ${RENDERER_JOBS_STATICSHADOWVOLUME_SOURCES}
  ${RENDERER_OPENGL_SOURCES}
  ${SOUND_SOURCES}
  ${UI_SOURCES}
  ${SWF_SOURCES}
  ${COMMON_SOURCES}
  )

add_definitions(-D__DOOM__
  #-DBUILD_FREETYPE
  #-DFT2_BUILD_LIBRARY
  )

if(MONOLITH)
  list(APPEND OpenTechBFG_INCLUDES
    ${GAMED3XP_INCLUDES}
    ${GAMED3XP_AI_INCLUDES} 
    ${GAMED3XP_ANIM_INCLUDES} 
    ${GAMED3XP_GAMESYS_INCLUDES} 
    ${GAMED3XP_MENUS_INCLUDES}
    ${GAMED3XP_PHYSICS_INCLUDES}
    ${GAMED3XP_SCRIPT_INCLUDES})
  
  list(APPEND OpenTechBFG_SOURCES
    ${GAMED3XP_SOURCES}
    ${GAMED3XP_AI_SOURCES}
    ${GAMED3XP_ANIM_SOURCES}
    ${GAMED3XP_GAMESYS_SOURCES}
    ${GAMED3XP_MENUS_SOURCES}
    ${GAMED3XP_PHYSICS_SOURCES}
    ${GAMED3XP_SCRIPT_SOURCES})
else()
  add_definitions(-D__DOOM_DLL__)
endif()

# KORTEMIK: fix these to contain only /
include_directories(
  .
  idlib)
#  libs/glew/include
#  libs/zlib)

if(IDTOOLS)
  add_definitions(-DUSE_IDTOOLS)
  
  list(APPEND OpenTechBFG_INCLUDES
    ${IDTOOLS_INCLUDES}
    )
  
  list(APPEND OpenTechBFG_SOURCES
    ${IDTOOLS_SOURCES} 
    )
endif()
