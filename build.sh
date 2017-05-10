#!/usr/bin/env bash

mkdir -p tmp
cd tmp
rm -rf *
cmake ..

make
cp binarization ..

cd ..
rm -rf tmp
