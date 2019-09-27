cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (HerculesProject "Main.cpp" "HerculesProject\UMLObject.h" "HerculesProject\UMLObject.cpp" "HerculesProject\SavingLoadingIO.h" "HerculesProject\SavingLoadingIO.cpp" "HerculesProject\UMLObjectsHolder.h" "HerculesProject\UMLObjectsHolder.cpp")

# TODO: Add tests and install targets if needed.

set(CMAKE_CXX_STANDARD 14)