# Test and tool configuration
enable_testing()
add_subdirectory(tests)

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