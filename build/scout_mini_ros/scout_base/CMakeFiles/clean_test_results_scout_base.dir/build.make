# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/cmake-3.13.1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake-3.13.1-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/build

# Utility rule file for clean_test_results_scout_base.

# Include the progress variables for this target.
include scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/progress.make

scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base:
	cd /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/build/scout_mini_ros/scout_base && /usr/bin/python2 /opt/ros/melodic/share/catkin/cmake/test/remove_test_results.py /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/build/test_results/scout_base

clean_test_results_scout_base: scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base
clean_test_results_scout_base: scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/build.make

.PHONY : clean_test_results_scout_base

# Rule to build all files generated by this target.
scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/build: clean_test_results_scout_base

.PHONY : scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/build

scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/clean:
	cd /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/build/scout_mini_ros/scout_base && $(CMAKE_COMMAND) -P CMakeFiles/clean_test_results_scout_base.dir/cmake_clean.cmake
.PHONY : scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/clean

scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/depend:
	cd /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/src /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/src/scout_mini_ros/scout_base /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/build /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/build/scout_mini_ros/scout_base /home/jetli/Files/Courses/Mobile_Robots/scout_mini_ws/build/scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : scout_mini_ros/scout_base/CMakeFiles/clean_test_results_scout_base.dir/depend

