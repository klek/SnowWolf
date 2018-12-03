#!/bin/bash

SRCDIR="../code"
SRC="$SRCDIR/glfw_SnowWolf.cpp"
GRAPHDIR="$SRCDIR/graphics"
GRAPHSRC="$GRAPHDIR/window.cpp $GRAPHDIR/shader.cpp $GRAPHDIR/simple2drenderer.cpp $GRAPHDIR/batchrenderer2d.cpp $GRAPHDIR/staticSprite.cpp $GRAPHDIR/sprite.cpp $GRAPHDIR/texture.cpp"
BUFFERSDIR="$GRAPHDIR/buffers"
BUFFERSRC="$BUFFERSDIR/indexBuffer.cpp $BUFFERSDIR/buffer.cpp $BUFFERSDIR/vertexArray.cpp"
LAYERDIR="$GRAPHDIR/layers"
LAYERSRC="$LAYERDIR/layer.cpp $LAYERDIR/tileLayer.cpp $LAYERDIR/group.cpp"
MATHSDIR="$SRCDIR/maths"
MATHSRC="$MATHSDIR/vec2.cpp $MATHSDIR/vec3.cpp $MATHSDIR/vec4.cpp $MATHSDIR/mat4.cpp $MATHSDIR/maths_func.cpp"
UTILS="$SRCDIR/utils"
UTILSCR="$UTILS/fileutils.cpp"

INCSTRING="$MATHSRC $UTILSCR $GRAPHSRC $BUFFERSRC $LAYERSRC $SRC"

mkdir -p ../build
pushd ../build
g++ ../code/sdl_SnowWolf.cpp -o SnowWolf -g `sdl2-config --cflags --libs`
# Building for debug -O0
g++ $INCSTRING -o SnowWolf_glfw -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread \
    -ldl -lXinerama -lXcursor -lGLEW -lfreeimage
# Building for release with -O2
g++ $INCSTRING -o SnowWolf_glfw_release -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread \
    -ldl -lXinerama -lXcursor -lGLEW -lfreeimage -O2
#x86_64-w64-mingw32-g++ $MATHSRC $UTILSCR $GRAPHSRC $BUFFERSRC $SRC -o SnowWolf_glfw.exe -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread \
#    -ldl -lXinerama -lXcursor -lGLEW
popd
