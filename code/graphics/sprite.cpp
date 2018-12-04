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
    // If there is no texture, set the pointer to null
//    m_Texture = nullptr;
}

Sprite::Sprite(float x, float y, float width, float height, Texture *texture)
        : Renderable2D(vec3(x, y, 0), vec2(width, height), vec4(1, 0, 0, 1))
{
    m_Texture = texture;
}
