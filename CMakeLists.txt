# Project basic settings
cmake_minimum_required(VERSION 3.15)
project(Boids VERSION 1.0)

# Add cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include compiler settings
include(compiler)

# Include output settings
include(output)

# Include third party library settings
include(thirdparty)

# Include tools settings
include(tools)

# Core library build
add_library(boids_core STATIC
    src/core/Boid.cpp
    src/core/Boid.h
    src/core/BoidManager.cpp
    src/core/BoidManager.h
    src/core/Simulation.cpp
    src/core/Simulation.h
)

target_include_directories(boids_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm
    ${GLFW_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include
)

target_link_libraries(boids_core PUBLIC
    glfw
    glad
    OpenGL::GL
    spdlog::spdlog
)

# Demo build
add_subdirectory(demo/bgfx)

# Main project build
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/ui/ImGuiLayer.cpp
    src/ui/ImGuiLayer.h
    src/ui/BoidsParams.h
    src/core/Boid.cpp
    src/core/Boid.h
    src/core/BoidManager.cpp
    src/core/BoidManager.h
    src/core/Simulation.cpp
    src/core/Simulation.h
    src/Utils/WindowInfo.cpp
    src/Utils/WindowInfo.h
    src/Utils/Camera.cpp
    src/Utils/Camera.h
    src/Utils/Log.cpp
    src/Utils/Log.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewport
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include
    ${SPDLOG_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    imgui
    glad
    OpenGL::GL
    boids_core
    spdlog::spdlog
)

