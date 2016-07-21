set(CPACK_PACKAGE_NAME "OpenTechBFG")
set(CPACK_PACKAGE_VENDOR "OpenTechEngine")
set(CPACK_PACKAGE_CONTACT "https://github.com/OpenTechEngine/OpenTechBFG")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Engine based on Doom 3 BFG aiming to allow the creation of standalone games")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_COMPONENT_OPENTECHENGINE_DESCRIPTION "OpenTechBFG")
set(CPACK_COMPONENT_ASSETS_DESCRIPTION "Sample game content")
set(CPACK_COMPONENT_CEGUI_LIB_DESCRIPTION "CEGUI libraries")
set(CPACK_COMPONENT_CEGUI_BIN_DESCRIPTION "CEGUI runtime libraries")
set(CPACK_COMPONENT_OPENTECHENGINE_DISPLAY_NAME "OpenTechBFG")
set(CPACK_COMPONENT_ASSETS_DISPLAY_NAME "Sample game content")
set(CPACK_COMPONENT_CEGUI_LIB_DISPLAY_NAME "CEGUI libraries")
set(CPACK_COMPONENT_CEGUI_BIN_DISPLAY_NAME "CEGUI runtime libraries")
set(CPACK_RESOURCE_FILE_LICENSE_PROVIDED "1")
if(CPACK_RESOURCE_FILE_LICENSE_PROVIDED STREQUAL "1")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING-GPLv3-id.txt")
endif()
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/README_SDL_Joystick.txt")

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(CPACK_COMPONENTS_ALL
    OpenTechEngine
    Assets
    cegui_lib
    #  cegui_bin
    #  cegui_devel
    #  cegui_lua
    #  cegui_devel
    #  cegui_python
    )
  set(CPACK_GENERATOR RPM DEB)
  set(CPACK_DEB_COMPONENT_INSTALL ON)
  set(CPACK_RPM_COMPONENT_INSTALL ON)
  set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/OpenTechEngine/OpenTechBFG")
  set(CPACK_COMPONENT_OPENTECHENGINE_REQUIRED ON)
  set(CPACK_COMPONENT_CEGUI_LIB_REQUIRED ON)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  set(CPACK_COMPONENTS_ALL
    OpenTechEngine
    Assets
    cegui_lib
    cegui_bin
    #  cegui_devel
    #  cegui_lua
    #  cegui_devel
    #  cegui_python
    )
  set(CPACK_GENERATOR BUNDLE)
  set(CPACK_BUNDLE_COMPONENT_INSTALL ON)
  set(CPACK_COMPONENT_OPENTECHENGINE_REQUIRED ON)
  set(CPACK_COMPONENT_CEGUI_LIB_REQUIRED ON)
  set(CPACK_COMPONENT_CEGUI_BIN_REQUIRED ON)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(CPACK_COMPONENTS_ALL
    OpenTechEngine
    Assets
    #  cegui_lib
    cegui_bin
    #  cegui_devel
    #  cegui_lua
    #  cegui_devel
    #  cegui_python
    )
  set(CPACK_GENERATOR NSIS)
  set(CPACK_NSIS_COMPONENT_INSTALL ON)
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "OpenTechEngine\\\\\\\\OpenTechBFG")
  set(CPACK_COMPONENT_OPENTECHENGINE_REQUIRED ON)
  set(CPACK_COMPONENT_CEGUI_BIN_REQUIRED ON)
  set(CPACK_NSIS_DISPLAY_NAME "OpenTechBFG")
  set(CPACK_PACKAGE_EXECUTABLES "OpenTechEngine;OpenTechEngine")
  #set(CPACK_NSIS_MUI_FINISHPAGE_RUN "OpenTechEngine.exe")
  set(CPACK_NSIS_MODIFY_PATH "ON")
  set(CPACK_CREATE_DESKTOP_LINKS "OpenTechEngine")
  set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/OpenTechEngine.ico")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\\\\\OpenTechEngine.exe")
  set(CPACK_NSIS_HELP_LINK "https://github.com/OpenTechEngine/Discussions/issues")
  set(CPACK_NSIS_URL_INFO_ABOUT "https://modwiki.xnet.fi")
  set(CPACK_NSIS_CONTACT "opentechengine@github.com")
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
else()
  set(CPACK_COMPONENTS_ALL
    OpenTechEngine
    Assets
    cegui_lib
    #  cegui_bin
    #  cegui_devel
    #  cegui_lua
    #  cegui_devel
    #  cegui_python
    )
  set(CPACK_GENERATOR TGZ)
  set(CPACK_TGZ_COMPONENT_INSTALL ON)
  set(CPACK_COMPONENT_OPENTECHENGINE_REQUIRED ON)
  set(CPACK_COMPONENT_CEGUI_LIB_REQUIRED ON)
endif()




