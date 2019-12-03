cmake_minimum_required (VERSION 3.8)
project (Hercules)
set(CMAKE_CXX_STANDARD 17)
option(COVERALLS "Turn on coveralls support" OFF)



# WKK - header files do not belong in source list; source files != header files
add_executable (Hercules Main.cpp UMLObject.cpp SavingLoadingIO.cpp UMLObjectsHolder.cpp Class.cpp Attribute.cpp Model.cpp Relationship.cpp Command.cpp CommandFactory.cpp ConsoleView.cpp)


add_test (NAME mytest COMMAND HerculesTest)
