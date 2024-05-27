# Install script for directory: /__w/OpenTTD-modded/OpenTTD-modded

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/emsdk/upstream/emscripten/cache/sysroot")
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

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/emsdk/upstream/bin/llvm-objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/games" TYPE EXECUTABLE FILES "/__w/OpenTTD-modded/OpenTTD-modded/em_build/openttd.html")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/games/openttd.html" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/games/openttd.html")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/emsdk/upstream/bin/llvm-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/games/openttd.html")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/games" TYPE FILE FILES
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/openttd.js"
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/openttd.wasm"
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/openttd.data"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/openttd" TYPE FILE FILES
    "/__w/OpenTTD-modded/OpenTTD-modded/COPYING.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/README.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/CREDITS.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/CONTRIBUTING.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/changelog.txt"
    "/__w/OpenTTD-modded/OpenTTD-modded/known-bugs.txt"
    "/__w/OpenTTD-modded/OpenTTD-modded/jgrpp-changelog.md"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/openttd/docs" TYPE FILE FILES
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/admin_network.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/debugging_desyncs.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/desync.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/directory_structure.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/eints.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/game_coordinator.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/linkgraph.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/logging_and_performance_metrics.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/multiplayer.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/savegame_format.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/symbol_server.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/obg_format.txt"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/obm_format.txt"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/obs_format.txt"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmanualx" OR NOT CMAKE_INSTALL_COMPONENT)
  
                execute_process(COMMAND /usr/bin/cmake -E copy /__w/OpenTTD-modded/OpenTTD-modded/docs/openttd.6 /__w/OpenTTD-modded/OpenTTD-modded/em_build/docs/openttd.6)
                execute_process(COMMAND gzip -9 -n -f /__w/OpenTTD-modded/OpenTTD-modded/em_build/docs/openttd.6)
            
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmanualx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man6" TYPE FILE FILES "/__w/OpenTTD-modded/OpenTTD-modded/em_build/docs/openttd.6.gz")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/bin/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/media/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/regression/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/__w/OpenTTD-modded/OpenTTD-modded/em_build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
