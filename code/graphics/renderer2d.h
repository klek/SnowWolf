/*******************************************************************
   $File:    renderer2d.h
   $Date:    Thu, 22 Nov 2018: 23:14
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(RENDERER2D_H)
#define RENDERER2D_H

#include <vector>
#include <GL/glew.h>
#include "../maths/math.h"
//#include "renderable2d.h"

class Renderable2D;

class Renderer2D
{
protected:
//    std::vector<const mat4> m_TransformationStack;
    std::vector<mat4> m_TransformationStack;
    const mat4 *m_TransformationBack;

    Renderer2D()
    {
        m_TransformationStack.push_back(mat4::identity());
        m_TransformationBack = &m_TransformationStack.back();
    }
    
public:
    virtual void begin() {}
    virtual void end() {}
    virtual void submit(const Renderable2D *renderable) = 0;
    virtual void flush() = 0;

    void push(const mat4& matrix, bool override = false)
    {
        if ( override )
        {
            m_TransformationStack.push_back(matrix);
        }
        else
        {
            m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
        }

        m_TransformationBack = &m_TransformationStack.back();
    }

    void pop()
    {
        // TODO: Add to log!
        if ( m_TransformationStack.size() > 1 )
        {
            m_TransformationStack.pop_back();
        }

        m_TransformationBack = &m_TransformationStack.back();
    }
};

#endif
