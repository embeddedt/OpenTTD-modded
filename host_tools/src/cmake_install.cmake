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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/script/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/settingsgen/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/strgen/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/3rdparty/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/ai/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/blitter/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/core/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/game/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/lang/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/linkgraph/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/misc/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/music/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/network/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/os/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/pathfinder/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/saveload/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/sound/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/spriteloader/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/table/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/video/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/widgets/cmake_install.cmake")

endif()

