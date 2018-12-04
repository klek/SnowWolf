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

// Including library for reading simple image-files
#include <FreeImage.h>

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

#include "graphics/layers/tileLayer.h"
#include "graphics/layers/group.h"

#include "graphics/texture.h"

#include <time.h>

//#define BATCH_RENDERER 1
#define TEST_50K_SPRITES 0
#define TEST_LOW_SPRITES 0

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main(void)
{
    Window window("klek testing", 960, 540);

    // Add a color to the window to check for GL
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    // Read in the shader
    Shader *s = new Shader("../shaders/basic.vert", "../shaders/basic.frag");
    Shader& shader = *s;
    shader.enable();
    shader.setUniform2f("light_pos", vec2(4.5f, 1.5f));

    srand(time(NULL));
    
    TileLayer layer(&shader);

    Texture *textures[] =
        {
            new Texture("../pics/test.png"),
            new Texture("../pics/testBorder.png"),
            new Texture("../pics/test.png")
        };

#if TEST_50K_SPRITES
    for ( float y = -9.0f; y < 9.0f; y+= 0.1f)
    {
        for ( float x = -16.0f; x < 16.0f; x += 0.1f)
        {
            if ( rand() % 4 == 0 )
            {
                layer.add(new Sprite(x, y, 0.09f, 0.09f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
            }
            else
            {
                layer.add(new Sprite(x, y, 0.09f, 0.09f, textures[rand() % 3]));
            }
        }
    }
#elif TEST_LOW_SPRITES

    for ( float y = -9.0f; y < 9.0f; y+=6)
    {
        for ( float x = -16.0f; x < 16.0f; x+=8)
        {
            if ( rand() % 4 == 0 )
            {
                layer.add(new Sprite(x, y, 6.4f, 5.4f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
            }
            else
            {
                layer.add(new Sprite(x, y, 6.4f, 5.4f, textures[rand() % 3]));                
            }
        }
    }

#else

    for ( float y = -9.0f; y < 9.0f; y++)
    {
        for ( float x = -16.0f; x < 16.0f; x++)
        {
            if ( rand() % 4 == 0 )
            {
                layer.add(new Sprite(x, y, 0.9f, 0.9f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
            }
            else
            {
                layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
//                layer.add(new Sprite(x, y, 0.9f, 0.9f, new Texture("../pics/test.png")));                
            }
        }
    }

/*    Group *group = new Group(mat4::translation(vec3(-15.0f, 5.0f, 0.0f)));
    group->add(new Sprite(0, 0, 6, 3, vec4( 1, 1, 1, 1)));
    
    Group *button = new Group(mat4::translation(vec3(0.5f, 0.5f, 0.0f)));
    button->add(new Sprite(0, 0, 5.0f, 2.0f, vec4(1, 0, 1, 1)));
    group->add(button);
    layer.add(group);
    //layer.add(new Sprite(0.5f, 0.5f, 5.0f, 2.0f, vec4(1, 0, 1, 1)));
*/
#endif
    
    GLint texIDs[] =
        {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        };
    
    shader.enable();
    shader.setUniform1iv("textures", texIDs, 10);
    shader.setUniformMat4("pr_matrix", mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
    
    Timer time;
    float timer = 0;
    unsigned int frames = 0;

    // Main loop 
    while ( !window.closed() )
    {
        window.clear();
        double x, y;
        window.getMousePosition(x, y);
        shader.enable();
        
        shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

        layer.render();

        window.update();
        frames++;
        if ( time.elapsed() - timer > 1.0f )
        {
            timer += 1.0f;
            printf("%d fps\n", frames);
            frames = 0;
        }
    }

//    for ( int i = 0; i < 3; i++ )
//    {
//        delete textures[i];
//    }
    return 0;
}
