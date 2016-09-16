/*******************************************************************
   $File:    maths_func.h
   $Date:    Fri, 16 Sep 2016: 13:22
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(MATHS_FUNC_H)
#define MATHS_FUNC_H

#include <math.h>

/*
  Defining sine function and overloads
 */
double maths_sin(double x);

float maths_sin(float x);

long double maths_sin(long double x);

/*
  Defining cosine functions and overloads
 */
double maths_cos(double x);

float maths_cos(float x);

long double maths_cos(long double x);

/*
  Defining cosine functions and overloads
 */
double maths_tan(double x);

float maths_tan(float x);

long double maths_tan(long double x);

/*
  Defining a toRadians function
 */
float toRadians(float degrees);

#endif
