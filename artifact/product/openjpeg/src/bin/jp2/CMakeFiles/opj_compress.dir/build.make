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
CMAKE_SOURCE_DIR = /home/liu2598/MemFuzz/generator/jp2/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liu2598/MemFuzz/generator/jp2/src

# Include any dependencies generated for this target.
include src/bin/jp2/CMakeFiles/opj_compress.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.make

# Include the progress variables for this target.
include src/bin/jp2/CMakeFiles/opj_compress.dir/progress.make

# Include the compile flags for this target's objects.
include src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make

src/bin/jp2/CMakeFiles/opj_compress.dir/opj_compress.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make
src/bin/jp2/CMakeFiles/opj_compress.dir/opj_compress.c.o: src/bin/jp2/opj_compress.c
src/bin/jp2/CMakeFiles/opj_compress.dir/opj_compress.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/bin/jp2/CMakeFiles/opj_compress.dir/opj_compress.c.o"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/bin/jp2/CMakeFiles/opj_compress.dir/opj_compress.c.o -MF CMakeFiles/opj_compress.dir/opj_compress.c.o.d -o CMakeFiles/opj_compress.dir/opj_compress.c.o -c /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/opj_compress.c

src/bin/jp2/CMakeFiles/opj_compress.dir/opj_compress.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opj_compress.dir/opj_compress.c.i"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/opj_compress.c > CMakeFiles/opj_compress.dir/opj_compress.c.i

src/bin/jp2/CMakeFiles/opj_compress.dir/opj_compress.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opj_compress.dir/opj_compress.c.s"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/opj_compress.c -o CMakeFiles/opj_compress.dir/opj_compress.c.s

src/bin/jp2/CMakeFiles/opj_compress.dir/convert.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make
src/bin/jp2/CMakeFiles/opj_compress.dir/convert.c.o: src/bin/jp2/convert.c
src/bin/jp2/CMakeFiles/opj_compress.dir/convert.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/bin/jp2/CMakeFiles/opj_compress.dir/convert.c.o"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/bin/jp2/CMakeFiles/opj_compress.dir/convert.c.o -MF CMakeFiles/opj_compress.dir/convert.c.o.d -o CMakeFiles/opj_compress.dir/convert.c.o -c /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convert.c

src/bin/jp2/CMakeFiles/opj_compress.dir/convert.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opj_compress.dir/convert.c.i"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convert.c > CMakeFiles/opj_compress.dir/convert.c.i

src/bin/jp2/CMakeFiles/opj_compress.dir/convert.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opj_compress.dir/convert.c.s"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convert.c -o CMakeFiles/opj_compress.dir/convert.c.s

src/bin/jp2/CMakeFiles/opj_compress.dir/convertbmp.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make
src/bin/jp2/CMakeFiles/opj_compress.dir/convertbmp.c.o: src/bin/jp2/convertbmp.c
src/bin/jp2/CMakeFiles/opj_compress.dir/convertbmp.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/bin/jp2/CMakeFiles/opj_compress.dir/convertbmp.c.o"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/bin/jp2/CMakeFiles/opj_compress.dir/convertbmp.c.o -MF CMakeFiles/opj_compress.dir/convertbmp.c.o.d -o CMakeFiles/opj_compress.dir/convertbmp.c.o -c /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convertbmp.c

src/bin/jp2/CMakeFiles/opj_compress.dir/convertbmp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opj_compress.dir/convertbmp.c.i"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convertbmp.c > CMakeFiles/opj_compress.dir/convertbmp.c.i

src/bin/jp2/CMakeFiles/opj_compress.dir/convertbmp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opj_compress.dir/convertbmp.c.s"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convertbmp.c -o CMakeFiles/opj_compress.dir/convertbmp.c.s

src/bin/jp2/CMakeFiles/opj_compress.dir/index.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make
src/bin/jp2/CMakeFiles/opj_compress.dir/index.c.o: src/bin/jp2/index.c
src/bin/jp2/CMakeFiles/opj_compress.dir/index.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/bin/jp2/CMakeFiles/opj_compress.dir/index.c.o"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/bin/jp2/CMakeFiles/opj_compress.dir/index.c.o -MF CMakeFiles/opj_compress.dir/index.c.o.d -o CMakeFiles/opj_compress.dir/index.c.o -c /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/index.c

src/bin/jp2/CMakeFiles/opj_compress.dir/index.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opj_compress.dir/index.c.i"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/index.c > CMakeFiles/opj_compress.dir/index.c.i

src/bin/jp2/CMakeFiles/opj_compress.dir/index.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opj_compress.dir/index.c.s"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/index.c -o CMakeFiles/opj_compress.dir/index.c.s

src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/color.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make
src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/color.c.o: src/bin/common/color.c
src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/color.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/color.c.o"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/color.c.o -MF CMakeFiles/opj_compress.dir/__/common/color.c.o.d -o CMakeFiles/opj_compress.dir/__/common/color.c.o -c /home/liu2598/MemFuzz/generator/jp2/src/src/bin/common/color.c

src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/color.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opj_compress.dir/__/common/color.c.i"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/jp2/src/src/bin/common/color.c > CMakeFiles/opj_compress.dir/__/common/color.c.i

src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/color.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opj_compress.dir/__/common/color.c.s"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/jp2/src/src/bin/common/color.c -o CMakeFiles/opj_compress.dir/__/common/color.c.s

src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make
src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o: src/bin/common/opj_getopt.c
src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o -MF CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o.d -o CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o -c /home/liu2598/MemFuzz/generator/jp2/src/src/bin/common/opj_getopt.c

src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.i"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/jp2/src/src/bin/common/opj_getopt.c > CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.i

src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.s"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/jp2/src/src/bin/common/opj_getopt.c -o CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.s

src/bin/jp2/CMakeFiles/opj_compress.dir/converttif.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make
src/bin/jp2/CMakeFiles/opj_compress.dir/converttif.c.o: src/bin/jp2/converttif.c
src/bin/jp2/CMakeFiles/opj_compress.dir/converttif.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/bin/jp2/CMakeFiles/opj_compress.dir/converttif.c.o"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/bin/jp2/CMakeFiles/opj_compress.dir/converttif.c.o -MF CMakeFiles/opj_compress.dir/converttif.c.o.d -o CMakeFiles/opj_compress.dir/converttif.c.o -c /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/converttif.c

src/bin/jp2/CMakeFiles/opj_compress.dir/converttif.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opj_compress.dir/converttif.c.i"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/converttif.c > CMakeFiles/opj_compress.dir/converttif.c.i

src/bin/jp2/CMakeFiles/opj_compress.dir/converttif.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opj_compress.dir/converttif.c.s"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/converttif.c -o CMakeFiles/opj_compress.dir/converttif.c.s

src/bin/jp2/CMakeFiles/opj_compress.dir/convertpng.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/flags.make
src/bin/jp2/CMakeFiles/opj_compress.dir/convertpng.c.o: src/bin/jp2/convertpng.c
src/bin/jp2/CMakeFiles/opj_compress.dir/convertpng.c.o: src/bin/jp2/CMakeFiles/opj_compress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/bin/jp2/CMakeFiles/opj_compress.dir/convertpng.c.o"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/bin/jp2/CMakeFiles/opj_compress.dir/convertpng.c.o -MF CMakeFiles/opj_compress.dir/convertpng.c.o.d -o CMakeFiles/opj_compress.dir/convertpng.c.o -c /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convertpng.c

src/bin/jp2/CMakeFiles/opj_compress.dir/convertpng.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opj_compress.dir/convertpng.c.i"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convertpng.c > CMakeFiles/opj_compress.dir/convertpng.c.i

src/bin/jp2/CMakeFiles/opj_compress.dir/convertpng.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opj_compress.dir/convertpng.c.s"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/convertpng.c -o CMakeFiles/opj_compress.dir/convertpng.c.s

# Object files for target opj_compress
opj_compress_OBJECTS = \
"CMakeFiles/opj_compress.dir/opj_compress.c.o" \
"CMakeFiles/opj_compress.dir/convert.c.o" \
"CMakeFiles/opj_compress.dir/convertbmp.c.o" \
"CMakeFiles/opj_compress.dir/index.c.o" \
"CMakeFiles/opj_compress.dir/__/common/color.c.o" \
"CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o" \
"CMakeFiles/opj_compress.dir/converttif.c.o" \
"CMakeFiles/opj_compress.dir/convertpng.c.o"

# External object files for target opj_compress
opj_compress_EXTERNAL_OBJECTS =

bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/opj_compress.c.o
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/convert.c.o
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/convertbmp.c.o
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/index.c.o
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/color.c.o
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/__/common/opj_getopt.c.o
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/converttif.c.o
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/convertpng.c.o
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/build.make
bin/opj_compress: bin/libopenjp2.a
bin/opj_compress: /usr/lib/x86_64-linux-gnu/libpng.so
bin/opj_compress: /usr/lib/x86_64-linux-gnu/libz.so
bin/opj_compress: /usr/lib/x86_64-linux-gnu/libtiff.so
bin/opj_compress: /usr/lib/x86_64-linux-gnu/liblcms2.so
bin/opj_compress: /usr/lib/x86_64-linux-gnu/libz.so
bin/opj_compress: /usr/lib/x86_64-linux-gnu/libtiff.so
bin/opj_compress: /usr/lib/x86_64-linux-gnu/liblcms2.so
bin/opj_compress: src/bin/jp2/CMakeFiles/opj_compress.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liu2598/MemFuzz/generator/jp2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable ../../../bin/opj_compress"
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opj_compress.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/bin/jp2/CMakeFiles/opj_compress.dir/build: bin/opj_compress
.PHONY : src/bin/jp2/CMakeFiles/opj_compress.dir/build

src/bin/jp2/CMakeFiles/opj_compress.dir/clean:
	cd /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 && $(CMAKE_COMMAND) -P CMakeFiles/opj_compress.dir/cmake_clean.cmake
.PHONY : src/bin/jp2/CMakeFiles/opj_compress.dir/clean

src/bin/jp2/CMakeFiles/opj_compress.dir/depend:
	cd /home/liu2598/MemFuzz/generator/jp2/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liu2598/MemFuzz/generator/jp2/src /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 /home/liu2598/MemFuzz/generator/jp2/src /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2 /home/liu2598/MemFuzz/generator/jp2/src/src/bin/jp2/CMakeFiles/opj_compress.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/bin/jp2/CMakeFiles/opj_compress.dir/depend
