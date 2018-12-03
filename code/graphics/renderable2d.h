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
#include "renderer2d.h"

#include "../maths/math.h"

struct VertexData
{
    vec3 vertex;
//    vec4 color;
    vec2 uv;
    unsigned int color;
};

class Renderable2D
{
protected:
    vec3 m_Position;
    vec2 m_Size;
    vec4 m_Color;
    std::vector<vec2> m_UV;

    Renderable2D() { setUVDefaults(); }

private:
    void setUVDefaults()
    {
        m_UV.push_back(vec2(0, 0));
        m_UV.push_back(vec2(0, 1));
        m_UV.push_back(vec2(1, 1));
        m_UV.push_back(vec2(1, 0));
    }
    

public:
    // Constructor
    Renderable2D(vec3 position, vec2 size, vec4 color)
            : m_Position(position), m_Size(size), m_Color(color)
    {
        setUVDefaults();
    }

    virtual ~Renderable2D() { }

    virtual void submit(Renderer2D *renderer) const
    {
        renderer->submit(this);
    }

    // Inline functions to get the different members
    inline const vec3& getPosition() const { return m_Position; }
    inline const vec2& getSize() const { return m_Size; }
    inline const vec4& getColor() const { return m_Color; }
    inline const std::vector<vec2>& getUV() const { return m_UV; }

};

#endif
