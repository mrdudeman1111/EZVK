#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SAIL::sail" for configuration "Release"
set_property(TARGET SAIL::sail APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SAIL::sail PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsail.so.0.8.0"
  IMPORTED_SONAME_RELEASE "libsail.so.0"
  )

list(APPEND _cmake_import_check_targets SAIL::sail )
list(APPEND _cmake_import_check_files_for_SAIL::sail "${_IMPORT_PREFIX}/lib/libsail.so.0.8.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
