if(MSVC)
    message(STATUS "MSVC_VERSION: ${MSVC_VERSION}")
    message(STATUS "MSVC_TOOLSET_VERSION: ${MSVC_TOOLSET_VERSION}")
    message(STATUS "CMAKE_VS_PLATFORM_TOOLSET: ${CMAKE_VS_PLATFORM_TOOLSET}")
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler detection and settings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Clang specific settings
elseif(MSVC)
    # MSVC specific setting
endif()

# Global compile definitions
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_CRT_NONSTDC_NO_WARNINGS)
add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)

# Set compile features
set(CMAKE_POSITION_INDEPENDENT_CODE ON)