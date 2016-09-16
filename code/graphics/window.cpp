/*******************************************************************
   $File:    window.cpp
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

    // Initialize the m_Keys array
    for (int i = 0; i < MAX_KEYS; i++) {
        m_Keys[i] = false;
    }
    // Initialize the m_MouseButtons array
    for (int i = 0; i < MAX_BUTTONS; i++) {
        m_MouseButtons[i] = false;
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

bool Window::isKeyPressed(unsigned int keyCode) const
{
    // TODO(klek): Insert logging here
    if ( keyCode >= MAX_KEYS ) {
        return false;
    }

    return m_Keys[keyCode];
}

bool Window::isMouseButtonPressed(unsigned int mouseButton) const
{
    // TODO(klek): Insert logging here
    if ( mouseButton >= MAX_BUTTONS ) {
        return false;
    }

    return m_MouseButtons[mouseButton];
}

void Window::getMousePosition(double &xpos, double &ypos) const
{
    xpos = m_MouseX;
    ypos = m_MouseY;
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
    glfwSetWindowUserPointer(m_Window, this);

    // Set up callbacks
    glfwSetWindowSizeCallback(m_Window, window_resize);
    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    glfwSetCursorPosCallback(m_Window, cursor_position_callback);

    // Start GLEW
    if ( glewInit() != GLEW_OK )
    {
        // TODO(klek): Insert logger here instead
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    
    // Print out our GL verison
    // TODO(klek): Print it to logger instead.
    std::cout << "OpenGL version "<< glGetString(GL_VERSION) << std::endl;

    // If everything worked so far
    return true;
}

// Callback function for keyboard keys
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Get the pointer to this class
    Window *win = (Window *) glfwGetWindowUserPointer(window);

    // Set the index of our array to true if the key isn't released
    win->m_Keys[key] = (action != GLFW_RELEASE);
}

// Callback function for mouse buttons
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // Get the pointer to this class
    Window *win = (Window *) glfwGetWindowUserPointer(window);

    // Set the index of our array to true if the key isn't released
    win->m_MouseButtons[button] = (action != GLFW_RELEASE);
    
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Get the pointer to this class
    Window *win = (Window *) glfwGetWindowUserPointer(window);

    // Set the positions of the mouse cursor
    win->m_MouseX = xpos;
    win->m_MouseY = ypos;
}


void window_resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
