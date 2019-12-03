cmake_minimum_required (VERSION 3.8)
project (Hercules)
set(CMAKE_CXX_STANDARD 17)
option(COVERALLS "Turn on coveralls support" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

if (COVERALLS)
	include(Coveralls)
	coveralls_turn_on_coverage()
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Set RPATH
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
MESSAGE( STATUS "CMAKE_INSTALL_RPATH: " "${CMAKE_INSTALL_PREFIX}/lib" )
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if (COVERALLS)
    set(COVERAGE_SRCS Unit-test.cpp UMLObject.cpp SavingLoadingIO.cpp UMLObjectsHolder.cpp)
	coveralls_setup(
        "${COVERAGE_SRCS}"
        ON
        )
endif()

# WKK - header files do not belong in source list; source files != header files
add_executable (Hercules Main.cpp UMLObject.cpp SavingLoadingIO.cpp UMLObjectsHolder.cpp Class.cpp Attribute.cpp Model.cpp Relationship.cpp Command.cpp CommandFactory.cpp ConsoleView.cpp)

enable_testing()

target_include_directories(Hercules PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS})
target_link_libraries(Hercules PUBLIC ${CONAN_LIBS})

add_test (NAME mytest COMMAND HerculesTest)
