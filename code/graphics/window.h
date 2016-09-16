/*******************************************************************
   $File:    window.h
   $Date:    Sat, 10 Sep 2016: 16:34
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(WINDOW_H)
#define WINDOW_H

#include <iostream>
#include <GL/glew.h>
//#include <GL/glut.h>
#include <GLFW/glfw3.h>

// Macros
#define MAX_KEYS 1024
#define MAX_BUTTONS 32


class Window
{
// Public members

// Private members
private:
    const char *m_Title;
    int m_Width, m_Height;
    GLFWwindow *m_Window;
    bool m_Closed;

    // Input stuff
    bool m_Keys[MAX_KEYS];
    bool m_MouseButtons[MAX_BUTTONS];
    double m_MouseX, m_MouseY;

// Public methods
public:
    Window(const char *name, int width, int height);
    ~Window();
    bool closed() const;
    void clear() const;
    void update() const;

    bool isKeyPressed(unsigned int keyCode) const;
    bool isMouseButtonPressed(unsigned int mouseButton) const;
    void getMousePosition(double &xpos, double &ypos) const;

// Private methods    
private:
    bool init();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

};

// Callback function to be able to resize the window
void window_resize(GLFWwindow *window, int width, int height);

#endif
