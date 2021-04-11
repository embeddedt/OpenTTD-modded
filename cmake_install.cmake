# Install script for directory: /__w/OpenTTD-modded/OpenTTD-modded

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/games" TYPE EXECUTABLE FILES "/__w/OpenTTD-modded/OpenTTD-modded/em_build/openttd.html")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/games/openttd.html" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/games/openttd.html")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/games/openttd.html")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlanguage_filesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/games/openttd" TYPE DIRECTORY FILES
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/lang"
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/baseset"
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/ai"
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/game"
    "/__w/OpenTTD-modded/OpenTTD-modded/bin/scripts"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/openttd" TYPE FILE FILES
    "/__w/OpenTTD-modded/OpenTTD-modded/COPYING.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/README.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/changelog.txt"
    "/__w/OpenTTD-modded/OpenTTD-modded/docs/multiplayer.md"
    "/__w/OpenTTD-modded/OpenTTD-modded/known-bugs.txt"
    "/__w/OpenTTD-modded/OpenTTD-modded/jgrpp-changelog.md"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmanualx" OR NOT CMAKE_INSTALL_COMPONENT)
  
                execute_process(COMMAND /usr/bin/cmake -E copy /__w/OpenTTD-modded/OpenTTD-modded/docs/openttd.6 /__w/OpenTTD-modded/OpenTTD-modded/em_build/docs/openttd.6)
                execute_process(COMMAND gzip -9 -n -f /__w/OpenTTD-modded/OpenTTD-modded/em_build/docs/openttd.6)
            
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmanualx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man6" TYPE FILE FILES "/__w/OpenTTD-modded/OpenTTD-modded/em_build/docs/openttd.6.gz")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmediax" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE DIRECTORY FILES
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/media/icons"
    "/__w/OpenTTD-modded/OpenTTD-modded/em_build/media/pixmaps"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmenux" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/applications" TYPE FILE FILES "/__w/OpenTTD-modded/OpenTTD-modded/em_build/media/openttd.desktop")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/bin/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/src/cmake_install.cmake")
  include("/__w/OpenTTD-modded/OpenTTD-modded/em_build/media/cmake_install.cmake")

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
