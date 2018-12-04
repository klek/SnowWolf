/*******************************************************************
   $File:    shader.cpp
   $Date:    Fri, 16 Sep 2016: 17:25
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "shader.h"


Shader::Shader(const char* vertPath, const char* fragPath)
        :m_VertPath(vertPath), m_FragPath(fragPath)
{
    m_Id = load();
}

Shader::~Shader()
{
    glDeleteProgram(m_Id);
}

const GLuint Shader::getShaderId() const
{
    return m_Id;
}

void Shader::enable() const
{
    glUseProgram(m_Id);
}

void Shader::disable() const
{
    glUseProgram(0);
}

void Shader::setUniform1f(const GLchar* name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1fv(const GLchar* name, float *value, int count)
{
    glUniform1fv(getUniformLocation(name), count, value);
}

void Shader::setUniform1i(const GLchar* name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1iv(const GLchar* name, int *value, int count)
{
    glUniform1iv(getUniformLocation(name), count, value);
}

void Shader::setUniform2f(const GLchar* name, const vec2& vector)
{
    glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void Shader::setUniform3f(const GLchar* name, const vec3& vector)
{
    glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(const GLchar* name, const vec4& vector)
{
    glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformMat4(const GLchar* name, const mat4& matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
}

/*
  Private methods
 */
GLuint Shader::load()
{
    // Create the program container for the shaders
    GLuint program = glCreateProgram();

    // Create shaders. One vertex shader and one fragment shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // Debugging
    std::cout << "glCreateProgram worked including glCreateShader" << std::endl;

    // Read the shaders
    std::string vertSource = read_file(m_VertPath);
    std::string fragSource = read_file(m_FragPath);

    // Debugging
    std::cout << "Loaded the files" << std::endl;
    
    // Grab
    const char* vertSourceString = vertSource.c_str();
    const char* fragSourceString = fragSource.c_str();

    // 
    glShaderSource(vertex, 1, &vertSourceString, NULL);
    glCompileShader(vertex);

    GLint result;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
    
    // Check for errors
    if ( result == GL_FALSE ) {
        GLint length;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
        char error[length];
        glGetShaderInfoLog(vertex, length, &length, &error[0]);
        std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
        glDeleteShader(vertex);
        return 0;
    }

    //
    glShaderSource(fragment, 1, &fragSourceString, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
    
    // Check for errors
    if ( result == GL_FALSE ) {
        GLint length;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
        char error[length];
        glGetShaderInfoLog(fragment, length, &length, &error[0]);
        std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
        glDeleteShader(fragment);
        return 0;
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

GLint Shader::getUniformLocation(const GLchar* name)
{
    return glGetUniformLocation(m_Id, name);
}
