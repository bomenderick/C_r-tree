# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/bomen/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.7479.33/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/bomen/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.7479.33/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bomen/CLionProjects/R-Tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bomen/CLionProjects/R-Tree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/R-Tree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/R-Tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/R-Tree.dir/flags.make

CMakeFiles/R-Tree.dir/rtree.cpp.o: CMakeFiles/R-Tree.dir/flags.make
CMakeFiles/R-Tree.dir/rtree.cpp.o: ../rtree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bomen/CLionProjects/R-Tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/R-Tree.dir/rtree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/R-Tree.dir/rtree.cpp.o -c /home/bomen/CLionProjects/R-Tree/rtree.cpp

CMakeFiles/R-Tree.dir/rtree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/R-Tree.dir/rtree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bomen/CLionProjects/R-Tree/rtree.cpp > CMakeFiles/R-Tree.dir/rtree.cpp.i

CMakeFiles/R-Tree.dir/rtree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/R-Tree.dir/rtree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bomen/CLionProjects/R-Tree/rtree.cpp -o CMakeFiles/R-Tree.dir/rtree.cpp.s

CMakeFiles/R-Tree.dir/main.cpp.o: CMakeFiles/R-Tree.dir/flags.make
CMakeFiles/R-Tree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bomen/CLionProjects/R-Tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/R-Tree.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/R-Tree.dir/main.cpp.o -c /home/bomen/CLionProjects/R-Tree/main.cpp

CMakeFiles/R-Tree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/R-Tree.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bomen/CLionProjects/R-Tree/main.cpp > CMakeFiles/R-Tree.dir/main.cpp.i

CMakeFiles/R-Tree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/R-Tree.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bomen/CLionProjects/R-Tree/main.cpp -o CMakeFiles/R-Tree.dir/main.cpp.s

# Object files for target R-Tree
R__Tree_OBJECTS = \
"CMakeFiles/R-Tree.dir/rtree.cpp.o" \
"CMakeFiles/R-Tree.dir/main.cpp.o"

# External object files for target R-Tree
R__Tree_EXTERNAL_OBJECTS =

R-Tree: CMakeFiles/R-Tree.dir/rtree.cpp.o
R-Tree: CMakeFiles/R-Tree.dir/main.cpp.o
R-Tree: CMakeFiles/R-Tree.dir/build.make
R-Tree: CMakeFiles/R-Tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bomen/CLionProjects/R-Tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable R-Tree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/R-Tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/R-Tree.dir/build: R-Tree

.PHONY : CMakeFiles/R-Tree.dir/build

CMakeFiles/R-Tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/R-Tree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/R-Tree.dir/clean

CMakeFiles/R-Tree.dir/depend:
	cd /home/bomen/CLionProjects/R-Tree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bomen/CLionProjects/R-Tree /home/bomen/CLionProjects/R-Tree /home/bomen/CLionProjects/R-Tree/cmake-build-debug /home/bomen/CLionProjects/R-Tree/cmake-build-debug /home/bomen/CLionProjects/R-Tree/cmake-build-debug/CMakeFiles/R-Tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/R-Tree.dir/depend

