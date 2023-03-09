#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SAIL::sail-c++" for configuration "Release"
set_property(TARGET SAIL::sail-c++ APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SAIL::sail-c++ PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsail-c++.so.0.7.1"
  IMPORTED_SONAME_RELEASE "libsail-c++.so.0"
  )

list(APPEND _cmake_import_check_targets SAIL::sail-c++ )
list(APPEND _cmake_import_check_files_for_SAIL::sail-c++ "${_IMPORT_PREFIX}/lib/libsail-c++.so.0.7.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
