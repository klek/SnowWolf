/*******************************************************************
   $File:    layer.cpp
   $Date:    Sat, 24 Nov 2018: 13:36
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "layer.h"

Layer::Layer(Renderer2D *renderer, Shader *shader, mat4 projectionMatrix)
        : m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
{
    m_Shader->enable();
    m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
    m_Shader->disable();
}

Layer::~Layer()
{
    delete m_Shader;
    delete m_Renderer;

    for ( int i = 0; i < m_Renderables.size(); i++)
    {
        delete m_Renderables[i];
    }
}


void Layer::add(Renderable2D *renderable)
{
    m_Renderables.push_back(renderable);
}

void Layer::render()
{
    m_Shader->enable();
    m_Renderer->begin();

    // Submit each renderable to the renderer
    for ( const Renderable2D *renderable : m_Renderables)
    {
//        m_Renderer->submit(renderable);
        renderable->submit(m_Renderer);
    }

    m_Renderer->end();
    // Flush everything
        
    m_Renderer->flush();
//    m_Shader->disable();
}
