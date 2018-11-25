/*******************************************************************
   $File:    group.c
   $Date:    Sun, 25 Nov 2018: 20:34
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "group.h"

Group::Group(const mat4& transform)
        : m_TransformationMatrix(transform)
{
    
}

void Group::add(Renderable2D* renderable)
{
    m_Children.push_back(renderable);
}

void Group::submit(Renderer2D* renderer) const
{
    renderer->push(m_TransformationMatrix);

    for (const Renderable2D* renderable : m_Children )
    {
        renderable->submit(renderer);
    }

    renderer->pop();
}

