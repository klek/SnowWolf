/*******************************************************************
   $File:    layer.h
   $Date:    Sat, 24 Nov 2018: 13:36
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(LAYER_H)
#define LAYER_H

#include "../renderer2d.h"
#include "../renderable2d.h"

class Layer
{
protected:
    // The renderer should be located on the heap
    Renderer2D *m_Renderer;
    std::vector<Renderable2D*> m_Renderables;
    Shader *m_Shader;
    mat4 m_ProjectionMatrix;

    // Protected constructor to force a implemention layer?
    Layer(Renderer2D *renderer, Shader *shader, mat4 projectionMatrix);

public:
    //Layer();

    virtual ~Layer();
    virtual void add(Renderable2D *renderable);
    virtual void render();
};

#endif
