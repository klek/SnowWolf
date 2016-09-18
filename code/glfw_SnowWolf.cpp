/*******************************************************************
   $File:    glfw_SnowWolf.cpp
   $Date:    Sat, 10 Sep 2016: 16:32
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include <GL/glew.h>
//#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphics/window.h"
#include "graphics/shader.h"
#include "maths/math.h"
#include "utils/fileutils.h"

#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main(void)
{
    Window window("klek testing", 960, 540);

    // Add a color to the window to check for GL
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

#if 0
    GLfloat vertices[] =
        {
            0, 0, 0,
            8, 0, 0,
            0, 3, 0,
            0, 3, 0,
            8, 3, 0,
            8, 0, 0
        };

    // Create a Vector Buffer Object that will store the vertices on video memory
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Allocate space and upload data from CPU to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    std::cout << "Do I get error here? " << glGetError() << std::endl;
    glEnableVertexAttribArray(0);
    std::cout << glGetError() << std::endl;
#else
    GLfloat vertices[] =
        {
            0, 0, 0,
            0, 3, 0,
            8, 3, 0,
            8, 0, 0
        };

    GLushort indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

    GLfloat colorsA[] =
        {
            1, 0, 1, 1,
            1, 0, 1, 1,
            1, 0, 1, 1,
            1, 0, 1, 1            
        };
    GLfloat colorsB[] =
        {
            0.2f, 0.3f, 0.8f, 1,
            0.2f, 0.3f, 0.8f, 1,
            0.2f, 0.3f, 0.8f, 1,
            0.2f, 0.3f, 0.8f, 1,
        };

    VertexArray sprite1, sprite2;
    IndexBuffer ibo(indices, 6);

    sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
    sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

    sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
    sprite2.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);
#endif


    
    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
    
    // Read in the shader
    Shader shader("../shaders/basic.vert", "../shaders/basic.frag");
    shader.enable();

    shader.setUniformMat4("pr_matrix", ortho);
    shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

    shader.setUniform2f("light_pos", vec2(4.5f, 1.5f));
    shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
    
    // Main loop 
    while ( !window.closed() ) {
        window.clear();
        double x, y;
        window.getMousePosition(x, y);
        shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
#if 0
        glDrawArrays(GL_TRIANGLES, 0, 6);
#else
        sprite1.bind();
        ibo.bind();
        shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
        ibo.unbind();
        sprite1.unbind();

        sprite2.bind();
        ibo.bind();
        shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
        ibo.unbind();
        sprite2.unbind();
#endif
        window.update();
    }

    return 0;


/*  Old Method for triangle
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

*/
}
