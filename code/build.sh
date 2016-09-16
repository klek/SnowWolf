#!/bin/bash

SRCDIR="../code"
SRC="$SRCDIR/glfw_SnowWolf.cpp $SRCDIR/window.cpp"
MATHSDIR="../code/maths"
MATHSRC="$MATHSDIR/vec2.cpp $MATHSDIR/vec3.cpp $MATHSDIR/vec4.cpp $MATHSDIR/mat4.cpp $MATHSDIR/maths_func.cpp"
UTILS="../code/utils"
UTILSCR="$UTILS/fileutils.cpp"


mkdir -p ../build
pushd ../build
g++ ../code/sdl_SnowWolf.cpp -o SnowWolf -g `sdl2-config --cflags --libs`
g++ $MATHSRC $UTILSCR $SRC -o SnowWolf_glfw -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -ldl \
-lXinerama -lXcursor -lGLEW
popd
