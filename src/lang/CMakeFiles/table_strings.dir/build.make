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

# Utility rule file for table_strings.

# Include the progress variables for this target.
include src/lang/CMakeFiles/table_strings.dir/progress.make

src/lang/CMakeFiles/table_strings: src/lang/strings.h.timestamp


src/lang/strings.h.timestamp: host_tools/src/strgen/strgen
src/lang/strings.h.timestamp: ../src/lang/afrikaans.txt
src/lang/strings.h.timestamp: ../src/lang/arabic_egypt.txt
src/lang/strings.h.timestamp: ../src/lang/basque.txt
src/lang/strings.h.timestamp: ../src/lang/belarusian.txt
src/lang/strings.h.timestamp: ../src/lang/brazilian_portuguese.txt
src/lang/strings.h.timestamp: ../src/lang/bulgarian.txt
src/lang/strings.h.timestamp: ../src/lang/catalan.txt
src/lang/strings.h.timestamp: ../src/lang/croatian.txt
src/lang/strings.h.timestamp: ../src/lang/czech.txt
src/lang/strings.h.timestamp: ../src/lang/danish.txt
src/lang/strings.h.timestamp: ../src/lang/dutch.txt
src/lang/strings.h.timestamp: ../src/lang/english.txt
src/lang/strings.h.timestamp: ../src/lang/english_AU.txt
src/lang/strings.h.timestamp: ../src/lang/english_US.txt
src/lang/strings.h.timestamp: ../src/lang/esperanto.txt
src/lang/strings.h.timestamp: ../src/lang/estonian.txt
src/lang/strings.h.timestamp: ../src/lang/faroese.txt
src/lang/strings.h.timestamp: ../src/lang/finnish.txt
src/lang/strings.h.timestamp: ../src/lang/french.txt
src/lang/strings.h.timestamp: ../src/lang/gaelic.txt
src/lang/strings.h.timestamp: ../src/lang/galician.txt
src/lang/strings.h.timestamp: ../src/lang/german.txt
src/lang/strings.h.timestamp: ../src/lang/greek.txt
src/lang/strings.h.timestamp: ../src/lang/hebrew.txt
src/lang/strings.h.timestamp: ../src/lang/hungarian.txt
src/lang/strings.h.timestamp: ../src/lang/icelandic.txt
src/lang/strings.h.timestamp: ../src/lang/indonesian.txt
src/lang/strings.h.timestamp: ../src/lang/irish.txt
src/lang/strings.h.timestamp: ../src/lang/italian.txt
src/lang/strings.h.timestamp: ../src/lang/japanese.txt
src/lang/strings.h.timestamp: ../src/lang/korean.txt
src/lang/strings.h.timestamp: ../src/lang/latin.txt
src/lang/strings.h.timestamp: ../src/lang/latvian.txt
src/lang/strings.h.timestamp: ../src/lang/lithuanian.txt
src/lang/strings.h.timestamp: ../src/lang/luxembourgish.txt
src/lang/strings.h.timestamp: ../src/lang/malay.txt
src/lang/strings.h.timestamp: ../src/lang/norwegian_bokmal.txt
src/lang/strings.h.timestamp: ../src/lang/norwegian_nynorsk.txt
src/lang/strings.h.timestamp: ../src/lang/polish.txt
src/lang/strings.h.timestamp: ../src/lang/portuguese.txt
src/lang/strings.h.timestamp: ../src/lang/romanian.txt
src/lang/strings.h.timestamp: ../src/lang/russian.txt
src/lang/strings.h.timestamp: ../src/lang/serbian.txt
src/lang/strings.h.timestamp: ../src/lang/simplified_chinese.txt
src/lang/strings.h.timestamp: ../src/lang/slovak.txt
src/lang/strings.h.timestamp: ../src/lang/slovenian.txt
src/lang/strings.h.timestamp: ../src/lang/spanish.txt
src/lang/strings.h.timestamp: ../src/lang/spanish_MX.txt
src/lang/strings.h.timestamp: ../src/lang/swedish.txt
src/lang/strings.h.timestamp: ../src/lang/tamil.txt
src/lang/strings.h.timestamp: ../src/lang/thai.txt
src/lang/strings.h.timestamp: ../src/lang/traditional_chinese.txt
src/lang/strings.h.timestamp: ../src/lang/turkish.txt
src/lang/strings.h.timestamp: ../src/lang/ukrainian.txt
src/lang/strings.h.timestamp: ../src/lang/vietnamese.txt
src/lang/strings.h.timestamp: ../src/lang/welsh.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/__w/OpenTTD-modded/OpenTTD-modded/em_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating table/strings.h"
	cd /__w/OpenTTD-modded/OpenTTD-modded/em_build/src/lang && /usr/bin/cmake -E make_directory /__w/OpenTTD-modded/OpenTTD-modded/em_build/generated/table
	cd /__w/OpenTTD-modded/OpenTTD-modded/em_build/src/lang && /__w/OpenTTD-modded/OpenTTD-modded/em_build/host_tools/src/strgen/strgen -s /__w/OpenTTD-modded/OpenTTD-modded/src/lang -d /__w/OpenTTD-modded/OpenTTD-modded/em_build/generated/table
	cd /__w/OpenTTD-modded/OpenTTD-modded/em_build/src/lang && /usr/bin/cmake -E touch /__w/OpenTTD-modded/OpenTTD-modded/em_build/src/lang/strings.h.timestamp

table_strings: src/lang/CMakeFiles/table_strings
table_strings: src/lang/strings.h.timestamp
table_strings: src/lang/CMakeFiles/table_strings.dir/build.make

.PHONY : table_strings

# Rule to build all files generated by this target.
src/lang/CMakeFiles/table_strings.dir/build: table_strings

.PHONY : src/lang/CMakeFiles/table_strings.dir/build

src/lang/CMakeFiles/table_strings.dir/clean:
	cd /__w/OpenTTD-modded/OpenTTD-modded/em_build/src/lang && $(CMAKE_COMMAND) -P CMakeFiles/table_strings.dir/cmake_clean.cmake
.PHONY : src/lang/CMakeFiles/table_strings.dir/clean

src/lang/CMakeFiles/table_strings.dir/depend:
	cd /__w/OpenTTD-modded/OpenTTD-modded/em_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /__w/OpenTTD-modded/OpenTTD-modded /__w/OpenTTD-modded/OpenTTD-modded/src/lang /__w/OpenTTD-modded/OpenTTD-modded/em_build /__w/OpenTTD-modded/OpenTTD-modded/em_build/src/lang /__w/OpenTTD-modded/OpenTTD-modded/em_build/src/lang/CMakeFiles/table_strings.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lang/CMakeFiles/table_strings.dir/depend

