#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SAIL::sail-common" for configuration "Release"
set_property(TARGET SAIL::sail-common APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SAIL::sail-common PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsail-common.so.0.9.2"
  IMPORTED_SONAME_RELEASE "libsail-common.so.0"
  )

list(APPEND _cmake_import_check_targets SAIL::sail-common )
list(APPEND _cmake_import_check_files_for_SAIL::sail-common "${_IMPORT_PREFIX}/lib/libsail-common.so.0.9.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
