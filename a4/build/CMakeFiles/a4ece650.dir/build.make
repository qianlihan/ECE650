# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/qianlihan/levn/workspace/ece650/q36han/a4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/qianlihan/levn/workspace/ece650/q36han/a4/build

# Include any dependencies generated for this target.
include CMakeFiles/a4ece650.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a4ece650.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a4ece650.dir/flags.make

CMakeFiles/a4ece650.dir/ece650-a4.cpp.o: CMakeFiles/a4ece650.dir/flags.make
CMakeFiles/a4ece650.dir/ece650-a4.cpp.o: ../ece650-a4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/qianlihan/levn/workspace/ece650/q36han/a4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a4ece650.dir/ece650-a4.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a4ece650.dir/ece650-a4.cpp.o -c /Users/qianlihan/levn/workspace/ece650/q36han/a4/ece650-a4.cpp

CMakeFiles/a4ece650.dir/ece650-a4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a4ece650.dir/ece650-a4.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qianlihan/levn/workspace/ece650/q36han/a4/ece650-a4.cpp > CMakeFiles/a4ece650.dir/ece650-a4.cpp.i

CMakeFiles/a4ece650.dir/ece650-a4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a4ece650.dir/ece650-a4.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qianlihan/levn/workspace/ece650/q36han/a4/ece650-a4.cpp -o CMakeFiles/a4ece650.dir/ece650-a4.cpp.s

# Object files for target a4ece650
a4ece650_OBJECTS = \
"CMakeFiles/a4ece650.dir/ece650-a4.cpp.o"

# External object files for target a4ece650
a4ece650_EXTERNAL_OBJECTS =

a4ece650: CMakeFiles/a4ece650.dir/ece650-a4.cpp.o
a4ece650: CMakeFiles/a4ece650.dir/build.make
a4ece650: minisat/libminisat.a
a4ece650: /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/lib/libz.tbd
a4ece650: CMakeFiles/a4ece650.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/qianlihan/levn/workspace/ece650/q36han/a4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable a4ece650"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a4ece650.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a4ece650.dir/build: a4ece650

.PHONY : CMakeFiles/a4ece650.dir/build

CMakeFiles/a4ece650.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a4ece650.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a4ece650.dir/clean

CMakeFiles/a4ece650.dir/depend:
	cd /Users/qianlihan/levn/workspace/ece650/q36han/a4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/qianlihan/levn/workspace/ece650/q36han/a4 /Users/qianlihan/levn/workspace/ece650/q36han/a4 /Users/qianlihan/levn/workspace/ece650/q36han/a4/build /Users/qianlihan/levn/workspace/ece650/q36han/a4/build /Users/qianlihan/levn/workspace/ece650/q36han/a4/build/CMakeFiles/a4ece650.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a4ece650.dir/depend

