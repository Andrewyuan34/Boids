if(NOT DEFINED SHADER_DIR)
    set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif ()

file(GLOB VERTEX_SHADERS "${SHADER_DIR}/vs_*.sc")
file(GLOB FRAGMENT_SHADERS "${SHADER_DIR}/fs_*.sc")
file(GLOB BOIDS_VARYING_DEF_FILE "${SHADER_DIR}/varying.def.sc")

# Debug platform detection
message(STATUS "=== Platform Detection Debug ===")
message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "UNIX: ${UNIX}")
message(STATUS "APPLE: ${APPLE}")
message(STATUS "WIN32: ${WIN32}")
message(STATUS "MINGW: ${MINGW}")
message(STATUS "MSYS: ${MSYS}")
message(STATUS "CYGWIN: ${CYGWIN}")
message(STATUS "ANDROID: ${ANDROID}")
message(STATUS "IOS: ${IOS}")
message(STATUS "EMSCRIPTEN: ${EMSCRIPTEN}")

# Force platform detection for Linux to avoid DirectX compilation
if(UNIX AND NOT APPLE)
    set(CMAKE_SYSTEM_NAME Linux)
    message(STATUS "Forcing CMAKE_SYSTEM_NAME to Linux")
else()
    message(STATUS "Not forcing Linux platform detection")
endif()

message(STATUS "Final CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "=== End Platform Detection Debug ===")

# Debug bgfx_compile_shaders platform detection
message(STATUS "=== bgfx_compile_shaders Platform Detection ===")
if(IOS)
    message(STATUS "bgfx detected: IOS platform")
elseif(ANDROID)
    message(STATUS "bgfx detected: ANDROID platform")
elseif(UNIX AND NOT APPLE)
    message(STATUS "bgfx detected: LINUX platform")
elseif(EMSCRIPTEN)
    message(STATUS "bgfx detected: ASM_JS platform")
elseif(APPLE)
    message(STATUS "bgfx detected: OSX platform")
elseif(WIN32 OR MINGW OR MSYS OR CYGWIN)
    message(STATUS "bgfx detected: WINDOWS platform")
elseif(ORBIS)
    message(STATUS "bgfx detected: ORBIS platform")
else()
    message(STATUS "bgfx detected: UNSUPPORTED platform")
endif()
message(STATUS "=== End bgfx Platform Detection ===")

bgfx_compile_shaders(
        AS_HEADERS
        TYPE VERTEX
        INCLUDE_DIRS ${SHADER_DIR}
        SHADERS ${VERTEX_SHADERS}
        VARYING_DEF ${BOIDS_VARYING_DEF_FILE}
        OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
        OUT_FILES_VAR VERTEX_FILES
)

bgfx_compile_shaders(
        AS_HEADERS
        TYPE FRAGMENT
        INCLUDE_DIRS ${SHADER_DIR}
        SHADERS ${FRAGMENT_SHADERS}
        VARYING_DEF ${SERAPH_VARYING_DEF_FILE}
        OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
        OUT_FILES_VAR FRAGMENT_FILES
)

# Debug platform detection
message(STATUS "=== Platform Detection Debug ===")
message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "UNIX: ${UNIX}")
message(STATUS "APPLE: ${APPLE}")
message(STATUS "WIN32: ${WIN32}")
message(STATUS "MINGW: ${MINGW}")
message(STATUS "MSYS: ${MSYS}")
message(STATUS "CYGWIN: ${CYGWIN}")
message(STATUS "ANDROID: ${ANDROID}")
message(STATUS "IOS: ${IOS}")
message(STATUS "EMSCRIPTEN: ${EMSCRIPTEN}")

# Force platform detection for Linux to avoid DirectX compilation
if(UNIX AND NOT APPLE)
    set(CMAKE_SYSTEM_NAME Linux)
    message(STATUS "Forcing CMAKE_SYSTEM_NAME to Linux")
else()
    message(STATUS "Not forcing Linux platform detection")
endif()

message(STATUS "Final CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "=== End Platform Detection Debug ===")

# Debug bgfx_compile_shaders platform detection
message(STATUS "=== bgfx_compile_shaders Platform Detection ===")
if(IOS)
    message(STATUS "bgfx detected: IOS platform")
elseif(ANDROID)
    message(STATUS "bgfx detected: ANDROID platform")
elseif(UNIX AND NOT APPLE)
    message(STATUS "bgfx detected: LINUX platform")
elseif(EMSCRIPTEN)
    message(STATUS "bgfx detected: ASM_JS platform")
elseif(APPLE)
    message(STATUS "bgfx detected: OSX platform")
elseif(WIN32 OR MINGW OR MSYS OR CYGWIN)
    message(STATUS "bgfx detected: WINDOWS platform")
elseif(ORBIS)
    message(STATUS "bgfx detected: ORBIS platform")
else()
    message(STATUS "bgfx detected: UNSUPPORTED platform")
endif()
message(STATUS "=== End bgfx Platform Detection ===")

add_custom_target(
        Shaders ALL
        DEPENDS ${FRAGMENT_FILES} ${VERTEX_FILES}
        bgfx::shaderc
)
