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
CMAKE_SOURCE_DIR = /home/liu2598/MemFuzz/src/third/gen_struct

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liu2598/MemFuzz/src/third/gen_struct

# Include any dependencies generated for this target.
include CMakeFiles/dwarves_reorganize.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dwarves_reorganize.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dwarves_reorganize.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dwarves_reorganize.dir/flags.make

CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o: CMakeFiles/dwarves_reorganize.dir/flags.make
CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o: dwarves_reorganize.c
CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o: CMakeFiles/dwarves_reorganize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/src/third/gen_struct/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o -MF CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o.d -o CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o -c /home/liu2598/MemFuzz/src/third/gen_struct/dwarves_reorganize.c

CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/src/third/gen_struct/dwarves_reorganize.c > CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.i

CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/src/third/gen_struct/dwarves_reorganize.c -o CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.s

# Object files for target dwarves_reorganize
dwarves_reorganize_OBJECTS = \
"CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o"

# External object files for target dwarves_reorganize
dwarves_reorganize_EXTERNAL_OBJECTS =

libdwarves_reorganize.so.1.0.0: CMakeFiles/dwarves_reorganize.dir/dwarves_reorganize.c.o
libdwarves_reorganize.so.1.0.0: CMakeFiles/dwarves_reorganize.dir/build.make
libdwarves_reorganize.so.1.0.0: libdwarves.so.1.0.0
libdwarves_reorganize.so.1.0.0: /usr/lib/x86_64-linux-gnu/libdw.so
libdwarves_reorganize.so.1.0.0: /usr/lib/x86_64-linux-gnu/libelf.so
libdwarves_reorganize.so.1.0.0: /usr/lib/x86_64-linux-gnu/libz.so
libdwarves_reorganize.so.1.0.0: CMakeFiles/dwarves_reorganize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liu2598/MemFuzz/src/third/gen_struct/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libdwarves_reorganize.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dwarves_reorganize.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libdwarves_reorganize.so.1.0.0 libdwarves_reorganize.so.1 libdwarves_reorganize.so

libdwarves_reorganize.so.1: libdwarves_reorganize.so.1.0.0
	@$(CMAKE_COMMAND) -E touch_nocreate libdwarves_reorganize.so.1

libdwarves_reorganize.so: libdwarves_reorganize.so.1.0.0
	@$(CMAKE_COMMAND) -E touch_nocreate libdwarves_reorganize.so

# Rule to build all files generated by this target.
CMakeFiles/dwarves_reorganize.dir/build: libdwarves_reorganize.so
.PHONY : CMakeFiles/dwarves_reorganize.dir/build

CMakeFiles/dwarves_reorganize.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dwarves_reorganize.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dwarves_reorganize.dir/clean

CMakeFiles/dwarves_reorganize.dir/depend:
	cd /home/liu2598/MemFuzz/src/third/gen_struct && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liu2598/MemFuzz/src/third/gen_struct /home/liu2598/MemFuzz/src/third/gen_struct /home/liu2598/MemFuzz/src/third/gen_struct /home/liu2598/MemFuzz/src/third/gen_struct /home/liu2598/MemFuzz/src/third/gen_struct/CMakeFiles/dwarves_reorganize.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dwarves_reorganize.dir/depend

