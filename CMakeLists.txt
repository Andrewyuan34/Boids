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

set(GTEST_DIR ${THIRDPARTY_DIR}/googletest)
add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest)

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

# Add GLFW
set(GLFW_DIR ${THIRDPARTY_DIR}/glfw)
add_subdirectory(${GLFW_DIR} ${CMAKE_BINARY_DIR}/glfw)

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
    ${IMGUI_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLFW_DIR}/include

)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
)

# 添加测试可执行文件
add_executable(${PROJECT_NAME}_tests
    tests/main_test.cpp
)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)