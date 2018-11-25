/*******************************************************************
   $File:    simple2drenderer.h
   $Date:    Thu, 22 Nov 2018: 23:19
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(SIMPLE2DRENDERER_H)
#define SIMPLE2DRENDERER_H

#include <deque>
//#include "renderer2d.h"
#include "renderable2d.h"
#include "staticSprite.h"

class Simple2DRenderer : public Renderer2D
{
private:
    std::deque<const StaticSprite*> m_RenderQueue;
public:
    void submit(const Renderable2D *renderable) override;
    void flush() override;
};

#endif
