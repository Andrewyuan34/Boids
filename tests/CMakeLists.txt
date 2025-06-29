# Define test name
set(TEST_NAME "Boids_Test")

# Add test executable
add_executable(${TEST_NAME}
    main_test.cpp
    BoidTest.cpp
    BoidManagerTest.cpp
    CameraTest.cpp
    PipelineTest.cpp
)

# Set include directories
target_include_directories(${TEST_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/rendering
    ${CMAKE_SOURCE_DIR}/thirdparty/glm
    ${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/include
    ${CMAKE_SOURCE_DIR}/thirdparty/bgfx.cmake/bgfx/include
    ${CMAKE_SOURCE_DIR}/thirdparty/bgfx.cmake/bx/include
    ${CMAKE_SOURCE_DIR}/thirdparty/bgfx.cmake/bimg/include
)

# Add compile definitions
target_compile_definitions(${TEST_NAME} PRIVATE
    GLM_ENABLE_EXPERIMENTAL
)

# Link necessary libraries
target_link_libraries(${TEST_NAME} PRIVATE
    gtest_main
    gmock
    boids_core
    bgfx
    bx
    bimg
)

# Add test
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME}) 