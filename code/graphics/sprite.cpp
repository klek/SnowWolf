/*******************************************************************
   $File:    sprite.c
   $Date:    Fri, 23 Nov 2018: 21:48
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "sprite.h"

Sprite::Sprite(float x, float y, float width, float height, const vec4& color)
        : Renderable2D(vec3(x, y, 0), vec2(width, height), color)
{
    
}
