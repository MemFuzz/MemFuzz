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
CMAKE_SOURCE_DIR = /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf

# Include any dependencies generated for this target.
include CMakeFiles/pdfinfo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pdfinfo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pdfinfo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pdfinfo.dir/flags.make

CMakeFiles/pdfinfo.dir/pdfinfo.o: CMakeFiles/pdfinfo.dir/flags.make
CMakeFiles/pdfinfo.dir/pdfinfo.o: pdfinfo.cc
CMakeFiles/pdfinfo.dir/pdfinfo.o: CMakeFiles/pdfinfo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pdfinfo.dir/pdfinfo.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pdfinfo.dir/pdfinfo.o -MF CMakeFiles/pdfinfo.dir/pdfinfo.o.d -o CMakeFiles/pdfinfo.dir/pdfinfo.o -c /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/pdfinfo.cc

CMakeFiles/pdfinfo.dir/pdfinfo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pdfinfo.dir/pdfinfo.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/pdfinfo.cc > CMakeFiles/pdfinfo.dir/pdfinfo.i

CMakeFiles/pdfinfo.dir/pdfinfo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pdfinfo.dir/pdfinfo.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/pdfinfo.cc -o CMakeFiles/pdfinfo.dir/pdfinfo.s

# Object files for target pdfinfo
pdfinfo_OBJECTS = \
"CMakeFiles/pdfinfo.dir/pdfinfo.o"

# External object files for target pdfinfo
pdfinfo_EXTERNAL_OBJECTS = \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/AcroForm.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Annot.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Array.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/BuiltinFont.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/BuiltinFontTables.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Catalog.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/CharCodeToUnicode.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/CMap.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Decrypt.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Dict.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Error.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/FontEncodingTables.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Form.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Function.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Gfx.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/GfxFont.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/GfxState.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/GlobalParams.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/JArithmeticDecoder.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/JBIG2Stream.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/JPXStream.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Lexer.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Link.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/NameToCharCode.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Object.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/OptionalContent.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Outline.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/OutputDev.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Page.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Parser.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/PDF417Barcode.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/PDFDoc.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/PDFDocEncoding.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/PSTokenizer.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/SecurityHandler.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Stream.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/TextString.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/UnicodeMap.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/UnicodeRemapping.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/UnicodeTypeTable.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/UTF8.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/XFAForm.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/XRef.o" \
"/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/xpdf_objs.dir/Zoox.o"

pdfinfo: CMakeFiles/pdfinfo.dir/pdfinfo.o
pdfinfo: CMakeFiles/xpdf_objs.dir/AcroForm.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Annot.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Array.o
pdfinfo: CMakeFiles/xpdf_objs.dir/BuiltinFont.o
pdfinfo: CMakeFiles/xpdf_objs.dir/BuiltinFontTables.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Catalog.o
pdfinfo: CMakeFiles/xpdf_objs.dir/CharCodeToUnicode.o
pdfinfo: CMakeFiles/xpdf_objs.dir/CMap.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Decrypt.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Dict.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Error.o
pdfinfo: CMakeFiles/xpdf_objs.dir/FontEncodingTables.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Form.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Function.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Gfx.o
pdfinfo: CMakeFiles/xpdf_objs.dir/GfxFont.o
pdfinfo: CMakeFiles/xpdf_objs.dir/GfxState.o
pdfinfo: CMakeFiles/xpdf_objs.dir/GlobalParams.o
pdfinfo: CMakeFiles/xpdf_objs.dir/JArithmeticDecoder.o
pdfinfo: CMakeFiles/xpdf_objs.dir/JBIG2Stream.o
pdfinfo: CMakeFiles/xpdf_objs.dir/JPXStream.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Lexer.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Link.o
pdfinfo: CMakeFiles/xpdf_objs.dir/NameToCharCode.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Object.o
pdfinfo: CMakeFiles/xpdf_objs.dir/OptionalContent.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Outline.o
pdfinfo: CMakeFiles/xpdf_objs.dir/OutputDev.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Page.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Parser.o
pdfinfo: CMakeFiles/xpdf_objs.dir/PDF417Barcode.o
pdfinfo: CMakeFiles/xpdf_objs.dir/PDFDoc.o
pdfinfo: CMakeFiles/xpdf_objs.dir/PDFDocEncoding.o
pdfinfo: CMakeFiles/xpdf_objs.dir/PSTokenizer.o
pdfinfo: CMakeFiles/xpdf_objs.dir/SecurityHandler.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Stream.o
pdfinfo: CMakeFiles/xpdf_objs.dir/TextString.o
pdfinfo: CMakeFiles/xpdf_objs.dir/UnicodeMap.o
pdfinfo: CMakeFiles/xpdf_objs.dir/UnicodeRemapping.o
pdfinfo: CMakeFiles/xpdf_objs.dir/UnicodeTypeTable.o
pdfinfo: CMakeFiles/xpdf_objs.dir/UTF8.o
pdfinfo: CMakeFiles/xpdf_objs.dir/XFAForm.o
pdfinfo: CMakeFiles/xpdf_objs.dir/XRef.o
pdfinfo: CMakeFiles/xpdf_objs.dir/Zoox.o
pdfinfo: CMakeFiles/pdfinfo.dir/build.make
pdfinfo: CMakeFiles/pdfinfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pdfinfo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pdfinfo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pdfinfo.dir/build: pdfinfo
.PHONY : CMakeFiles/pdfinfo.dir/build

CMakeFiles/pdfinfo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pdfinfo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pdfinfo.dir/clean

CMakeFiles/pdfinfo.dir/depend:
	cd /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf /home/liu2598/MemFuzz/generator/pdf/xpdf/master/src/xpdf/CMakeFiles/pdfinfo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pdfinfo.dir/depend
