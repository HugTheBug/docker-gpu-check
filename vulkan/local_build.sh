#! /bin/bash

rm -rf build
mkdir -p build
cd build
cmake -G "Ninja" -D CMAKE_BUILD_TYPE=Debug -Wno-dev -D BUILD_SHARED_LIBS:BOOL=OFF ../source
cmake --build .
