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

cmake -S . -B $BUILD_DIR -G "Ninja"

echo ""
echo "Building project..."

cmake --build $BUILD_DIR

echo ""
echo "Running tests..."

$BUILD_DIR/archaeologist_tests

echo ""
echo "Tests passed!"

echo ""
echo "Launching Python UI..."
echo "---------------------------------"

python archaeologist_ui/main.py

echo ""
echo "Done."