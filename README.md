# Hercules

## Description

Team Hercules UML editor written in C++

## Building

  - Clone the repository using your preferred method
  - Navigate into the clone location

### Windows

  - Dependencies: Chocolatey, Cmake v3.8.0, Microsoft Visual Studio 2017
```
- choco install python
- python -m pip install --upgrade pip
- pip install conan
- conan user
- mkdir build
- cd build
- conan install .. -s arch=x86 -s compiler="Visual Studio" -s compiler.version=15 -s compiler.runtime=MD --build missing
- cd ..
- cd build
- cmake ..
- cmake --build .
```

### Linux

  - Dependencies: Python, Pip, Cmake
```
- pip install --user conan
- conan user
- mkdir build
- cd build
- conan install .. --build missing
- cd ..
- cd build
- cmake ..
- cmake --build .
```

### Mac

  - Dependencies: Python, Pip, Cmake
```
- pip install python
- python -m pip install --upgrade pip
- pip install conan
- conan user
- mkdir build
- cd build
- conan install .. --build missing
- cd ..
- cd build
- cmake ..
- cmake --build .
```

## Running

  - Build the project using the instructions above

  - The executable runs in GUI mode by default
  - To run in console mode, execute:
```
- ./Hercules -console
```

## Tests

The project includes a dedicated unit test executable used to verify functionality

  - Build the project using the instructions above
  - From the build directory, execute:
```
- ctest -C Debug
```
  - Or, run the HerculesTest executable directly
