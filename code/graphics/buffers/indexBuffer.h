/*******************************************************************
   $File:    indexBuffer.h
   $Date:    Sun, 18 Sep 2016: 16:47
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(INDEXBUFFER_H)
#define INDEXBUFFER_H

#include <GL/glew.h>

class IndexBuffer
{
// Private members        
private:
    GLuint m_BufferId;

    // The number of elements the buffer has
    GLuint m_Count;

    // Public methods
public:
    IndexBuffer(GLushort *data, GLsizei count);
    IndexBuffer(GLuint *data, GLsizei count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline GLuint getCount() const { return m_Count; }
};

#endif
