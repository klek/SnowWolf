/*******************************************************************
   $File:    texture.cpp
   $Date:    Mon, 03 Dec 2018: 16:31
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "texture.h"

Texture::Texture(const std::string& fileName)
        : m_FileName(fileName)
{
    m_TID = load();
}

Texture::~Texture()
{

}

GLuint Texture::load()
{
    BYTE *pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height);

    GLuint result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    // For future
//    delete[] pixels;

    return result;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_TID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
