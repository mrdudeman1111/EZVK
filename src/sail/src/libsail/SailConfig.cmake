include(CMakeFindDependencyMacro)
find_dependency(SailCommon REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR})
# sail depends on sail-codecs if it's enabled

include(${CMAKE_CURRENT_LIST_DIR}/SailTargets.cmake)
