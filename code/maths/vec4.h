/*******************************************************************
   $File:    vec4.h
   $Date:    Mon, 12 Sep 2016: 09:15
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(VEC4_H)
#define VEC4_H

#include <iostream>

struct vec4
{
    float x, y, z, w;

    vec4();
    vec4(const float& x, const float& y, const float& z, const float& w);

    vec4& add(const vec4& other);
    vec4& subtract(const vec4& other);
    vec4& multiply(const vec4& other);
    vec4& divide(const vec4& other);

    // Math operators overloaded
    friend vec4 operator+(vec4 left, const vec4& right);
    friend vec4 operator-(vec4 left, const vec4& right);
    friend vec4 operator*(vec4 left, const vec4& right);
    friend vec4 operator/(vec4 left, const vec4& right);

    vec4& operator+=(const vec4& other);
    vec4& operator-=(const vec4& other);
    vec4& operator*=(const vec4& other);
    vec4& operator/=(const vec4& other);

    bool operator==(const vec4 other) const;
    bool operator!=(const vec4 other) const;

    // Output operators, overloaded
    friend std::ostream& operator<<(std::ostream &stream, const vec4& vector);
};


#endif
