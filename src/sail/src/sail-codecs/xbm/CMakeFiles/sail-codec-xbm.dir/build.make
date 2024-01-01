# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ethan/Repos/VulkanWrapper/sail

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ethan/Repos/VulkanWrapper/sail/build

# Include any dependencies generated for this target.
include src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/compiler_depend.make

# Include the progress variables for this target.
include src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/progress.make

# Include the compile flags for this target's objects.
include src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/flags.make

src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/helpers.c.o: src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/flags.make
src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/helpers.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm/helpers.c
src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/helpers.c.o: src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/helpers.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/helpers.c.o -MF CMakeFiles/sail-codec-xbm.dir/helpers.c.o.d -o CMakeFiles/sail-codec-xbm.dir/helpers.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm/helpers.c

src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/helpers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-codec-xbm.dir/helpers.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm/helpers.c > CMakeFiles/sail-codec-xbm.dir/helpers.c.i

src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/helpers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-codec-xbm.dir/helpers.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm/helpers.c -o CMakeFiles/sail-codec-xbm.dir/helpers.c.s

src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/xbm.c.o: src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/flags.make
src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/xbm.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm/xbm.c
src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/xbm.c.o: src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/xbm.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/xbm.c.o -MF CMakeFiles/sail-codec-xbm.dir/xbm.c.o.d -o CMakeFiles/sail-codec-xbm.dir/xbm.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm/xbm.c

src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/xbm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-codec-xbm.dir/xbm.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm/xbm.c > CMakeFiles/sail-codec-xbm.dir/xbm.c.i

src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/xbm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-codec-xbm.dir/xbm.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm/xbm.c -o CMakeFiles/sail-codec-xbm.dir/xbm.c.s

# Object files for target sail-codec-xbm
sail__codec__xbm_OBJECTS = \
"CMakeFiles/sail-codec-xbm.dir/helpers.c.o" \
"CMakeFiles/sail-codec-xbm.dir/xbm.c.o"

# External object files for target sail-codec-xbm
sail__codec__xbm_EXTERNAL_OBJECTS =

src/sail-codecs/xbm/sail-codec-xbm.so: src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/helpers.c.o
src/sail-codecs/xbm/sail-codec-xbm.so: src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/xbm.c.o
src/sail-codecs/xbm/sail-codec-xbm.so: src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/build.make
src/sail-codecs/xbm/sail-codec-xbm.so: src/libsail-common/libsail-common.so.0.9.2
src/sail-codecs/xbm/sail-codec-xbm.so: src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared module sail-codec-xbm.so"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sail-codec-xbm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/build: src/sail-codecs/xbm/sail-codec-xbm.so
.PHONY : src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/build

src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/clean:
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm && $(CMAKE_COMMAND) -P CMakeFiles/sail-codec-xbm.dir/cmake_clean.cmake
.PHONY : src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/clean

src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/depend:
	cd /home/ethan/Repos/VulkanWrapper/sail/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ethan/Repos/VulkanWrapper/sail /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/xbm /home/ethan/Repos/VulkanWrapper/sail/build /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/sail-codecs/xbm/CMakeFiles/sail-codec-xbm.dir/depend

