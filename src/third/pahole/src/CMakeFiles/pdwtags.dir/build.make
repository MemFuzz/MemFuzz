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
CMAKE_SOURCE_DIR = /home/liu2598/MemFuzz/src/third/pahole/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liu2598/MemFuzz/src/third/pahole/src

# Include any dependencies generated for this target.
include CMakeFiles/pdwtags.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pdwtags.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pdwtags.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pdwtags.dir/flags.make

CMakeFiles/pdwtags.dir/pdwtags.c.o: CMakeFiles/pdwtags.dir/flags.make
CMakeFiles/pdwtags.dir/pdwtags.c.o: pdwtags.c
CMakeFiles/pdwtags.dir/pdwtags.c.o: CMakeFiles/pdwtags.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/src/third/pahole/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/pdwtags.dir/pdwtags.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/pdwtags.dir/pdwtags.c.o -MF CMakeFiles/pdwtags.dir/pdwtags.c.o.d -o CMakeFiles/pdwtags.dir/pdwtags.c.o -c /home/liu2598/MemFuzz/src/third/pahole/src/pdwtags.c

CMakeFiles/pdwtags.dir/pdwtags.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pdwtags.dir/pdwtags.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/src/third/pahole/src/pdwtags.c > CMakeFiles/pdwtags.dir/pdwtags.c.i

CMakeFiles/pdwtags.dir/pdwtags.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pdwtags.dir/pdwtags.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/src/third/pahole/src/pdwtags.c -o CMakeFiles/pdwtags.dir/pdwtags.c.s

# Object files for target pdwtags
pdwtags_OBJECTS = \
"CMakeFiles/pdwtags.dir/pdwtags.c.o"

# External object files for target pdwtags
pdwtags_EXTERNAL_OBJECTS =

pdwtags: CMakeFiles/pdwtags.dir/pdwtags.c.o
pdwtags: CMakeFiles/pdwtags.dir/build.make
pdwtags: libdwarves.so.1.0.0
pdwtags: /usr/lib/x86_64-linux-gnu/libdw.so
pdwtags: /usr/lib/x86_64-linux-gnu/libelf.so
pdwtags: /usr/lib/x86_64-linux-gnu/libz.so
pdwtags: CMakeFiles/pdwtags.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liu2598/MemFuzz/src/third/pahole/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable pdwtags"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pdwtags.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pdwtags.dir/build: pdwtags
.PHONY : CMakeFiles/pdwtags.dir/build

CMakeFiles/pdwtags.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pdwtags.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pdwtags.dir/clean

CMakeFiles/pdwtags.dir/depend:
	cd /home/liu2598/MemFuzz/src/third/pahole/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liu2598/MemFuzz/src/third/pahole/src /home/liu2598/MemFuzz/src/third/pahole/src /home/liu2598/MemFuzz/src/third/pahole/src /home/liu2598/MemFuzz/src/third/pahole/src /home/liu2598/MemFuzz/src/third/pahole/src/CMakeFiles/pdwtags.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pdwtags.dir/depend

