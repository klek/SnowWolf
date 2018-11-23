/*******************************************************************
   $File:    batchrenderer2d.c
   $Date:    Fri, 23 Nov 2018: 20:35
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "batchrenderer2d.h"

BatchRenderer2D::BatchRenderer2D()
{
    init();
}

BatchRenderer2D::~BatchRenderer2D()
{
    delete m_IBO;
    glDeleteBuffers(1, &m_VBO);
}

void BatchRenderer2D::init()
{
    // Generate the buffers
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    // Bind the vertex array buffer for editing
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
    glEnableVertexAttribArray(SHADER_COLOR_INDEX);
    glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
    glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(sizeof(vec3)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Allocate the indices on the heap
    GLuint *indices = new GLuint[RENDERER_INDICES_SIZE];

    /*
     * Setup the indices to correctly map a sprite
     * 0--1 We are drawing clockwise, thus we draw:
     * |\ |   0, 1, 2,
     * | \|   2, 3, 0
     * 3--2
     *
     */
    int offset = 0;
    for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
    {
        indices[  i  ] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4;        
    }

    // Allocate the index buffer
    m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

    // Unbind the array
    glBindVertexArray(0);
}

void BatchRenderer2D::begin()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_Buffer = (VertexData *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BatchRenderer2D::end()
{
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BatchRenderer2D::submit(const Renderable2D *renderable)
{
    const vec3& position = renderable->getPosition();
    const vec2& size = renderable->getSize();
    const vec4& color = renderable->getColor();

    m_Buffer->vertex = position;
    m_Buffer->color = color;
    m_Buffer++;

    m_Buffer->vertex = vec3(position.x, position.y + size.y, position.z);
    m_Buffer->color = color;
    m_Buffer++;

    m_Buffer->vertex = vec3(position.x + size.x, position.y + size.y, position.z);
    m_Buffer->color = color;
    m_Buffer++;

    m_Buffer->vertex = vec3(position.x + size.x, position.y, position.z);
    m_Buffer->color = color;
    m_Buffer++;
    
    m_IndexCount += 6;
}

void BatchRenderer2D::flush()
{
    glBindVertexArray(m_VAO);
    m_IBO->bind();

    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

    m_IBO->unbind();
    glBindVertexArray(0);

    m_IndexCount = 0;
}
