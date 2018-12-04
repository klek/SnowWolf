/*******************************************************************
   $File:    sprite.h
   $Date:    Fri, 23 Nov 2018: 21:48
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(SPRITE_H)
#define SPRITE_H

#include "renderable2d.h"

class Sprite : public Renderable2D
{
private:

public:
    Sprite(float x, float y, float width, float height, const vec4& color);
    Sprite(float x, float y, float width, float height, Texture *texture);
};

#endif
