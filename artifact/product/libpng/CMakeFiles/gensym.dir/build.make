# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/liu2598/MemFuzz/generator/png/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liu2598/MemFuzz/generator/png/src

# Utility rule file for gensym.

# Include any custom commands dependencies for this target.
include CMakeFiles/gensym.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gensym.dir/progress.make

CMakeFiles/gensym: libpng.sym

libpng.sym: scripts/sym.out
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/liu2598/MemFuzz/generator/png/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating libpng.sym"
	/usr/local/bin/cmake -E remove /home/liu2598/MemFuzz/generator/png/src/libpng.sym
	/usr/local/bin/cmake -E copy /home/liu2598/MemFuzz/generator/png/src/scripts/sym.out /home/liu2598/MemFuzz/generator/png/src/libpng.sym

scripts/sym.out: scripts/sym.c
scripts/sym.out: pnglibconf.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/liu2598/MemFuzz/generator/png/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating scripts/sym.out"
	/usr/local/bin/cmake -DINPUT=/home/liu2598/MemFuzz/generator/png/src/scripts/sym.c -DOUTPUT=/home/liu2598/MemFuzz/generator/png/src/scripts/sym.out -P /home/liu2598/MemFuzz/generator/png/src/scripts/genout.cmake

pnglibconf.h: pnglibconf.out
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/liu2598/MemFuzz/generator/png/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating pnglibconf.h"
	/usr/local/bin/cmake -DOUTPUT=pnglibconf.h -P /home/liu2598/MemFuzz/generator/png/src/scripts/gensrc.cmake

pnglibconf.out: pnglibconf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/liu2598/MemFuzz/generator/png/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating pnglibconf.out"
	/usr/local/bin/cmake -DINPUT=/home/liu2598/MemFuzz/generator/png/src/pnglibconf.c -DOUTPUT=/home/liu2598/MemFuzz/generator/png/src/pnglibconf.out -P /home/liu2598/MemFuzz/generator/png/src/scripts/genout.cmake

pnglibconf.c: scripts/pnglibconf.dfa
pnglibconf.c: scripts/options.awk
pnglibconf.c: pngconf.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/liu2598/MemFuzz/generator/png/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Generating pnglibconf.c"
	/usr/local/bin/cmake -DOUTPUT=pnglibconf.c -P /home/liu2598/MemFuzz/generator/png/src/scripts/gensrc.cmake

gensym: CMakeFiles/gensym
gensym: libpng.sym
gensym: pnglibconf.c
gensym: pnglibconf.h
gensym: pnglibconf.out
gensym: scripts/sym.out
gensym: CMakeFiles/gensym.dir/build.make
.PHONY : gensym

# Rule to build all files generated by this target.
CMakeFiles/gensym.dir/build: gensym
.PHONY : CMakeFiles/gensym.dir/build

CMakeFiles/gensym.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gensym.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gensym.dir/clean

CMakeFiles/gensym.dir/depend:
	cd /home/liu2598/MemFuzz/generator/png/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liu2598/MemFuzz/generator/png/src /home/liu2598/MemFuzz/generator/png/src /home/liu2598/MemFuzz/generator/png/src /home/liu2598/MemFuzz/generator/png/src /home/liu2598/MemFuzz/generator/png/src/CMakeFiles/gensym.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gensym.dir/depend
