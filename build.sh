#!/bin/bash

mkdir -p build
pushd build
c++ ../code/sdl_handmade.cpp -o SnowWolf
popd
