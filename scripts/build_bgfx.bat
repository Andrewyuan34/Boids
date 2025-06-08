@echo off
setlocal enabledelayedexpansion

:: Get USE_MSVC from parent script
set USE_MSVC=%1

echo Building bgfx.cmake...

:: Check if the repository has been cloned
if not exist "thirdparty\bgfx.cmake" (
    echo Cloning bgfx.cmake repository...
    git clone https://github.com/bkaradzic/bgfx.cmake.git thirdparty\bgfx.cmake
    if errorlevel 1 (
        echo Failed to clone bgfx.cmake repository
        exit /b 1
    )

    :: Enter the bgfx.cmake directory
    cd thirdparty\bgfx.cmake
    
    :: Initialize submodules
    echo Initializing submodules...
    git submodule init
    if errorlevel 1 (
        echo Failed to initialize submodules
        exit /b 1
    )
    
    :: Update submodules
    echo Updating submodules...
    git submodule update
    if errorlevel 1 (
        echo Failed to update submodules
        exit /b 1
    )
    
    :: Create build directory and run CMake
    echo Configuring with CMake...
    
    :: Configure based on compiler choice
    if "%USE_MSVC%"=="ON" (
        cmake -S. -Bcmake-build
    ) else (
        cmake -S. -Bcmake-build -G "Ninja" ^
            -DCMAKE_C_COMPILER=clang ^
            -DCMAKE_CXX_COMPILER=clang++
    )

    if errorlevel 1 (
        echo Failed to configure with CMake
        exit /b 1
    )
)

:: Build project
cd thirdparty\bgfx.cmake
echo Building project...
cmake --build cmake-build
if errorlevel 1 (
    echo Failed to build project
    exit /b 1
)

:: Return to the original directory
cd ..\..

echo bgfx.cmake build completed successfully!
exit /b 0 