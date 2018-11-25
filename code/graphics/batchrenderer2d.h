/*******************************************************************
   $File:    batchrenderer2d.h
   $Date:    Fri, 23 Nov 2018: 20:35
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(BATCHRENDERER2D_H)
#define BATCHRENDERER2D_H

#include <cstddef>

#include "renderer2d.h"
//#include "renderable2d.h"
#include "buffers/vertexArray.h"
#include "buffers/indexBuffer.h"

#define RENDERER_MAX_SPRITES  60000
#define RENDERER_VERTEX_SIZE  sizeof(VertexData)
#define RENDERER_SPRITE_SIZE  RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE  RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX   0
#define SHADER_COLOR_INDEX    1

class BatchRenderer2D : public Renderer2D
{
private:
//    VertexArray m_VAO;
    GLuint m_VAO;
    GLuint m_VBO;
    IndexBuffer *m_IBO;
    GLsizei m_IndexCount;

    VertexData *m_Buffer;

    void init();
public:
    BatchRenderer2D();
    ~BatchRenderer2D();
    void begin() override;
    void end() override;
    void submit(const Renderable2D *renderable) override;
    void flush() override;

};

#endif
