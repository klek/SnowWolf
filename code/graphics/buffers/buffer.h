/*******************************************************************
   $File:    buffer.h
   $Date:    Sun, 18 Sep 2016: 16:37
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(BUFFER_H)
#define BUFFER_H

#include <GL/glew.h>

class Buffer
{
// Private members        
private:
    GLuint m_BufferId;

    // The number of components each element in the buffer has
    GLuint m_ComponentCount;

    // Public methods
public:
    Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

    void bind() const;
    void unbind() const;

    inline GLuint getComponentCount() const { return m_ComponentCount; }
};

#endif
