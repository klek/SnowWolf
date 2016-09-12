/*******************************************************************
   $File:    vec2.h
   $Date:    Sun, 11 Sep 2016: 17:28
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(VEC2_H)
#define VEC2_H

#include <iostream>

struct vec2
{
    float x, y;

    vec2();
    vec2(const float& x, const float& y);

    vec2& add(const vec2& other);
    vec2& subtract(const vec2& other);
    vec2& multiply(const vec2& other);
    vec2& divide(const vec2& other);

    // Math operators overloaded
    friend vec2 operator+(vec2 left, const vec2& right);
    friend vec2 operator-(vec2 left, const vec2& right);
    friend vec2 operator*(vec2 left, const vec2& right);
    friend vec2 operator/(vec2 left, const vec2& right);

    vec2& operator+=(const vec2& other);
    vec2& operator-=(const vec2& other);
    vec2& operator*=(const vec2& other);
    vec2& operator/=(const vec2& other);

    bool operator==(const vec2 other) const;
    bool operator!=(const vec2 other) const;

    // Output operators, overloaded
    friend std::ostream& operator<<(std::ostream &stream, const vec2& vector);
};


#endif
