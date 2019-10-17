cmake_minimum_required (VERSION 3.8)
project (Hercules)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Set RPATH
if(CMAKE_HOST_WIN32)
else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    MESSAGE( STATUS "CMAKE_INSTALL_RPATH: " "${CMAKE_INSTALL_PREFIX}/lib" )
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()


# WKK - header files do not belong in source list; source files != header files
add_executable (Hercules Main.cpp UMLObject.cpp SavingLoadingIO.cpp UMLObjectsHolder.cpp)

add_executable (HerculesTest UMLObject.cpp SavingLoadingIO.cpp UMLObjectsHolder.h UMLObjectsHolder.cpp Unit-test.cpp)

enable_testing()

target_include_directories(Hercules PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS})
target_link_libraries(Hercules PUBLIC ${CONAN_LIBS})

add_test (mytest HerculesTest)
