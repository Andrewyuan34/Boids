#!/usr/bin/env bash
set -e

echo "Building bgfx.cmake..."

# Check if the repository has been cloned
if [ ! -d "thirdparty/bgfx.cmake" ]; then
    echo "Cloning bgfx.cmake repository..."
    git clone https://github.com/bkaradzic/bgfx.cmake.git thirdparty/bgfx.cmake
    if [ $? -ne 0 ]; then
        echo "Failed to clone bgfx.cmake repository"
        exit 1
    fi
fi

# Enter the bgfx.cmake directory
cd thirdparty/bgfx.cmake

# Initialize submodules
echo "Initializing submodules..."
git submodule init
if [ $? -ne 0 ]; then
    echo "Failed to initialize submodules"
    exit 1
fi

# Update submodules
echo "Updating submodules..."
git submodule update
if [ $? -ne 0 ]; then
    echo "Failed to update submodules"
    exit 1
fi

# Create build directory and run CMake
echo "Configuring with CMake..."

# Check if we need to rebuild
NEED_REBUILD=0

# Check if build directory exists
if [ ! -d "cmake-build" ]; then
    echo "Build directory does not exist, creating..."
    NEED_REBUILD=1
else
    # Check if CMakeCache.txt exists and is newer than CMakeLists.txt
    if [ ! -f "cmake-build/CMakeCache.txt" ] || [ "CMakeLists.txt" -nt "cmake-build/CMakeCache.txt" ]; then
        echo "CMake configuration is out of date, rebuilding..."
        NEED_REBUILD=1
    fi
fi

if [ $NEED_REBUILD -eq 1 ]; then
    # Clean CMake cache if it exists
    if [ -d "cmake-build" ]; then
        echo "Cleaning CMake cache..."
        rm -rf cmake-build
    fi
    mkdir -p cmake-build

    # Configure with CMake
    cmake -S. -Bcmake-build -G "Ninja" \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="-D_CRT_SECURE_NO_WARNINGS"

    if [ $? -ne 0 ]; then
        echo "Failed to configure with CMake"
        exit 1
    fi
else
    echo "Using existing CMake configuration..."
fi

# Build project
echo "Building project..."
cmake --build cmake-build
if [ $? -ne 0 ]; then
    echo "Failed to build project"
    exit 1
fi

# Return to the original directory
cd ../..

echo "bgfx.cmake build completed successfully!"
exit 0 