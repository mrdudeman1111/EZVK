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
include src/libsail-manip/CMakeFiles/sail-manip.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/libsail-manip/CMakeFiles/sail-manip.dir/compiler_depend.make

# Include the progress variables for this target.
include src/libsail-manip/CMakeFiles/sail-manip.dir/progress.make

# Include the compile flags for this target's objects.
include src/libsail-manip/CMakeFiles/sail-manip.dir/flags.make

src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch: src/libsail-manip/CMakeFiles/sail-manip.dir/flags.make
src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.c
src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h
src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch: src/libsail-manip/CMakeFiles/sail-manip.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -x c-header -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -MD -MT src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch -MF CMakeFiles/sail-manip.dir/cmake_pch.h.gch.d -o CMakeFiles/sail-manip.dir/cmake_pch.h.gch -c /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.c

src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-manip.dir/cmake_pch.h.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -x c-header -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -E /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.c > CMakeFiles/sail-manip.dir/cmake_pch.h.i

src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-manip.dir/cmake_pch.h.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -x c-header -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -S /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.c -o CMakeFiles/sail-manip.dir/cmake_pch.h.s

src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/flags.make
src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/cmyk.c
src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h
src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch
src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -MD -MT src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.o -MF CMakeFiles/sail-manip.dir/cmyk.c.o.d -o CMakeFiles/sail-manip.dir/cmyk.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/cmyk.c

src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-manip.dir/cmyk.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -E /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/cmyk.c > CMakeFiles/sail-manip.dir/cmyk.c.i

src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-manip.dir/cmyk.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -S /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/cmyk.c -o CMakeFiles/sail-manip.dir/cmyk.c.s

src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/flags.make
src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/conversion_options.c
src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h
src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch
src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -MD -MT src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.o -MF CMakeFiles/sail-manip.dir/conversion_options.c.o.d -o CMakeFiles/sail-manip.dir/conversion_options.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/conversion_options.c

src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-manip.dir/conversion_options.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -E /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/conversion_options.c > CMakeFiles/sail-manip.dir/conversion_options.c.i

src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-manip.dir/conversion_options.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -S /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/conversion_options.c -o CMakeFiles/sail-manip.dir/conversion_options.c.s

src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/flags.make
src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/convert.c
src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h
src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch
src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -MD -MT src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.o -MF CMakeFiles/sail-manip.dir/convert.c.o.d -o CMakeFiles/sail-manip.dir/convert.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/convert.c

src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-manip.dir/convert.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -E /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/convert.c > CMakeFiles/sail-manip.dir/convert.c.i

src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-manip.dir/convert.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -S /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/convert.c -o CMakeFiles/sail-manip.dir/convert.c.s

src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/flags.make
src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/manip_utils.c
src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h
src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch
src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -MD -MT src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.o -MF CMakeFiles/sail-manip.dir/manip_utils.c.o.d -o CMakeFiles/sail-manip.dir/manip_utils.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/manip_utils.c

src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-manip.dir/manip_utils.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -E /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/manip_utils.c > CMakeFiles/sail-manip.dir/manip_utils.c.i

src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-manip.dir/manip_utils.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -S /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/manip_utils.c -o CMakeFiles/sail-manip.dir/manip_utils.c.s

src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/flags.make
src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/ycbcr.c
src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h
src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch
src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -MD -MT src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.o -MF CMakeFiles/sail-manip.dir/ycbcr.c.o.d -o CMakeFiles/sail-manip.dir/ycbcr.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/ycbcr.c

src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-manip.dir/ycbcr.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -E /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/ycbcr.c > CMakeFiles/sail-manip.dir/ycbcr.c.i

src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-manip.dir/ycbcr.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -S /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/ycbcr.c -o CMakeFiles/sail-manip.dir/ycbcr.c.s

src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/flags.make
src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.o: /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/ycck.c
src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h
src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch
src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.o: src/libsail-manip/CMakeFiles/sail-manip.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.o"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -MD -MT src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.o -MF CMakeFiles/sail-manip.dir/ycck.c.o.d -o CMakeFiles/sail-manip.dir/ycck.c.o -c /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/ycck.c

src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sail-manip.dir/ycck.c.i"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -E /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/ycck.c > CMakeFiles/sail-manip.dir/ycck.c.i

src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sail-manip.dir/ycck.c.s"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Winvalid-pch -include /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h -S /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip/ycck.c -o CMakeFiles/sail-manip.dir/ycck.c.s

# Object files for target sail-manip
sail__manip_OBJECTS = \
"CMakeFiles/sail-manip.dir/cmyk.c.o" \
"CMakeFiles/sail-manip.dir/conversion_options.c.o" \
"CMakeFiles/sail-manip.dir/convert.c.o" \
"CMakeFiles/sail-manip.dir/manip_utils.c.o" \
"CMakeFiles/sail-manip.dir/ycbcr.c.o" \
"CMakeFiles/sail-manip.dir/ycck.c.o"

# External object files for target sail-manip
sail__manip_EXTERNAL_OBJECTS =

src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/cmake_pch.h.gch
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/cmyk.c.o
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/conversion_options.c.o
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/convert.c.o
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/manip_utils.c.o
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/ycbcr.c.o
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/ycck.c.o
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/build.make
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-common/libsail-common.so.0.9.2
src/libsail-manip/libsail-manip.so.0.3.0: src/libsail-manip/CMakeFiles/sail-manip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ethan/Repos/VulkanWrapper/sail/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C shared library libsail-manip.so"
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sail-manip.dir/link.txt --verbose=$(VERBOSE)
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && $(CMAKE_COMMAND) -E cmake_symlink_library libsail-manip.so.0.3.0 libsail-manip.so.0 libsail-manip.so

src/libsail-manip/libsail-manip.so.0: src/libsail-manip/libsail-manip.so.0.3.0
	@$(CMAKE_COMMAND) -E touch_nocreate src/libsail-manip/libsail-manip.so.0

src/libsail-manip/libsail-manip.so: src/libsail-manip/libsail-manip.so.0.3.0
	@$(CMAKE_COMMAND) -E touch_nocreate src/libsail-manip/libsail-manip.so

# Rule to build all files generated by this target.
src/libsail-manip/CMakeFiles/sail-manip.dir/build: src/libsail-manip/libsail-manip.so
.PHONY : src/libsail-manip/CMakeFiles/sail-manip.dir/build

src/libsail-manip/CMakeFiles/sail-manip.dir/clean:
	cd /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip && $(CMAKE_COMMAND) -P CMakeFiles/sail-manip.dir/cmake_clean.cmake
.PHONY : src/libsail-manip/CMakeFiles/sail-manip.dir/clean

src/libsail-manip/CMakeFiles/sail-manip.dir/depend:
	cd /home/ethan/Repos/VulkanWrapper/sail/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ethan/Repos/VulkanWrapper/sail /home/ethan/Repos/VulkanWrapper/sail/src/libsail-manip /home/ethan/Repos/VulkanWrapper/sail/build /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip /home/ethan/Repos/VulkanWrapper/sail/build/src/libsail-manip/CMakeFiles/sail-manip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/libsail-manip/CMakeFiles/sail-manip.dir/depend

