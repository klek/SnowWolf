/*******************************************************************
   $File:    vertexArray.cpp
   $Date:    Sun, 18 Sep 2016: 17:01
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "vertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ArrayId);
}

VertexArray::~VertexArray()
{
    // This isn't needed unless we use the vector right?
    // Cause if we use the vector, we need to delete the
    // data we have allocated...
    for (int i = 0; i < m_Buffers.size(); i++) {
        delete m_Buffers[i];
    }
}

void VertexArray::addBuffer(Buffer* buffer, GLuint index)
{
    // Bind this vertex array
    bind();
    // Bind the buffer array
    buffer->bind();

    //
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

    // Unbind the buffer
    buffer->unbind();
    // Unbind the vertex array
    unbind();
}

void VertexArray::bind() const
{
    glBindVertexArray(m_ArrayId);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

