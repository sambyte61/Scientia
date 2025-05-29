cmake_minimum_required(VERSION 3.14)
project(Scientia VERSION 0.1.0 LANGUAGES C CXX)

# C++ settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include CTest and FetchContent early
include(CTest)
include(FetchContent)

# Fetch Catch2 v3
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(Catch2)

# Include Catch2 CMake support (important for catch_discover_tests)
include(${catch2_SOURCE_DIR}/extras/Catch.cmake)

# Add subdirectories
add_subdirectory(Src/Math)
add_subdirectory(Src/Utils)
add_subdirectory(Tests)

# Main executable
add_executable(Scientia main.cpp)
target_link_libraries(Scientia PRIVATE ScientiaMath ScientiaUtils)
target_include_directories(Scientia PRIVATE Examples/Math)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS ScientiaMathTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
