# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /snap/cmake/1329/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1329/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Desktop/assignment2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Desktop/assignment2/built

# Include any dependencies generated for this target.
include tests/CMakeFiles/tcp_reciever_checks.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/tcp_reciever_checks.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/tcp_reciever_checks.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/tcp_reciever_checks.dir/flags.make

tests/CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o: tests/CMakeFiles/tcp_reciever_checks.dir/flags.make
tests/CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o: /home/user/Desktop/assignment2/tests/byte_stream_test_harness.cc
tests/CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o: tests/CMakeFiles/tcp_reciever_checks.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/Desktop/assignment2/built/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o"
	cd /home/user/Desktop/assignment2/built/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o -MF CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o.d -o CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o -c /home/user/Desktop/assignment2/tests/byte_stream_test_harness.cc

tests/CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.i"
	cd /home/user/Desktop/assignment2/built/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/assignment2/tests/byte_stream_test_harness.cc > CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.i

tests/CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.s"
	cd /home/user/Desktop/assignment2/built/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/assignment2/tests/byte_stream_test_harness.cc -o CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.s

# Object files for target tcp_reciever_checks
tcp_reciever_checks_OBJECTS = \
"CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o"

# External object files for target tcp_reciever_checks
tcp_reciever_checks_EXTERNAL_OBJECTS =

tests/libtcp_reciever_checks.a: tests/CMakeFiles/tcp_reciever_checks.dir/byte_stream_test_harness.cc.o
tests/libtcp_reciever_checks.a: tests/CMakeFiles/tcp_reciever_checks.dir/build.make
tests/libtcp_reciever_checks.a: tests/CMakeFiles/tcp_reciever_checks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/user/Desktop/assignment2/built/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtcp_reciever_checks.a"
	cd /home/user/Desktop/assignment2/built/tests && $(CMAKE_COMMAND) -P CMakeFiles/tcp_reciever_checks.dir/cmake_clean_target.cmake
	cd /home/user/Desktop/assignment2/built/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_reciever_checks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/tcp_reciever_checks.dir/build: tests/libtcp_reciever_checks.a
.PHONY : tests/CMakeFiles/tcp_reciever_checks.dir/build

tests/CMakeFiles/tcp_reciever_checks.dir/clean:
	cd /home/user/Desktop/assignment2/built/tests && $(CMAKE_COMMAND) -P CMakeFiles/tcp_reciever_checks.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/tcp_reciever_checks.dir/clean

tests/CMakeFiles/tcp_reciever_checks.dir/depend:
	cd /home/user/Desktop/assignment2/built && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Desktop/assignment2 /home/user/Desktop/assignment2/tests /home/user/Desktop/assignment2/built /home/user/Desktop/assignment2/built/tests /home/user/Desktop/assignment2/built/tests/CMakeFiles/tcp_reciever_checks.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/tcp_reciever_checks.dir/depend

