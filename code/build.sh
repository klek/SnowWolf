#!/bin/bash

mkdir -p ../build
pushd ../build
g++ ../code/sdl_SnowWolf.cpp -o SnowWolf -g `sdl2-config --cflags --libs`
g++ ../code/glfw_SnowWolf.cpp -o SnowWolf_glfw -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -ldl \
-lXinerama -lXcursor
popd
