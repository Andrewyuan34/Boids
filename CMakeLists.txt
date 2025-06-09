cmake_minimum_required(VERSION 3.15)

project(Boids VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add third party library path
set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
set(GLAD_DIR ${THIRDPARTY_DIR}/glad)

# Add GLFW first (to be used by both main project and Ozz)
set(GLFW_DIR ${THIRDPARTY_DIR}/glfw)
add_subdirectory(${GLFW_DIR} ${CMAKE_BINARY_DIR}/glfw)

# Add Ozz Animation
set(OZZ_DIR ${THIRDPARTY_DIR}/ozz-animation)

if(WIN32)
    if(MSVC)
        set(ozz_build_msvc_rt_dll ON CACHE BOOL "Use MSVC runtime DLL" FORCE)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # For Clang on Windows
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS -Wno-deprecated-declarations")
    endif()
endif()
set(ozz_build_tools OFF CACHE BOOL "Disable Ozz tools" FORCE)
set(ozz_build_samples OFF CACHE BOOL "Disable Ozz samples" FORCE)
set(ozz_build_howtos OFF CACHE BOOL "Disable Ozz howtos" FORCE)
set(ozz_build_tests OFF CACHE BOOL "Disable Ozz tests" FORCE)
set(ozz_build_fbx OFF CACHE BOOL "Disable FBX support" FORCE)
set(ozz_build_gltf OFF CACHE BOOL "Disable glTF support" FORCE)
add_subdirectory(${OZZ_DIR} ${CMAKE_BINARY_DIR}/ozz-animation)

# Add GoogleTest (only if not already added by Ozz)
if(NOT TARGET gtest)
    set(GTEST_DIR ${THIRDPARTY_DIR}/googletest)
    add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest)
endif()

add_subdirectory(${GLAD_DIR} glad)

# Add ImGui source files
set(IMGUI_DIR ${THIRDPARTY_DIR}/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLFW_DIR}/include
)

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

# Add link libraries for boids_core
target_link_libraries(boids_core PUBLIC
    glfw
    glad
    OpenGL::GL
    spdlog::spdlog
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    imgui
    glad  
    OpenGL::GL
    boids_core
    spdlog::spdlog
)

# Add spdlog
set(SPDLOG_DIR ${THIRDPARTY_DIR}/spdlog)
add_subdirectory(${SPDLOG_DIR} ${CMAKE_BINARY_DIR}/spdlog)

add_subdirectory(tests)

# Add demos
add_subdirectory(demos/ozz_animation)

option(CLANG_TIDY_ENABLE "Enable clang-tidy" OFF)
if(CLANG_TIDY_ENABLE)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    else()
        message(STATUS "clang-tidy not found.")
    endif()
endif()