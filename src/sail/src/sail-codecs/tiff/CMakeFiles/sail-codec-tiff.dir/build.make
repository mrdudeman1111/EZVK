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
include src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/compiler_depend.make

# Include the progress variables for this target.
include src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/progress.make

# Include the compile flags for this target's objects.
include src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/flags.make

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/helpers.c.o: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/flags.make
src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/helpers.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/helpers.c
src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/helpers.c.o: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/helpers.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/helpers.c.o -MF CMakeFiles/sail-codec-tiff.dir/helpers.c.o.d -o CMakeFiles/sail-codec-tiff.dir/helpers.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/helpers.c

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/helpers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-codec-tiff.dir/helpers.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/helpers.c > CMakeFiles/sail-codec-tiff.dir/helpers.c.i

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/helpers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-codec-tiff.dir/helpers.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/helpers.c -o CMakeFiles/sail-codec-tiff.dir/helpers.c.s

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/io.c.o: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/flags.make
src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/io.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/io.c
src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/io.c.o: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/io.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/io.c.o -MF CMakeFiles/sail-codec-tiff.dir/io.c.o.d -o CMakeFiles/sail-codec-tiff.dir/io.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/io.c

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-codec-tiff.dir/io.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/io.c > CMakeFiles/sail-codec-tiff.dir/io.c.i

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-codec-tiff.dir/io.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/io.c -o CMakeFiles/sail-codec-tiff.dir/io.c.s

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/tiff.c.o: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/flags.make
src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/tiff.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/tiff.c
src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/tiff.c.o: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/tiff.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/tiff.c.o -MF CMakeFiles/sail-codec-tiff.dir/tiff.c.o.d -o CMakeFiles/sail-codec-tiff.dir/tiff.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/tiff.c

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/tiff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-codec-tiff.dir/tiff.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/tiff.c > CMakeFiles/sail-codec-tiff.dir/tiff.c.i

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/tiff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-codec-tiff.dir/tiff.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff/tiff.c -o CMakeFiles/sail-codec-tiff.dir/tiff.c.s

# Object files for target sail-codec-tiff
sail__codec__tiff_OBJECTS = \
"CMakeFiles/sail-codec-tiff.dir/helpers.c.o" \
"CMakeFiles/sail-codec-tiff.dir/io.c.o" \
"CMakeFiles/sail-codec-tiff.dir/tiff.c.o"

# External object files for target sail-codec-tiff
sail__codec__tiff_EXTERNAL_OBJECTS =

src/sail-codecs/tiff/sail-codec-tiff.so: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/helpers.c.o
src/sail-codecs/tiff/sail-codec-tiff.so: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/io.c.o
src/sail-codecs/tiff/sail-codec-tiff.so: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/tiff.c.o
src/sail-codecs/tiff/sail-codec-tiff.so: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/build.make
src/sail-codecs/tiff/sail-codec-tiff.so: src/libsail-common/libsail-common.so.0.9.2
src/sail-codecs/tiff/sail-codec-tiff.so: /usr/lib/libtiff.so
src/sail-codecs/tiff/sail-codec-tiff.so: src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C shared module sail-codec-tiff.so"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sail-codec-tiff.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/build: src/sail-codecs/tiff/sail-codec-tiff.so
.PHONY : src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/build

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/clean:
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff && $(CMAKE_COMMAND) -P CMakeFiles/sail-codec-tiff.dir/cmake_clean.cmake
.PHONY : src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/clean

src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/depend:
	cd /home/ethan/Repos/VulkanWrapper/sail/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ethan/Repos/VulkanWrapper/sail /home/ethan/Repos/VulkanWrapper/sail/src/sail-codecs/tiff /home/ethan/Repos/VulkanWrapper/sail/build /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff /home/ethan/Repos/VulkanWrapper/sail/build/src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/sail-codecs/tiff/CMakeFiles/sail-codec-tiff.dir/depend

