/*******************************************************************
   $File:    texture.h
   $Date:    Mon, 03 Dec 2018: 16:25
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <FreeImage.h>
#include <string>
#include <GL/glew.h>
#include "../utils/imageLoad.h"

class Texture
{
private:
    std::string m_FileName;
    GLuint m_TID;
    GLsizei m_Width, m_Height;

    GLuint load();

public:
    Texture(const std::string& fileName);
    ~Texture();

    void bind() const;
    void unbind() const;

    inline const unsigned int getWidth() const { return m_Width; }
    inline const unsigned int getHeight() const { return m_Height; }
    inline const unsigned int getID() const { return m_TID; }
};


#endif
