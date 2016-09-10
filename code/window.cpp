/*******************************************************************
   $File:    window.h
   $Date:    Sat, 10 Sep 2016: 16:34
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "window.h"

// Constructor for the window class
Window::Window(const char *name, int width, int height)
{
    m_Title = name;
    m_Width = width;
    m_Height = height;

    // Check if the init function worked
    if ( !init() ) {
        glfwTerminate();
    }
    
}

// Deconstructor for the window class
Window::~Window()
{
    glfwTerminate();
}

// Closed member function. Should return a bool telling if the window is closed or not
bool Window::closed() const
{
    return glfwWindowShouldClose(m_Window);
}

// Clear the current window
void Window::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Update() will poll events and swap buffers
void Window::update() const
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

bool Window::init()
{
    // Init the glfw
    if ( !glfwInit() )
    {
        // TODO(klek): Insert logger here instead
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

    // Check if window got something
    if ( !m_Window ) {
        glfwTerminate();
        // TODO(klek): Insert logger here instead
        std::cout << "Failed to create a windows" << std::endl;

        return false;
    }
    // Make the our m_Window the current context
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowSizeCallback(m_Window, windowResize);

    // If everything worked so far
    return true;
}

void windowResize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
