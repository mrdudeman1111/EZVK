# Install script for directory: /home/ethan/Repos/VulkanWrapper/sail/src/libsail-common

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
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
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so.0.9.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/libsail-common.so.0.9.2"
    "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/libsail-common.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so.0.9.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so.0"
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/libsail-common.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-common.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/sail/sail-common" TYPE FILE FILES
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/common.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/common_serialize.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/compiler_specifics.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/compression_level.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/error.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/export.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/hash_map.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/iccp.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/image.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/io_common.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/load_features.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/load_options.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/log.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/memory.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/meta_data.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/meta_data_node.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/palette.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/pixel.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/resolution.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/sail-common.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/save_features.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/save_options.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/source_image.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/string_node.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/utils.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/variant.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/libsail-common/variant_node.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/libsail-common.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sailcommon/SailCommonTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sailcommon/SailCommonTargets.cmake"
         "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/CMakeFiles/Export/562481cd46f674124a1a026f224d69ea/SailCommonTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sailcommon/SailCommonTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sailcommon/SailCommonTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sailcommon" TYPE FILE FILES "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/CMakeFiles/Export/562481cd46f674124a1a026f224d69ea/SailCommonTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sailcommon" TYPE FILE FILES "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/CMakeFiles/Export/562481cd46f674124a1a026f224d69ea/SailCommonTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sailcommon" TYPE FILE FILES
    "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/SailCommonConfig.cmake"
    "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common/SailCommonConfigVersion.cmake"
    )
endif()

