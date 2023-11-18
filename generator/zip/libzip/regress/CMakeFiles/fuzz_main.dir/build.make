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
include regress/CMakeFiles/fuzz_main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include regress/CMakeFiles/fuzz_main.dir/compiler_depend.make

# Include the progress variables for this target.
include regress/CMakeFiles/fuzz_main.dir/progress.make

# Include the compile flags for this target's objects.
include regress/CMakeFiles/fuzz_main.dir/flags.make

regress/CMakeFiles/fuzz_main.dir/fuzz_main.c.o: regress/CMakeFiles/fuzz_main.dir/flags.make
regress/CMakeFiles/fuzz_main.dir/fuzz_main.c.o: regress/fuzz_main.c
regress/CMakeFiles/fuzz_main.dir/fuzz_main.c.o: regress/CMakeFiles/fuzz_main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/zip/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object regress/CMakeFiles/fuzz_main.dir/fuzz_main.c.o"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT regress/CMakeFiles/fuzz_main.dir/fuzz_main.c.o -MF CMakeFiles/fuzz_main.dir/fuzz_main.c.o.d -o CMakeFiles/fuzz_main.dir/fuzz_main.c.o -c /home/liu2598/MemFuzz/generator/zip/src/regress/fuzz_main.c

regress/CMakeFiles/fuzz_main.dir/fuzz_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fuzz_main.dir/fuzz_main.c.i"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/zip/src/regress/fuzz_main.c > CMakeFiles/fuzz_main.dir/fuzz_main.c.i

regress/CMakeFiles/fuzz_main.dir/fuzz_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fuzz_main.dir/fuzz_main.c.s"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/zip/src/regress/fuzz_main.c -o CMakeFiles/fuzz_main.dir/fuzz_main.c.s

# Object files for target fuzz_main
fuzz_main_OBJECTS = \
"CMakeFiles/fuzz_main.dir/fuzz_main.c.o"

# External object files for target fuzz_main
fuzz_main_EXTERNAL_OBJECTS =

regress/fuzz_main: regress/CMakeFiles/fuzz_main.dir/fuzz_main.c.o
regress/fuzz_main: regress/CMakeFiles/fuzz_main.dir/build.make
regress/fuzz_main: lib/libzip.a
regress/fuzz_main: /usr/lib/x86_64-linux-gnu/libbz2.so
regress/fuzz_main: /usr/lib/x86_64-linux-gnu/liblzma.so
regress/fuzz_main: /usr/lib/x86_64-linux-gnu/libcrypto.so
regress/fuzz_main: /usr/lib/x86_64-linux-gnu/libz.so
regress/fuzz_main: regress/CMakeFiles/fuzz_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liu2598/MemFuzz/generator/zip/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable fuzz_main"
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fuzz_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
regress/CMakeFiles/fuzz_main.dir/build: regress/fuzz_main
.PHONY : regress/CMakeFiles/fuzz_main.dir/build

regress/CMakeFiles/fuzz_main.dir/clean:
	cd /home/liu2598/MemFuzz/generator/zip/src/regress && $(CMAKE_COMMAND) -P CMakeFiles/fuzz_main.dir/cmake_clean.cmake
.PHONY : regress/CMakeFiles/fuzz_main.dir/clean

regress/CMakeFiles/fuzz_main.dir/depend:
	cd /home/liu2598/MemFuzz/generator/zip/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liu2598/MemFuzz/generator/zip/src /home/liu2598/MemFuzz/generator/zip/src/regress /home/liu2598/MemFuzz/generator/zip/src /home/liu2598/MemFuzz/generator/zip/src/regress /home/liu2598/MemFuzz/generator/zip/src/regress/CMakeFiles/fuzz_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : regress/CMakeFiles/fuzz_main.dir/depend
