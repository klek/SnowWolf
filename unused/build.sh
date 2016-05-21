#!/bin/bash

mkdir -p build
pushd build
c++ ../code/sdl_SnowWolf.cpp -o SnowWolf -g `sdl2-config --cflags --libs`
popd
