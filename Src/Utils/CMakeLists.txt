add_library(ScientiaUtils SHARED)

target_sources(ScientiaUtils
    PRIVATE
        Private/Utils.cpp
        Public/Utils.h
)

target_include_directories(ScientiaUtils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
)
