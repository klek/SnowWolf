/*******************************************************************
   $File:    indexBuffer.cpp
   $Date:    Sun, 18 Sep 2016: 16:47
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "indexBuffer.h"

IndexBuffer::IndexBuffer(GLushort *data, GLsizei count)
        : m_Count(count)
{
    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(GLuint *data, GLsizei count)
        : m_Count(count)
{
    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_BufferId);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
