/*******************************************************************
   $File:    glfw_SnowWolf.h
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

#include "window.h"
#include "maths/math.h"
#include "utils/fileutils.h"
#include <string.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main(void)
{
    Window window("klek testing", 800, 600);

    // Add a color to the window to check for GL
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    std::string file = read_file("../code/glfw_SnowWolf.cpp");

    std::cout << file << std::endl;

    // Main loop 
    while ( !window.closed() ) {
        window.clear();
        
#if 1
        // Draw a rectangle
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
#elif
        glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
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
