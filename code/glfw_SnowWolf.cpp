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
#include "utils/timer.h"

#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"

#include "graphics/renderer2d.h"
#include "graphics/simple2drenderer.h"
#include "graphics/batchrenderer2d.h"

#include "graphics/staticSprite.h"
#include "graphics/sprite.h"


#include <time.h>

#define BATCH_RENDERER 1

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main(void)
{
    Window window("klek testing", 960, 540);

    // Add a color to the window to check for GL
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    // Debugging
//    std::cout << "We could apparently make a window" << std::endl;
    
    // Read in the shader
    Shader shader("../shaders/basic.vert", "../shaders/basic.frag");
    // Debugging
//    std::cout << "Passed the reading of the shader" << std::endl;
    
    shader.enable();
    shader.setUniformMat4("pr_matrix", ortho);
//    shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

    std::vector<Renderable2D*> sprites;

    srand(time(NULL));
    
    for (float y = 0; y < 9.0f; y += 0.05)
    {
        for (float x = 0; x < 16.0f; x += 0.05)
        {
            sprites.push_back(new
#if BATCH_RENDERER
                              Sprite
#else
                              StaticSprite
#endif
                              (x, y, 0.04f, 0.04f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !BATCH_RENDERER
                               , shader
#endif
                               ));
        }
    }
    
#if BATCH_RENDERER
    Sprite sprite1(5, 5, 4, 4, vec4(1, 0, 1, 1));
    Sprite sprite2(7, 1, 2, 3, vec4(0.2f, 0, 1, 1));
    BatchRenderer2D renderer;
#else
    StaticSprite sprite1(5, 5, 4, 4, vec4(1, 0, 1, 1), shader);
    StaticSprite sprite2(7, 1, 2, 3, vec4(0.2f, 0, 1, 1), shader);
    Simple2DRenderer renderer;
#endif
    shader.setUniform2f("light_pos", vec2(4.5f, 1.5f));
    shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

//    std::cout << sizeof(vec3) << " VS " << sizeof(vec4) << std::endl;

    Timer time;
    float timer = 0;
    unsigned int frames = 0;
    
    // Main loop 
    while ( !window.closed() ) {

        mat4 mat = mat4::translation(vec3(5, 5, 5));
        mat = mat * mat4::rotation(time.elapsed() * 50.0f, vec3(0, 0, 1));
        mat = mat * mat4::translation(vec3(-5, -5, -5));
        shader.setUniformMat4("ml_matrix", mat);
        window.clear();
        double x, y;
        window.getMousePosition(x, y);
        shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
#if BATCH_RENDERER
        renderer.begin();
#endif
        for (int i = 0; i < sprites.size(); i++)
        {
            renderer.submit(sprites[i]);
        }
#if BATCH_RENDERER
        renderer.end();
#endif
        renderer.flush();

        window.update();
//        printf("Sprites: %d\n", sprites.size());
        
        frames++;
        if ( time.elapsed() - timer > 1.0f )
        {
            timer += 1.0f;
            printf("%d fps\n", frames);
            frames = 0;
        }
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
