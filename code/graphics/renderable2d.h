/*******************************************************************
   $File:    renderable2d.h
   $Date:    Thu, 22 Nov 2018: 20:14
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(RENDERABLE2D_H)
#define RENDERABLE2D_H

#include "buffers/buffer.h"
#include "buffers/indexBuffer.h"
#include "buffers/vertexArray.h"
#include "shader.h"

#include "../maths/math.h"

struct VertexData
{
    vec3 vertex;
    vec4 color;
};

class Renderable2D
{
protected:
    vec3 m_Position;
    vec2 m_Size;
    vec4 m_Color;

public:
    // Constructor
    Renderable2D(vec3 position, vec2 size, vec4 color)
            : m_Position(position), m_Size(size), m_Color(color)
    {

    }

    // Inline functions to get the different members
    inline const vec3& getPosition() const { return m_Position; }
    inline const vec2& getSize() const { return m_Size; }
    inline const vec4& getColor() const { return m_Color; }
};

#endif
