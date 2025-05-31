@echo off
setlocal

:: Set default values
set BUILD_TYPE=Release
set RUN_TESTS=OFF
set ENABLE_TIDY=OFF
set USE_MSVC=OFF

:: Parse command line arguments
:parse_args
if "%~1"=="" goto :end_parse_args
if /i "%~1"=="--debug" set BUILD_TYPE=Debug
if /i "%~1"=="--test" set RUN_TESTS=ON
if /i "%~1"=="--tidy" set ENABLE_TIDY=ON
if /i "%~1"=="--msvc" set USE_MSVC=ON
shift
goto :parse_args
:end_parse_args

:: If not using MSVC, check if clang is in PATH
if "%USE_MSVC%"=="OFF" (
    where clang >nul 2>nul
    if errorlevel 1 (
        echo "clang not found in PATH!"
        exit /b 1
    )
)

:: Set build directory based on compiler
if "%USE_MSVC%"=="ON" (
    set BUILD_DIR=build-msvc
) else (
    set BUILD_DIR=build-clang
)

if not exist %BUILD_DIR% mkdir %BUILD_DIR%
cd %BUILD_DIR%

:: Configure CMake 
:: Let system decide the generator
if "%USE_MSVC%"=="ON" (
    if "%ENABLE_TIDY%"=="ON" (
        cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DCLANG_TIDY_ENABLE=ON
    ) else (
        cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
    )
) else (
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
)

:: Build project
cmake --build .

:: If you need to run tests
if "%RUN_TESTS%"=="ON" (
    ctest -R Boids_Test --output-on-failure
)

endlocal