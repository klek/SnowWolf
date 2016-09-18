/*******************************************************************
   $File:    shader.h
   $Date:    Fri, 16 Sep 2016: 17:13
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(SHADER_H)
#define SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <string>
#include "../utils/fileutils.h"

class Shader
{
// Private members
private:
    GLuint m_Id;
    const char* m_VertPath;
    const char* m_FragPath;

// Public methods
public:
    Shader(const char* vertPath, const char* fragPath);
    ~Shader();

    const GLuint getShaderId() const;
    
    void enable() const;
    void disable() const;
    
// Private methods
private:
    GLuint load();
};

#endif
