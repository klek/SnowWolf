/*******************************************************************
   $File:    tileLayer.cpp
   $Date:    Sat, 24 Nov 2018: 13:55
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "tileLayer.h"

TileLayer::TileLayer(Shader *shader)
        : Layer(new BatchRenderer2D(), shader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
}

TileLayer::~TileLayer()
{
}
