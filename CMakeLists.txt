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
#set(CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})
#set(CMAKE_PREFIX_PATH ${CONAN_CMAKE_PREFIX_PATH} ${CMAKE_PREFIX_PATH})

# Add the executable
find_package(OpenGL REQUIRED)
find_package(glew REQUIRED)
find_package(glfw3 REQUIRED)

add_executable (Hercules Main.cpp UMLObject.cpp SavingLoadingIO.cpp UMLObjectsHolder.cpp)
add_executable (HerculesTest UMLObject.cpp SavingLoadingIO.cpp UMLObjectsHolder.cpp Unit-test.cpp)

target_include_directories(Hercules PUBLIC ${OPENGL_INCLUDE_DIRS} ${glew_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS})
target_link_libraries(Hercules PUBLIC ${OPENGL_LIBRARIES} ${glew_LIBRARIES}  ${glfw_LIBRARIES})

add_test (mytest HerculesTest)
