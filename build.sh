#!/usr/bin/env bash
set -e

# -----------------------------------------------------------------------------
# build.sh - Cross-platform build script for Linux/macOS (Bash)
# -----------------------------------------------------------------------------
# Usage examples:
#   ./build.sh                # Debug build
#   ./build.sh --release      # Release build
#   ./build.sh --test         # Run tests after build
#   ./build.sh --tidy         # Enable clang-tidy static analysis
#   ./build.sh --release --test --tidy
# -----------------------------------------------------------------------------

# Default build options
BUILD_TYPE=Debug
RUN_TESTS=OFF
ENABLE_TIDY=OFF

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --release)
            BUILD_TYPE=Release
            shift
            ;;
        --test)
            RUN_TESTS=ON
            shift
            ;;
        --tidy)
            ENABLE_TIDY=ON
            shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

# Check if clang is available in PATH
if ! command -v clang >/dev/null 2>&1; then
    echo "clang not found in PATH!"
    exit 1
fi

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure CMake with or without clang-tidy
if [ "$ENABLE_TIDY" = "ON" ]; then
    cmake .. -G "Ninja" \
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCLANG_TIDY_ENABLE=ON
else
    cmake .. -G "Ninja" \
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++
fi

# Build the project
cmake --build .

# Run tests if requested
if [ "$RUN_TESTS" = "ON" ]; then
    ctest --output-on-failure
fi
