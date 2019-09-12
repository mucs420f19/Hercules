# CMakeList.txt : CMake project for HerculesProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (HerculesProject "Main.cpp" "UMLObject.h" "UMLObject.cpp")

# TODO: Add tests and install targets if needed.

set(CMAKE_CXX_STANDARD 14)