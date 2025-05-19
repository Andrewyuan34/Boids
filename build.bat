@echo off
setlocal

:: Set default values
set BUILD_TYPE=Debug
set RUN_TESTS=OFF
set ENABLE_TIDY=OFF

:: Parse command line arguments
:parse_args
if "%~1"=="" goto :end_parse_args
if /i "%~1"=="--release" set BUILD_TYPE=Release
if /i "%~1"=="--test" set RUN_TESTS=ON
if /i "%~1"=="--tidy" set ENABLE_TIDY=ON
shift
goto :parse_args
:end_parse_args

:: Check if clang is in PATH
where clang >nul 2>nul
if errorlevel 1 (
    echo "clang not found in PATH!"
    exit /b 1
)


:: Create build directory
if not exist build mkdir build
cd build

:: Configure CMake
if "%ENABLE_TIDY%"=="ON" (
    cmake .. -G "Ninja" ^
        -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
        -DCMAKE_C_COMPILER=clang ^
        -DCMAKE_CXX_COMPILER=clang++ ^
        -DCLANG_TIDY_ENABLE=ON
) else (
    cmake .. -G "Ninja" ^
        -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
        -DCMAKE_C_COMPILER=clang ^
        -DCMAKE_CXX_COMPILER=clang++
)

:: Build project
cmake --build .

:: If you need to run tests
if "%RUN_TESTS%"=="ON" (
    ctest --output-on-failure
)

endlocal