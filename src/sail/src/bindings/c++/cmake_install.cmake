# Install script for directory: /home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so.0.7.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/libsail-c++.so.0.7.1"
    "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/libsail-c++.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so.0.7.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail:/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip:/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/libsail-c++.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so"
         OLD_RPATH "/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail:/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip:/home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-common:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsail-c++.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/sail/sail-c++" TYPE FILE FILES
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/abstract_io-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/arbitrary_data-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/at_scope_exit-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/codec_info-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/context-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/conversion_options-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/compression_level-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/iccp-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/image-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/image_input-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/image_output-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/io_base-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/io_file-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/io_memory-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/load_features-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/load_options-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/log-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/meta_data-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/ostream-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/palette-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/resolution-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/sail-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/save_features-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/save_options-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/source_image-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/special_properties-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/tuning-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/utils-c++.h"
    "/home/ethan/Repos/VulkanWrapper/sail/src/bindings/c++/variant-c++.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/libsail-c++.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sailc++/SailC++Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sailc++/SailC++Targets.cmake"
         "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/CMakeFiles/Export/7bb2c8fee28830c2967ebf63c0c5e75a/SailC++Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sailc++/SailC++Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/sailc++/SailC++Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sailc++" TYPE FILE FILES "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/CMakeFiles/Export/7bb2c8fee28830c2967ebf63c0c5e75a/SailC++Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sailc++" TYPE FILE FILES "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/CMakeFiles/Export/7bb2c8fee28830c2967ebf63c0c5e75a/SailC++Targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/sailc++" TYPE FILE FILES
    "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/SailC++Config.cmake"
    "/home/ethan/Repos/VulkanWrapper/sail/build/src/bindings/c++/SailC++ConfigVersion.cmake"
    )
endif()

