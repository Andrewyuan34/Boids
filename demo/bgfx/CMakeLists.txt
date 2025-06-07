cmake_minimum_required(VERSION 3.15)
project(BGFXTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BGFX_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bgfx.cmake)

# Add executable
add_executable(bgfx_test
    bgfx_test.cpp
    bgfx_test.h
)

# Link libraries
target_link_libraries(bgfx_test PRIVATE
    bgfx
    bx
    bimg
    glfw
)

# Add header file paths
target_include_directories(bgfx_test PRIVATE
    ${BGFX_CMAKE_DIR}/bgfx/include
    ${BGFX_CMAKE_DIR}/bx/include
    ${BGFX_CMAKE_DIR}/bimg/include
)

# Set output directory
set_target_properties(bgfx_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)