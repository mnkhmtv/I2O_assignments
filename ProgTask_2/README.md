# Interior Point Method Solver

This project implements the Interior Point Method for solving linear programming problems. 

### A vector of decision variables - x by Interior-Point algorithm (when α = 0.5 and α = 0.9) and by Simplex method from programming Task 1

```bash
g++ src/main.cpp src/Matrix.cpp src/InteriorPoint.cpp src/Simplex/Simplex.cpp -o main
./main
```

## Getting Started

### Building the Project

To build the project, use the following commands:

```bash
make build
```

This will generate the necessary build files and compile the project. The compiled binaries will be located in the build directory.

### Running Tests
After building the project, you can run the tests to ensure everything is functioning as expected:
```bash
make test
```
### Memory Check
To check for memory leaks, you can use Valgrind:

```bash
make memory
```

### Formatting Code
To format the code according to the style guidelines, run:

```bash
make format
```

### Linting Code
For linting the C++ code and ensuring it adheres to best practices, use:

```bash
make lint
```

### Cleaning Up
To clean the build directory and remove all generated files, execute:

```bash
make clean
```
## Adding Tests
To add new tests, modify the tests/test_main.cpp file. You can create your test cases using the Google Test framework.

## File Structure
- src/: Contains the source code for the Interior Point Method implementation.
- tests/: Contains the test cases for the project.
- CMakeLists.txt: The CMake configuration file for building the project.
- Makefile: The Makefile to automate the build and test processes.

## Dependencies

This project uses Google Test for unit testing. The Makefile includes a target that automatically downloads and installs Google Test if it is not already present in the project directory.

