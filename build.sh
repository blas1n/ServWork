#!/bin/sh

set -e

if [ -d build ]; then
	rm -rf build
fi

set BUILD_TYPE=Release
if [ "$1" = "" ]; then
	set BUILD_TYPE=$1
fi

mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build .
cd ..