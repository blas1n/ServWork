#!/bin/sh

set -e

if [ -d build ]; then
	rm -rf build
fi

build = Release
if [ "$1" = "" ]; then
	build = $1
fi

mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=$build .. || goto :error
make
cd ..
