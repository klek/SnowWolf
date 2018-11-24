/*******************************************************************
   $File:    timer.h
   $Date:    Fri, 23 Nov 2018: 23:35
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(TIMER_H)
#define TIMER_H

//#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Timer
{
private:
    unsigned long m_Start;
    unsigned long m_PreviousTime;
//    double m_Frequency;

public:

    Timer()
    {
        m_Start = glfwGetTime();
    }

    void reset()
    {
        double reset = 0.0;
        // This really needed?
        glfwSetTime(reset);
        m_Start = reset;
    }

    float elapsed()
    {
        double current = glfwGetTime();
        // Test if error occured
        if ( current == 0 )
        {
            return 0.0f;
        }
        // Return the elapsed time 
        return (float)(current - m_Start);
    }
};

#endif
