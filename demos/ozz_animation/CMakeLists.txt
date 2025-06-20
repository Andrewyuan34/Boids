cmake_minimum_required(VERSION 3.15)
project(ozz_animation_demo)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(ozz_demo main.cpp)

# Link against Ozz Animation
target_link_libraries(ozz_demo PRIVATE ozz_animation)

# Include directories
target_include_directories(ozz_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OZZ_DIR}/include
) 