/*******************************************************************
   $File:    simple2drenderer.c
   $Date:    Thu, 22 Nov 2018: 23:22
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "simple2drenderer.h"

// Function to simply push new items into the queue
void Simple2DRenderer::submit(const Renderable2D *renderable)
{
    // Push new items in from the back
    m_RenderQueue.push_back(renderable);
}

// Function to flush the queue, item by item
void Simple2DRenderer::flush()
{
    // While the queue is not empty, grab the next front
    while ( !m_RenderQueue.empty() )
    {
        // Grab the front of the queue
        const Renderable2D *renderable = m_RenderQueue.front();

        renderable->getVAO()->bind();
        renderable->getIBO()->bind();

        renderable->getShader().setUniformMat4("ml_matrix", mat4::translation(renderable->getPosition()));
        glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

        renderable->getIBO()->unbind();
        renderable->getVAO()->unbind();

        m_RenderQueue.pop_front();
    }
}
