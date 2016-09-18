/*******************************************************************
   $File:    vertexArray.h
   $Date:    Sun, 18 Sep 2016: 17:01
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(VERTEXARRAY_H)
#define VERTEXARRAY_H

#include <GL/glew.h>
#include <vector>
#include "buffer.h"

class VertexArray
{
// Private members
private:
    GLuint m_ArrayId;
    // Vector array to store each buffer we attach
    // NOTE(klek): This isn't really needed?? Will only use up
    //             extra amount of RAM??
    std::vector<Buffer*> m_Buffers;

// Public methods
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(Buffer* buffer, GLuint index);
    void bind() const;
    void unbind() const;
};

#endif
