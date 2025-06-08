# Third party library path
set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
set(GLAD_DIR ${THIRDPARTY_DIR}/glad)
set(GTEST_DIR ${THIRDPARTY_DIR}/googletest)
set(IMGUI_DIR ${THIRDPARTY_DIR}/imgui)
set(GLFW_DIR ${THIRDPARTY_DIR}/glfw)
set(SPDLOG_DIR ${THIRDPARTY_DIR}/spdlog)

find_package(OpenGL REQUIRED)

# BGFX configuration
set(BGFX_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/bgfx.cmake)
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "Build bgfx tools." FORCE)
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "Build bgfx examples." FORCE)
set(BX_AMALGAMATED ON CACHE BOOL "Amalgamated bx build for faster compilation" FORCE)
set(BGFX_AMALGAMATED ON CACHE BOOL "Amalgamated bgfx build for faster compilation" FORCE)
set(BGFX_GLOBAL_TARGETS ON CACHE BOOL "Make bgfx targets global" FORCE)
add_subdirectory(${BGFX_CMAKE_DIR})

# Third party library build
add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest)
add_subdirectory(${GLAD_DIR} glad)
add_subdirectory(${GLFW_DIR} ${CMAKE_BINARY_DIR}/glfw)
add_subdirectory(${SPDLOG_DIR} ${CMAKE_BINARY_DIR}/spdlog)

# ImGui build
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