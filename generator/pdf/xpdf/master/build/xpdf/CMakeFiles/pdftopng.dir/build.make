# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/lib/python2.7/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python2.7/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/youwei/MemFuzz/generator/pdf/xpdf/master/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/youwei/MemFuzz/generator/pdf/xpdf/master/build

# Include any dependencies generated for this target.
include xpdf/CMakeFiles/pdftopng.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include xpdf/CMakeFiles/pdftopng.dir/compiler_depend.make

# Include the progress variables for this target.
include xpdf/CMakeFiles/pdftopng.dir/progress.make

# Include the compile flags for this target's objects.
include xpdf/CMakeFiles/pdftopng.dir/flags.make

xpdf/CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o: xpdf/CMakeFiles/pdftopng.dir/flags.make
xpdf/CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o: /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf/SplashOutputDev.cc
xpdf/CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o: xpdf/CMakeFiles/pdftopng.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object xpdf/CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o"
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT xpdf/CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o -MF CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o.d -o CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o -c /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf/SplashOutputDev.cc

xpdf/CMakeFiles/pdftopng.dir/SplashOutputDev.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pdftopng.dir/SplashOutputDev.cc.i"
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf/SplashOutputDev.cc > CMakeFiles/pdftopng.dir/SplashOutputDev.cc.i

xpdf/CMakeFiles/pdftopng.dir/SplashOutputDev.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pdftopng.dir/SplashOutputDev.cc.s"
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf/SplashOutputDev.cc -o CMakeFiles/pdftopng.dir/SplashOutputDev.cc.s

xpdf/CMakeFiles/pdftopng.dir/pdftopng.cc.o: xpdf/CMakeFiles/pdftopng.dir/flags.make
xpdf/CMakeFiles/pdftopng.dir/pdftopng.cc.o: /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf/pdftopng.cc
xpdf/CMakeFiles/pdftopng.dir/pdftopng.cc.o: xpdf/CMakeFiles/pdftopng.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object xpdf/CMakeFiles/pdftopng.dir/pdftopng.cc.o"
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT xpdf/CMakeFiles/pdftopng.dir/pdftopng.cc.o -MF CMakeFiles/pdftopng.dir/pdftopng.cc.o.d -o CMakeFiles/pdftopng.dir/pdftopng.cc.o -c /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf/pdftopng.cc

xpdf/CMakeFiles/pdftopng.dir/pdftopng.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pdftopng.dir/pdftopng.cc.i"
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf/pdftopng.cc > CMakeFiles/pdftopng.dir/pdftopng.cc.i

xpdf/CMakeFiles/pdftopng.dir/pdftopng.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pdftopng.dir/pdftopng.cc.s"
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf/pdftopng.cc -o CMakeFiles/pdftopng.dir/pdftopng.cc.s

# Object files for target pdftopng
pdftopng_OBJECTS = \
"CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o" \
"CMakeFiles/pdftopng.dir/pdftopng.cc.o"

# External object files for target pdftopng
pdftopng_EXTERNAL_OBJECTS = \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/AcroForm.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Annot.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Array.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/BuiltinFont.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/BuiltinFontTables.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Catalog.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/CharCodeToUnicode.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/CMap.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Decrypt.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Dict.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Error.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/FontEncodingTables.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Form.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Function.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Gfx.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/GfxFont.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/GfxState.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/GlobalParams.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/JArithmeticDecoder.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/JBIG2Stream.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/JPXStream.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Lexer.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Link.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/NameToCharCode.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Object.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/OptionalContent.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Outline.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/OutputDev.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Page.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Parser.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/PDF417Barcode.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/PDFDoc.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/PDFDocEncoding.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/PSTokenizer.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/SecurityHandler.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Stream.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/TextString.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/UnicodeMap.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/UnicodeRemapping.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/UnicodeTypeTable.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/UTF8.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/XFAForm.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/XRef.cc.o" \
"/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/xpdf_objs.dir/Zoox.cc.o"

xpdf/pdftopng: xpdf/CMakeFiles/pdftopng.dir/SplashOutputDev.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/pdftopng.dir/pdftopng.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/AcroForm.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Annot.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Array.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/BuiltinFont.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/BuiltinFontTables.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Catalog.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/CharCodeToUnicode.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/CMap.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Decrypt.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Dict.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Error.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/FontEncodingTables.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Form.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Function.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Gfx.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/GfxFont.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/GfxState.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/GlobalParams.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/JArithmeticDecoder.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/JBIG2Stream.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/JPXStream.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Lexer.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Link.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/NameToCharCode.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Object.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/OptionalContent.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Outline.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/OutputDev.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Page.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Parser.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/PDF417Barcode.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/PDFDoc.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/PDFDocEncoding.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/PSTokenizer.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/SecurityHandler.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Stream.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/TextString.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/UnicodeMap.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/UnicodeRemapping.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/UnicodeTypeTable.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/UTF8.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/XFAForm.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/XRef.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/xpdf_objs.dir/Zoox.cc.o
xpdf/pdftopng: xpdf/CMakeFiles/pdftopng.dir/build.make
xpdf/pdftopng: goo/libgoo.a
xpdf/pdftopng: fofi/libfofi.a
xpdf/pdftopng: splash/libsplash.a
xpdf/pdftopng: /usr/lib/x86_64-linux-gnu/libfreetype.so
xpdf/pdftopng: /usr/lib/x86_64-linux-gnu/libpng.so
xpdf/pdftopng: /usr/lib/x86_64-linux-gnu/libz.so
xpdf/pdftopng: /usr/lib/x86_64-linux-gnu/libfontconfig.so
xpdf/pdftopng: xpdf/CMakeFiles/pdftopng.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/youwei/MemFuzz/generator/pdf/xpdf/master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable pdftopng"
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pdftopng.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
xpdf/CMakeFiles/pdftopng.dir/build: xpdf/pdftopng
.PHONY : xpdf/CMakeFiles/pdftopng.dir/build

xpdf/CMakeFiles/pdftopng.dir/clean:
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf && $(CMAKE_COMMAND) -P CMakeFiles/pdftopng.dir/cmake_clean.cmake
.PHONY : xpdf/CMakeFiles/pdftopng.dir/clean

xpdf/CMakeFiles/pdftopng.dir/depend:
	cd /home/youwei/MemFuzz/generator/pdf/xpdf/master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/youwei/MemFuzz/generator/pdf/xpdf/master/src /home/youwei/MemFuzz/generator/pdf/xpdf/master/src/xpdf /home/youwei/MemFuzz/generator/pdf/xpdf/master/build /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf /home/youwei/MemFuzz/generator/pdf/xpdf/master/build/xpdf/CMakeFiles/pdftopng.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : xpdf/CMakeFiles/pdftopng.dir/depend

