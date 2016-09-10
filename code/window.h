/*******************************************************************
   $File:    window.h
   $Date:    Sat, 10 Sep 2016: 16:34
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(WINDOW_H)
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
// Public members

// Private members
private:
    const char *m_Title;
    int m_Width, m_Height;
    GLFWwindow *m_Window;
    bool m_Closed;

// Public methods
public:
    Window(const char *name, int width, int height);
    ~Window();
    bool closed() const;
    void clear() const;
    void update() const;

// Private methods    
private:
    bool init();
    
};

// Callback function to be able to resize the window
void windowResize(GLFWwindow *window, int width, int height);

#endif
