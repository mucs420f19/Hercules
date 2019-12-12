cmake_minimum_required (VERSION 3.8)
project (Hercules)
set(CMAKE_CXX_STANDARD 17)
option(COVERALLS "Turn on coveralls support" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)
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


set(HERCULES_MODEL_SRCS Class.cpp Attribute.cpp Model.cpp Relationship.cpp)
set(HERCULES_API_SRCS Command.cpp CommandFactory.cpp SavingLoadingIO.cpp)
set(HERCULES_COVERAGE_SRCS ${HERCULES_MODEL_SRCS} ${HERCULES_API_SRCS})

if (COVERALLS)
   coveralls_setup("${HERCULES_COVERAGE_SRCS}" On)
endif()

add_library (HerculesAPI STATIC ${HERCULES_MODEL_SRCS} ${HERCULES_API_SRCS})

add_executable (Hercules Main.cpp ConsoleView.cpp)

target_include_directories(Hercules PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS})
target_link_libraries(Hercules PUBLIC ${CONAN_LIBS} HerculesAPI)

FILE(GLOB TEST_FILES tests/*.cpp)
add_executable (HerculesTest UnitTest.cpp ${TEST_FILES})
target_link_libraries(HerculesTest PUBLIC HerculesAPI)

enable_testing()
add_test (NAME mytest COMMAND HerculesTest)
