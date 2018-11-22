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

class Renderable2D
{
protected:
    vec3 m_Position;
    vec2 m_Size;
    vec4 m_Color;

    VertexArray *m_VertexArray;
    IndexBuffer *m_IndexBuffer;
    Shader& m_Shader;

public:
    // Constructor
    Renderable2D(vec3 position, vec2 size, vec4 color, Shader& shader)
            : m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
    {
        // Allocate the VertexArray on the heap
        m_VertexArray = new VertexArray();

        // Set up the vertices, clock-wise rotation?
        GLfloat vertices[] =
            {
                0, 0, 0,
                0, size.x, 0,
                size.x, size.y, 0,
                size.x, 0, 0
            };

        // Set up the colors for the vertices
        GLfloat colors[] =
            {
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w
            };

        m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);      
        m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
        
        
        GLushort indices[] = { 0, 1, 2, 2, 3, 0};
        // Allocate the IndexBuffer on the heap
        m_IndexBuffer = new IndexBuffer(indices, 6);
    }

    // Destructor to free all the memory we allocated
    virtual ~Renderable2D()
    {
        delete m_VertexArray;
        delete m_IndexBuffer;
    }

    // Inline functions to get the different members
    inline const VertexArray *getVAO() const { return m_VertexArray; }
    inline const IndexBuffer *getIBO() const { return m_IndexBuffer; }

    inline Shader& getShader() const { return m_Shader; }
    
    inline const vec3& getPosition() const { return m_Position; }
    inline const vec2& getSize() const { return m_Size; }
    inline const vec4& getColor() const { return m_Color; }
};

#endif
