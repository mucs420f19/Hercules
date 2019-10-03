cmake_minimum_required (VERSION 3.8)
project (Hercules)
set(CMAKE_CXX_STANDARD 17)
MESSAGE( STATUS "PROJECT_NAME: " ${PROJECT_NAME} )

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# Set RPATH
if(WINDOWS)
else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    MESSAGE( STATUS "CMAKE_INSTALL_RPATH: " "${CMAKE_INSTALL_PREFIX}/lib" )
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

enable_testing()

# Add the executable
add_executable (Hercules Main.cpp UMLObject.h UMLObject.cpp SavingLoadingIO.h SavingLoadingIO.cpp UMLObjectsHolder.h UMLObjectsHolder.cpp)
add_executable (HerculesTest UMLObject.h UMLObject.cpp SavingLoadingIO.h SavingLoadingIO.cpp UMLObjectsHolder.h UMLObjectsHolder.cpp Unit-test.cpp Catch2.hpp)
add_test (mytest HerculesTest)