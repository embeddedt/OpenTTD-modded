# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /__w/OpenTTD-modded/OpenTTD-modded

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /__w/OpenTTD-modded/OpenTTD-modded/em_build

# Utility rule file for host_tools.

# Include the progress variables for this target.
include CMakeFiles/host_tools.dir/progress.make

CMakeFiles/host_tools:
	cd /__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools && /usr/bin/cmake --build . --target host_tools --config 

host_tools: CMakeFiles/host_tools
host_tools: CMakeFiles/host_tools.dir/build.make

.PHONY : host_tools

# Rule to build all files generated by this target.
CMakeFiles/host_tools.dir/build: host_tools

.PHONY : CMakeFiles/host_tools.dir/build

CMakeFiles/host_tools.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/host_tools.dir/cmake_clean.cmake
.PHONY : CMakeFiles/host_tools.dir/clean

CMakeFiles/host_tools.dir/depend:
	cd /__w/OpenTTD-modded/OpenTTD-modded/em_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /__w/OpenTTD-modded/OpenTTD-modded /__w/OpenTTD-modded/OpenTTD-modded /__w/OpenTTD-modded/OpenTTD-modded/em_build /__w/OpenTTD-modded/OpenTTD-modded/em_build /__w/OpenTTD-modded/OpenTTD-modded/em_build/CMakeFiles/host_tools.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/host_tools.dir/depend

