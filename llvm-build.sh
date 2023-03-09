#!/bin/bash

VER="9.0.1"
DOWNLOAD="wget"
BUILD_DIR="llvm-9.0.1-build"
INSTALL_DIR="/usr/bin"

export CC=clang
export CXX=clang++

if [ -d "$BUILD_DIR" ]; then
    echo "Build directory $BUILD_DIR already exists!"
    echo "Exiting..."
    exit 0
fi

echo "Creating llvm build dir"
mkdir "$BUILD_DIR"

pushd "$BUILD_DIR"
echo "Downloading LLVM components"

# $1 = url, $2 = tar_name, $3 = name
function download_extract {
    fn="$1-$VER.src"
    tarn="$fn.tar.xz"
    $DOWNLOAD "https://github.com/llvm/llvm-project/releases/download/llvmorg-$VER/$tarn"
    echo "Untar $tarn"
    tar -xf "$tarn"
    rm "$tarn"
    mv "$fn" "$1"
}

download_extract "llvm"

pushd llvm/tools
download_extract "clang"
popd

pushd llvm/projects


popd

echo "Building LLVM"
mkdir "build"
pushd "build"
cmake  \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_TARGETS_TO_BUILD="MSP430" \
    -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=MSP430 \
    -DLLVM_BUILD_TESTS=OFF \
    -DLLVM_BUILD_DOCS=OFF \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
    ../llvm

make -j8
make install

popd

popd

echo "Done"

