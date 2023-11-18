# Install script for directory: /home/liu2598/MemFuzz/src/third/gen_struct

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/pahole" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/pahole")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/pahole"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/pahole")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/pahole")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/pahole" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/pahole")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/pahole"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/pahole")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/pdwtags" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/pdwtags")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/pdwtags"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/pdwtags")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/pdwtags")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/pdwtags" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/pdwtags")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/pdwtags"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/pdwtags")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/pfunct" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/pfunct")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/pfunct"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/pfunct")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/pfunct")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/pfunct" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/pfunct")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/pfunct"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/pfunct")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/pglobal" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/pglobal")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/pglobal"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/pglobal")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/pglobal")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/pglobal" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/pglobal")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/pglobal"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/pglobal")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/prefcnt" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/prefcnt")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/prefcnt"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/prefcnt")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/prefcnt")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/prefcnt" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/prefcnt")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/prefcnt"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/prefcnt")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/scncopy" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/scncopy")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/scncopy"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/scncopy")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/scncopy")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/scncopy" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/scncopy")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/scncopy"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/scncopy")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/syscse" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/syscse")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/syscse"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/syscse")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/syscse")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/syscse" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/syscse")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/syscse"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/syscse")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}/usr/local/libdwarves.so.1.0.0"
      "$ENV{DESTDIR}/usr/local/libdwarves.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libdwarves.so.1.0.0;/usr/local/libdwarves.so.1")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local" TYPE SHARED_LIBRARY FILES
    "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves.so.1.0.0"
    "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}/usr/local/libdwarves.so.1.0.0"
      "$ENV{DESTDIR}/usr/local/libdwarves.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/libdwarves.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libdwarves.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/libdwarves.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libdwarves.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local" TYPE SHARED_LIBRARY FILES "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/libdwarves.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libdwarves.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/libdwarves.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}/usr/local/libdwarves.so.1.0.0"
      "$ENV{DESTDIR}/usr/local/libdwarves.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libdwarves.so.1.0.0;/usr/local/libdwarves.so.1")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local" TYPE SHARED_LIBRARY FILES
    "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves.so.1.0.0"
    "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}/usr/local/libdwarves.so.1.0.0"
      "$ENV{DESTDIR}/usr/local/libdwarves.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/libdwarves.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libdwarves.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/libdwarves.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libdwarves.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local" TYPE SHARED_LIBRARY FILES "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/libdwarves.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libdwarves.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/libdwarves.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}/usr/local/libdwarves_emit.so.1.0.0"
      "$ENV{DESTDIR}/usr/local/libdwarves_emit.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libdwarves_emit.so.1.0.0;/usr/local/libdwarves_emit.so.1")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local" TYPE SHARED_LIBRARY FILES
    "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves_emit.so.1.0.0"
    "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves_emit.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}/usr/local/libdwarves_emit.so.1.0.0"
      "$ENV{DESTDIR}/usr/local/libdwarves_emit.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/libdwarves_emit.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libdwarves_emit.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/libdwarves_emit.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libdwarves_emit.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local" TYPE SHARED_LIBRARY FILES "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves_emit.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/libdwarves_emit.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libdwarves_emit.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/libdwarves_emit.so"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/libdwarves_emit.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so.1.0.0"
      "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libdwarves_reorganize.so.1.0.0;/usr/local/libdwarves_reorganize.so.1")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local" TYPE SHARED_LIBRARY FILES
    "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves_reorganize.so.1.0.0"
    "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves_reorganize.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so.1.0.0"
      "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/libdwarves_reorganize.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local" TYPE SHARED_LIBRARY FILES "/home/liu2598/MemFuzz/src/third/gen_struct/libdwarves_reorganize.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so"
         OLD_RPATH "/home/liu2598/MemFuzz/src/third/gen_struct:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/libdwarves_reorganize.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/dwarves/dwarves.h;/usr/local/include/dwarves/dwarves_emit.h;/usr/local/include/dwarves/dwarves_reorganize.h;/usr/local/include/dwarves/dutil.h;/usr/local/include/dwarves/gobuffer.h;/usr/local/include/dwarves/list.h;/usr/local/include/dwarves/rbtree.h;/usr/local/include/dwarves/pahole_strings.h;/usr/local/include/dwarves/btf_encoder.h;/usr/local/include/dwarves/config.h;/usr/local/include/dwarves/ctf_encoder.h;/usr/local/include/dwarves/ctf.h;/usr/local/include/dwarves/elfcreator.h;/usr/local/include/dwarves/elf_symtab.h;/usr/local/include/dwarves/hash.h;/usr/local/include/dwarves/libbtf.h;/usr/local/include/dwarves/libctf.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/include/dwarves" TYPE FILE FILES
    "/home/liu2598/MemFuzz/src/third/gen_struct/dwarves.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/dwarves_emit.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/dwarves_reorganize.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/dutil.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/gobuffer.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/list.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/rbtree.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/pahole_strings.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/btf_encoder.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/config.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/ctf_encoder.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/ctf.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/elfcreator.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/elf_symtab.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/hash.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/libbtf.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/libctf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/man/man1/pahole.1")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/share/man/man1" TYPE FILE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/man-pages/pahole.1")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/ostra-cg")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE PROGRAM FILES "/home/liu2598/MemFuzz/src/third/gen_struct/ostra/ostra-cg")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/btfdiff;/usr/local/bin/fullcircle")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE PROGRAM FILES
    "/home/liu2598/MemFuzz/src/third/gen_struct/btfdiff"
    "/home/liu2598/MemFuzz/src/third/gen_struct/fullcircle"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/dwarves/runtime/python/ostra.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/share/dwarves/runtime/python" TYPE FILE FILES "/home/liu2598/MemFuzz/src/third/gen_struct/ostra/python/ostra.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/dwarves/runtime/Makefile;/usr/local/share/dwarves/runtime/ctracer_relay.c;/usr/local/share/dwarves/runtime/ctracer_relay.h;/usr/local/share/dwarves/runtime/linux.blacklist.cu")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/share/dwarves/runtime" TYPE FILE FILES
    "/home/liu2598/MemFuzz/src/third/gen_struct/lib/Makefile"
    "/home/liu2598/MemFuzz/src/third/gen_struct/lib/ctracer_relay.c"
    "/home/liu2598/MemFuzz/src/third/gen_struct/lib/ctracer_relay.h"
    "/home/liu2598/MemFuzz/src/third/gen_struct/lib/linux.blacklist.cu"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/liu2598/MemFuzz/src/third/gen_struct/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
