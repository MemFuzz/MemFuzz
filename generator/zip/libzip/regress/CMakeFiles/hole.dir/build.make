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
CMAKE_SOURCE_DIR = /home/liu2598/MemFuzz/generator/zip/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liu2598/MemFuzz/generator/zip/src

# Include any dependencies generated for this target.
include regress/CMakeFiles/hole.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include regress/CMakeFiles/hole.dir/compiler_depend.make

# Include the progress variables for this target.
include regress/CMakeFiles/hole.dir/progress.make

# Include the compile flags for this target's objects.
include regress/CMakeFiles/hole.dir/flags.make

regress/CMakeFiles/hole.dir/hole.c.o: regress/CMakeFiles/hole.dir/flags.make
regress/CMakeFiles/hole.dir/hole.c.o: regress/hole.c
regress/CMakeFiles/hole.dir/hole.c.o: regress/CMakeFiles/hole.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/zip/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object regress/CMakeFiles/hole.dir/hole.c.o"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT regress/CMakeFiles/hole.dir/hole.c.o -MF CMakeFiles/hole.dir/hole.c.o.d -o CMakeFiles/hole.dir/hole.c.o -c /home/liu2598/MemFuzz/generator/zip/src/regress/hole.c

regress/CMakeFiles/hole.dir/hole.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hole.dir/hole.c.i"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/zip/src/regress/hole.c > CMakeFiles/hole.dir/hole.c.i

regress/CMakeFiles/hole.dir/hole.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hole.dir/hole.c.s"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/zip/src/regress/hole.c -o CMakeFiles/hole.dir/hole.c.s

regress/CMakeFiles/hole.dir/source_hole.c.o: regress/CMakeFiles/hole.dir/flags.make
regress/CMakeFiles/hole.dir/source_hole.c.o: regress/source_hole.c
regress/CMakeFiles/hole.dir/source_hole.c.o: regress/CMakeFiles/hole.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/zip/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object regress/CMakeFiles/hole.dir/source_hole.c.o"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT regress/CMakeFiles/hole.dir/source_hole.c.o -MF CMakeFiles/hole.dir/source_hole.c.o.d -o CMakeFiles/hole.dir/source_hole.c.o -c /home/liu2598/MemFuzz/generator/zip/src/regress/source_hole.c

regress/CMakeFiles/hole.dir/source_hole.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hole.dir/source_hole.c.i"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/zip/src/regress/source_hole.c > CMakeFiles/hole.dir/source_hole.c.i

regress/CMakeFiles/hole.dir/source_hole.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hole.dir/source_hole.c.s"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/zip/src/regress/source_hole.c -o CMakeFiles/hole.dir/source_hole.c.s

# Object files for target hole
hole_OBJECTS = \
"CMakeFiles/hole.dir/hole.c.o" \
"CMakeFiles/hole.dir/source_hole.c.o"

# External object files for target hole
hole_EXTERNAL_OBJECTS =

regress/hole: regress/CMakeFiles/hole.dir/hole.c.o
regress/hole: regress/CMakeFiles/hole.dir/source_hole.c.o
regress/hole: regress/CMakeFiles/hole.dir/build.make
regress/hole: lib/libzip.a
regress/hole: /usr/lib/x86_64-linux-gnu/libbz2.so
regress/hole: /usr/lib/x86_64-linux-gnu/liblzma.so
regress/hole: /usr/lib/x86_64-linux-gnu/libcrypto.so
regress/hole: /usr/lib/x86_64-linux-gnu/libz.so
regress/hole: regress/CMakeFiles/hole.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liu2598/MemFuzz/generator/zip/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable hole"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hole.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
regress/CMakeFiles/hole.dir/build: regress/hole
.PHONY : regress/CMakeFiles/hole.dir/build

regress/CMakeFiles/hole.dir/clean:
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && $(CMAKE_COMMAND) -P CMakeFiles/hole.dir/cmake_clean.cmake
.PHONY : regress/CMakeFiles/hole.dir/clean

regress/CMakeFiles/hole.dir/depend:
	cd /home/liu2598/MemFuzz/generator/zip/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liu2598/MemFuzz/generator/zip/src /home/liu2598/MemFuzz/generator/zip/src/regress /home/liu2598/MemFuzz/generator/zip/src /home/liu2598/MemFuzz/generator/zip/src/regress /home/liu2598/MemFuzz/generator/zip/src/regress/CMakeFiles/hole.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : regress/CMakeFiles/hole.dir/depend

