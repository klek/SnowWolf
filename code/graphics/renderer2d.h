/*******************************************************************
   $File:    renderer2d.h
   $Date:    Thu, 22 Nov 2018: 23:14
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(RENDERER2D_H)
#define RENDERER2D_H

#include <GL/glew.h>
#include "../maths/math.h"
#include "renderable2d.h"

class Renderer2D
{
public:
    virtual void submit(const Renderable2D *renderable) = 0;
    virtual void flush() = 0;
};

#endif
