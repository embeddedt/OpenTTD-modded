# Install script for directory: /__w/OpenTTD-modded/OpenTTD-modded/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/script/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/settingsgen/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/strgen/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/3rdparty/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/ai/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/blitter/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/core/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/game/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/lang/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/linkgraph/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/misc/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/music/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/network/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/os/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/pathfinder/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/saveload/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/sound/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/spriteloader/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/table/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/video/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/widgets/cmake_install.cmake")

endif()

