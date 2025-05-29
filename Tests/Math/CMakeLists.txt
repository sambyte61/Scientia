add_executable(ScientiaMathTests MatrixTests.cpp)

target_include_directories(ScientiaMathTests PRIVATE
    ${PROJECT_SOURCE_DIR}/Src/Math/Public
)

target_link_libraries(ScientiaMathTests
    PRIVATE
        ScientiaMath
        Catch2::Catch2WithMain
)

# Register with CTest
catch_discover_tests(ScientiaMathTests)
