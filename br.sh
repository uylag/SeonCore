#!/usr/bin/bash

set -e

BUILD_DIR="build"
BIN_DIR="bin"

rm -rf "$BUILD_DIR"

mkdir -p "$BUILD_DIR"
mkdir -p "$BIN_DIR"

cmake -S . -B "$BUILD_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD_DIR" --parallel "$(nproc)"

cp "$BUILD_DIR/compile_commands.json" ./compile_commands.json

echo "Running $BUILD_DIR/seoncore..."
./"$BUILD_DIR"/seoncore
