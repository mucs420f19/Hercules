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
CMAKE_SOURCE_DIR = /home/brian/Hercules

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brian/Hercules/build

# Include any dependencies generated for this target.
include CMakeFiles/Hercules.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Hercules.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Hercules.dir/flags.make

CMakeFiles/Hercules.dir/Main.cpp.o: CMakeFiles/Hercules.dir/flags.make
CMakeFiles/Hercules.dir/Main.cpp.o: ../Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/Hercules/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Hercules.dir/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Hercules.dir/Main.cpp.o -c /home/brian/Hercules/Main.cpp

CMakeFiles/Hercules.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hercules.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/Hercules/Main.cpp > CMakeFiles/Hercules.dir/Main.cpp.i

CMakeFiles/Hercules.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hercules.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/Hercules/Main.cpp -o CMakeFiles/Hercules.dir/Main.cpp.s

CMakeFiles/Hercules.dir/Main.cpp.o.requires:

.PHONY : CMakeFiles/Hercules.dir/Main.cpp.o.requires

CMakeFiles/Hercules.dir/Main.cpp.o.provides: CMakeFiles/Hercules.dir/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Hercules.dir/build.make CMakeFiles/Hercules.dir/Main.cpp.o.provides.build
.PHONY : CMakeFiles/Hercules.dir/Main.cpp.o.provides

CMakeFiles/Hercules.dir/Main.cpp.o.provides.build: CMakeFiles/Hercules.dir/Main.cpp.o


CMakeFiles/Hercules.dir/UMLObject.cpp.o: CMakeFiles/Hercules.dir/flags.make
CMakeFiles/Hercules.dir/UMLObject.cpp.o: ../UMLObject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/Hercules/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Hercules.dir/UMLObject.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Hercules.dir/UMLObject.cpp.o -c /home/brian/Hercules/UMLObject.cpp

CMakeFiles/Hercules.dir/UMLObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hercules.dir/UMLObject.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/Hercules/UMLObject.cpp > CMakeFiles/Hercules.dir/UMLObject.cpp.i

CMakeFiles/Hercules.dir/UMLObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hercules.dir/UMLObject.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/Hercules/UMLObject.cpp -o CMakeFiles/Hercules.dir/UMLObject.cpp.s

CMakeFiles/Hercules.dir/UMLObject.cpp.o.requires:

.PHONY : CMakeFiles/Hercules.dir/UMLObject.cpp.o.requires

CMakeFiles/Hercules.dir/UMLObject.cpp.o.provides: CMakeFiles/Hercules.dir/UMLObject.cpp.o.requires
	$(MAKE) -f CMakeFiles/Hercules.dir/build.make CMakeFiles/Hercules.dir/UMLObject.cpp.o.provides.build
.PHONY : CMakeFiles/Hercules.dir/UMLObject.cpp.o.provides

CMakeFiles/Hercules.dir/UMLObject.cpp.o.provides.build: CMakeFiles/Hercules.dir/UMLObject.cpp.o


CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o: CMakeFiles/Hercules.dir/flags.make
CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o: ../SavingLoadingIO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/Hercules/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o -c /home/brian/Hercules/SavingLoadingIO.cpp

CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/Hercules/SavingLoadingIO.cpp > CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.i

CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/Hercules/SavingLoadingIO.cpp -o CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.s

CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o.requires:

.PHONY : CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o.requires

CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o.provides: CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o.requires
	$(MAKE) -f CMakeFiles/Hercules.dir/build.make CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o.provides.build
.PHONY : CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o.provides

CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o.provides.build: CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o


CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o: CMakeFiles/Hercules.dir/flags.make
CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o: ../UMLObjectsHolder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/Hercules/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o -c /home/brian/Hercules/UMLObjectsHolder.cpp

CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/Hercules/UMLObjectsHolder.cpp > CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.i

CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/Hercules/UMLObjectsHolder.cpp -o CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.s

CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o.requires:

.PHONY : CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o.requires

CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o.provides: CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o.requires
	$(MAKE) -f CMakeFiles/Hercules.dir/build.make CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o.provides.build
.PHONY : CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o.provides

CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o.provides.build: CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o


# Object files for target Hercules
Hercules_OBJECTS = \
"CMakeFiles/Hercules.dir/Main.cpp.o" \
"CMakeFiles/Hercules.dir/UMLObject.cpp.o" \
"CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o" \
"CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o"

# External object files for target Hercules
Hercules_EXTERNAL_OBJECTS =

Hercules: CMakeFiles/Hercules.dir/Main.cpp.o
Hercules: CMakeFiles/Hercules.dir/UMLObject.cpp.o
Hercules: CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o
Hercules: CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o
Hercules: CMakeFiles/Hercules.dir/build.make
Hercules: /usr/lib/x86_64-linux-gnu/libGL.so
Hercules: /usr/lib/x86_64-linux-gnu/libGLU.so
Hercules: /usr/lib/x86_64-linux-gnu/libGLEW.so
Hercules: /usr/lib/x86_64-linux-gnu/libglfw.so.3.2
Hercules: CMakeFiles/Hercules.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brian/Hercules/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Hercules"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Hercules.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Hercules.dir/build: Hercules

.PHONY : CMakeFiles/Hercules.dir/build

CMakeFiles/Hercules.dir/requires: CMakeFiles/Hercules.dir/Main.cpp.o.requires
CMakeFiles/Hercules.dir/requires: CMakeFiles/Hercules.dir/UMLObject.cpp.o.requires
CMakeFiles/Hercules.dir/requires: CMakeFiles/Hercules.dir/SavingLoadingIO.cpp.o.requires
CMakeFiles/Hercules.dir/requires: CMakeFiles/Hercules.dir/UMLObjectsHolder.cpp.o.requires

.PHONY : CMakeFiles/Hercules.dir/requires

CMakeFiles/Hercules.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Hercules.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Hercules.dir/clean

CMakeFiles/Hercules.dir/depend:
	cd /home/brian/Hercules/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brian/Hercules /home/brian/Hercules /home/brian/Hercules/build /home/brian/Hercules/build /home/brian/Hercules/build/CMakeFiles/Hercules.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Hercules.dir/depend

