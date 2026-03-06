#!/usr/bin/env bash

set -e

echo "================================="
echo "The Archaeologist Build Script"
echo "================================="

BUILD_DIR="build"

echo ""
echo "Cleaning previous build..."
rm -rf $BUILD_DIR

echo ""
echo "Configuring project with CMake..."
cmake -S . -B $BUILD_DIR

echo ""
echo "Building project..."
cmake --build $BUILD_DIR

echo ""
echo "Running tests..."

TEST_EXECUTABLES=$(find "$BUILD_DIR" -maxdepth 1 -type f -name "*test*" -o -name "*tests*" -o -name "*_tests*" 2>/dev/null)

for test in $TEST_EXECUTABLES; do
  if [[ -x "$test" ]]; then
    "$test"
  fi
done

echo ""
echo "Tests passed!"

echo ""
echo "Running main application..."
echo "---------------------------------"

./$BUILD_DIR/the_archaeologist .

echo ""
echo "Done."