#!/bin/sh

set -e

if [ -d build ]; then
	rm -rf build
fi

BUILD_TYPE=Release
if [ "$1" = "" ]; then
	BUILD_TYPE=$1
fi

mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. || goto :error
make
cd ..
