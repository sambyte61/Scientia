add_library(ScientiaMath SHARED)

# Sources
target_sources(ScientiaMath
    PRIVATE
        Private/Math.cpp
        Private/Vector.cpp
        Public/Matrix.h
        Public/Matrix.inl
        Public/Vector.h
        Public/Math.h
)

# Include directories
target_include_directories(ScientiaMath
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

# Definitions for Windows DLL support
target_compile_definitions(ScientiaMath PRIVATE SCIENTIAMATH_EXPORTS)
