# Scientia

Science! I made this repo as I was relearning calculus and linear algebra to help practice and reinforce math and physics with computer science. My main programming language is c++, so this project is meant to serve as a library/ libraries for these concepts in c++.

## Requirements

I am using Linux to develop, build, run this project. I have not tested this on Windows or plan to.

- CMake ≥ 3.14
- C++20-compatible compiler (e.g., GCC ≥ 10, Clang ≥ 11, MSVC ≥ 2019)
- Catch2 (for testing)
- Git (for cloning submodules and fetching dependencies)

## Build

1. Clone this repository and enter the project directory

```sh
git clone https://github.com/sambyte61/Scientia.git
cd Scientia
```

2. Configure the project with CMake. This will generate the `./build` dir.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

3. Build the project

```sh
cmake --build build
```

4. (Optional) Build and run tests

From the root dir of the project (`.../Scientia/`)

```sh
cmake --build build --target run_tests
```

## Run

After [building the project with cmake](#build), you can run the project via

```sh
cd build
./Scientia
```

After running the program you should see a cli menu to navigate through the library.

```sh
===== MAIN MENU =====
1. Run examples
0. Exit
Select an option: 
```

The "Run examples" option will take you to the Examples menu, which you can run the available examples.

```sh
===== EXAMPLES MENU =====
1. Matrices
0. Exit
Select an option: 
```

`0` in any menu will take you back a menu or terminate the program from the main menu.
