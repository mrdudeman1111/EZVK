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
include src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/compiler_depend.make

# Include the progress variables for this target.
include src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/progress.make

# Include the compile flags for this target's objects.
include src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/flags.make

src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/ico.c.o: src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/flags.make
src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/ico.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico/ico.c
src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/ico.c.o: src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/ico.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/ico.c.o -MF CMakeFiles/sail-codec-ico.dir/ico.c.o.d -o CMakeFiles/sail-codec-ico.dir/ico.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico/ico.c

src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/ico.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-codec-ico.dir/ico.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico/ico.c > CMakeFiles/sail-codec-ico.dir/ico.c.i

src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/ico.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-codec-ico.dir/ico.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico/ico.c -o CMakeFiles/sail-codec-ico.dir/ico.c.s

src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/helpers.c.o: src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/flags.make
src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/helpers.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico/helpers.c
src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/helpers.c.o: src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/helpers.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/helpers.c.o -MF CMakeFiles/sail-codec-ico.dir/helpers.c.o.d -o CMakeFiles/sail-codec-ico.dir/helpers.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico/helpers.c

src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/helpers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-codec-ico.dir/helpers.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico/helpers.c > CMakeFiles/sail-codec-ico.dir/helpers.c.i

src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/helpers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-codec-ico.dir/helpers.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico/helpers.c -o CMakeFiles/sail-codec-ico.dir/helpers.c.s

# Object files for target sail-codec-ico
sail__codec__ico_OBJECTS = \
"CMakeFiles/sail-codec-ico.dir/ico.c.o" \
"CMakeFiles/sail-codec-ico.dir/helpers.c.o"

# External object files for target sail-codec-ico
sail__codec__ico_EXTERNAL_OBJECTS = \
"/home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/common/bmp/CMakeFiles/bmp-common.dir/helpers.c.o" \
"/home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/common/bmp/CMakeFiles/bmp-common.dir/bmp.c.o"

src/sail-codecs/ico/sail-codec-ico.so: src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/ico.c.o
src/sail-codecs/ico/sail-codec-ico.so: src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/helpers.c.o
src/sail-codecs/ico/sail-codec-ico.so: src/sail-codecs/common/bmp/CMakeFiles/bmp-common.dir/helpers.c.o
src/sail-codecs/ico/sail-codec-ico.so: src/sail-codecs/common/bmp/CMakeFiles/bmp-common.dir/bmp.c.o
src/sail-codecs/ico/sail-codec-ico.so: src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/build.make
src/sail-codecs/ico/sail-codec-ico.so: src/libsail-common/libsail-common.so.0.9.2
src/sail-codecs/ico/sail-codec-ico.so: src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared module sail-codec-ico.so"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sail-codec-ico.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/build: src/sail-codecs/ico/sail-codec-ico.so
.PHONY : src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/build

src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/clean:
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico && $(CMAKE_COMMAND) -P CMakeFiles/sail-codec-ico.dir/cmake_clean.cmake
.PHONY : src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/clean

src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/depend:
	cd /home/ethan/Repos/VulkanWrapper/sail/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ethan/Repos/VulkanWrapper/sail /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/ico /home/ethan/Repos/VulkanWrapper/sail/build /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/sail-codecs/ico/CMakeFiles/sail-codec-ico.dir/depend

