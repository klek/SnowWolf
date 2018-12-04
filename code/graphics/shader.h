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
#include "../maths/math.h"

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

    void setUniform1f(const GLchar* name, float value);
    void setUniform1fv(const GLchar* name, float *value, int count);
    void setUniform1i(const GLchar* name, int value);
    void setUniform1iv(const GLchar* name, int *value, int count);
    void setUniform2f(const GLchar* name, const vec2& vector);
    void setUniform3f(const GLchar* name, const vec3& vector);
    void setUniform4f(const GLchar* name, const vec4& vector);
    void setUniformMat4(const GLchar* name, const mat4& matrix);
    
    void enable() const;
    void disable() const;
    
// Private methods
private:
    GLuint load();
    GLint getUniformLocation(const GLchar* name);
};

#endif
