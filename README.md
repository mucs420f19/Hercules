# Hercules

## Description

Team Hercules UML editor written in C++

## Building

  - Clone the repository using your preferred method
  - Navigate into the clone location

### Windows

  - Dependencies: Chocolatey v0.10.15, Cmake v3.8.0, Microsoft Visual Studio 2017
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

  - Dependencies: Python v3.8, Pip v19.3.1, Cmake v 3.8.0
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

  - Dependencies: Python v3.8, Pip v19.3.1, Cmake v 3.8.0
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
## Using The GUI
```
- If you wish to save your file enter the desired name into the text box by the save button 
and click the save button

- If you wish to load a file enter the name into the text box next to the load button 
and then click the load button

- To add a Class enter the desired name into the text box by the Add Class Button 
and click the Add Class button

- To edit a Class enter the name of the class you wish to edit into the text box 
by the Add Class Button then Enter the desired new name into the text box by the 
Edit Class Button then click the edit class button to change the class name.

- To Add a method or Field Hit the Add Method/Field button and type the name of the class in the first box
and click the confirm button then add the method/field name into the next text box and hit the
enter method/field name button

- To Edit a method or Field Hit the Edit Method/Field button and type the name of the class in the first box
and click the confirm button then add the method/field name into the next text box and hit the
enter method/field name button then Enter the new method/field into the third text box and click the button.

- To Delete a method or Field Hit the Delete Method/Field button and type the name of the class in the first box
and click the confirm button then add the method/field name into the next text box and hit the
enter method/field name button

-To List you Classes,Field, and Methods click the List you Classes,Field, and Methods button.
```
## Relationship Types
-When prompted for a relationship type input the number asscoiated with the type you want, types and numbers are listed below.
--RelationshipAbstraction =1

## Tests

The project includes a dedicated unit test executable used to verify functionality

  - Build the project using the instructions above
  - From the build directory, execute:
```
- ctest -C Debug
```
  - Or, run the HerculesTest executable directly
