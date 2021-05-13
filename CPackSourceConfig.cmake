# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "")
set(CPACK_BINARY_BUNDLE "")
set(CPACK_BINARY_CYGWIN "")
set(CPACK_BINARY_DEB "")
set(CPACK_BINARY_DRAGNDROP "")
set(CPACK_BINARY_FREEBSD "")
set(CPACK_BINARY_IFW "")
set(CPACK_BINARY_NSIS "")
set(CPACK_BINARY_NUGET "")
set(CPACK_BINARY_OSXX11 "")
set(CPACK_BINARY_PACKAGEMAKER "")
set(CPACK_BINARY_PRODUCTBUILD "")
set(CPACK_BINARY_RPM "")
set(CPACK_BINARY_STGZ "")
set(CPACK_BINARY_TBZ2 "")
set(CPACK_BINARY_TGZ "")
set(CPACK_BINARY_TXZ "")
set(CPACK_BINARY_TZ "")
set(CPACK_BINARY_WIX "")
set(CPACK_BINARY_ZIP "")
set(CPACK_BUILD_SOURCE_DIRS "/__w/OpenTTD-modded/OpenTTD-modded;/__w/OpenTTD-modded/OpenTTD-modded/em_build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_INSTALLED_DIRECTORIES "/__w/OpenTTD-modded/OpenTTD-modded;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/emsdk/upstream/emscripten/cmake/Modules;/emsdk/upstream/emscripten/cmake/Modules;/emsdk/upstream/emscripten/cmake/Modules;/emsdk/upstream/emscripten/cmake/Modules;/emsdk/upstream/emscripten/cmake/Modules;/__w/OpenTTD-modded/OpenTTD-modded/os/emscripten/cmake;/__w/OpenTTD-modded/OpenTTD-modded/cmake")
set(CPACK_MONOLITHIC_INSTALL "YES")
set(CPACK_NSIS_DISPLAY_NAME "OpenTTD-JGRPP")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "OpenTTD-JGRPP")
set(CPACK_OUTPUT_CONFIG_FILE "/__w/OpenTTD-modded/OpenTTD-modded/em_build/CPackConfig.cmake")
set(CPACK_OUTPUT_FILE_PREFIX "bundles")
set(CPACK_PACKAGE_CHECKSUM "SHA256")
set(CPACK_PACKAGE_CONTACT "https://github.com/JGRennison/OpenTTD-patches")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION "OpenTTD (JGRPP)")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.13/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenTTD (JGRPP)")
set(CPACK_PACKAGE_EXECUTABLES "openttd;OpenTTD")
set(CPACK_PACKAGE_FILE_NAME "openttd-1.12.0-Source")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/JGRennison/OpenTTD-patches")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "OpenTTD-JGRPP")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "OpenTTD-JGRPP")
set(CPACK_PACKAGE_NAME "openttd")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "OpenTTD (JGRPP)")
set(CPACK_PACKAGE_VERSION "1.12.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "12")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "/__w/OpenTTD-modded/OpenTTD-modded/COPYING.md")
set(CPACK_RESOURCE_FILE_README "/__w/OpenTTD-modded/OpenTTD-modded/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.13/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "")
set(CPACK_SOURCE_CYGWIN "")
set(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "/__w/OpenTTD-modded/OpenTTD-modded;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/__w/OpenTTD-modded/OpenTTD-modded/em_build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "openttd-1.12.0-Source")
set(CPACK_SOURCE_RPM "OFF")
set(CPACK_SOURCE_TBZ2 "ON")
set(CPACK_SOURCE_TGZ "ON")
set(CPACK_SOURCE_TOPLEVEL_TAG "x86-Source")
set(CPACK_SOURCE_TXZ "ON")
set(CPACK_SOURCE_TZ "ON")
set(CPACK_SOURCE_ZIP "OFF")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "x86")
set(CPACK_TOPLEVEL_TAG "x86-Source")
set(CPACK_WIX_SIZEOF_VOID_P "4")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/__w/OpenTTD-modded/OpenTTD-modded/em_build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()