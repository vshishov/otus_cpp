# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bob/otus_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bob/otus_cpp/build

# Include any dependencies generated for this target.
include 02_ip_filter/CMakeFiles/ip_filter_cli.dir/depend.make

# Include the progress variables for this target.
include 02_ip_filter/CMakeFiles/ip_filter_cli.dir/progress.make

# Include the compile flags for this target's objects.
include 02_ip_filter/CMakeFiles/ip_filter_cli.dir/flags.make

02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o: 02_ip_filter/CMakeFiles/ip_filter_cli.dir/flags.make
02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o: ../02_ip_filter/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bob/otus_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o"
	cd /home/bob/otus_cpp/build/02_ip_filter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ip_filter_cli.dir/src/main.cpp.o -c /home/bob/otus_cpp/02_ip_filter/src/main.cpp

02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ip_filter_cli.dir/src/main.cpp.i"
	cd /home/bob/otus_cpp/build/02_ip_filter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bob/otus_cpp/02_ip_filter/src/main.cpp > CMakeFiles/ip_filter_cli.dir/src/main.cpp.i

02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ip_filter_cli.dir/src/main.cpp.s"
	cd /home/bob/otus_cpp/build/02_ip_filter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bob/otus_cpp/02_ip_filter/src/main.cpp -o CMakeFiles/ip_filter_cli.dir/src/main.cpp.s

02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o.requires:

.PHONY : 02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o.requires

02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o.provides: 02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o.requires
	$(MAKE) -f 02_ip_filter/CMakeFiles/ip_filter_cli.dir/build.make 02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o.provides.build
.PHONY : 02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o.provides

02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o.provides.build: 02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o


# Object files for target ip_filter_cli
ip_filter_cli_OBJECTS = \
"CMakeFiles/ip_filter_cli.dir/src/main.cpp.o"

# External object files for target ip_filter_cli
ip_filter_cli_EXTERNAL_OBJECTS =

02_ip_filter/ip_filter_cli: 02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o
02_ip_filter/ip_filter_cli: 02_ip_filter/CMakeFiles/ip_filter_cli.dir/build.make
02_ip_filter/ip_filter_cli: 02_ip_filter/CMakeFiles/ip_filter_cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bob/otus_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ip_filter_cli"
	cd /home/bob/otus_cpp/build/02_ip_filter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ip_filter_cli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
02_ip_filter/CMakeFiles/ip_filter_cli.dir/build: 02_ip_filter/ip_filter_cli

.PHONY : 02_ip_filter/CMakeFiles/ip_filter_cli.dir/build

02_ip_filter/CMakeFiles/ip_filter_cli.dir/requires: 02_ip_filter/CMakeFiles/ip_filter_cli.dir/src/main.cpp.o.requires

.PHONY : 02_ip_filter/CMakeFiles/ip_filter_cli.dir/requires

02_ip_filter/CMakeFiles/ip_filter_cli.dir/clean:
	cd /home/bob/otus_cpp/build/02_ip_filter && $(CMAKE_COMMAND) -P CMakeFiles/ip_filter_cli.dir/cmake_clean.cmake
.PHONY : 02_ip_filter/CMakeFiles/ip_filter_cli.dir/clean

02_ip_filter/CMakeFiles/ip_filter_cli.dir/depend:
	cd /home/bob/otus_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bob/otus_cpp /home/bob/otus_cpp/02_ip_filter /home/bob/otus_cpp/build /home/bob/otus_cpp/build/02_ip_filter /home/bob/otus_cpp/build/02_ip_filter/CMakeFiles/ip_filter_cli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 02_ip_filter/CMakeFiles/ip_filter_cli.dir/depend

