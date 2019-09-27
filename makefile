CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)

add_executable:
	(HerculesProject "Main.cpp" "HerculesProject\UMLObject.h" "HerculesProject\UMLObject.cpp" "HerculesProject\SavingLoadingIO.h" "HerculesProject\SavingLoadingIO.cpp" "HerculesProject\UMLObjectsHolder.h" "HerculesProject\UMLObjectsHolder.cpp")

set:
	(CMAKE_CXX_STANDARD 14)