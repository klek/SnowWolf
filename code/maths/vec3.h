/*******************************************************************
   $File:    vec3.h
   $Date:    Mon, 12 Sep 2016: 09:13
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(VEC3_H)
#define VEC3_H

#include <iostream>

struct vec3
{
    float x, y, z;

    vec3();
    vec3(const float& x, const float& y, const float& z);

    vec3& add(const vec3& other);
    vec3& subtract(const vec3& other);
    vec3& multiply(const vec3& other);
    vec3& divide(const vec3& other);

    // Math operators overloaded
    friend vec3& operator+(vec3 left, const vec3& right);
    friend vec3& operator-(vec3 left, const vec3& right);
    friend vec3& operator*(vec3 left, const vec3& right);
    friend vec3& operator/(vec3 left, const vec3& right);

    vec3& operator+=(const vec3& other);
    vec3& operator-=(const vec3& other);
    vec3& operator*=(const vec3& other);
    vec3& operator/=(const vec3& other);

    bool operator==(const vec3 other) const;
    bool operator!=(const vec3 other) const;

    // Output operators, overloaded
    friend std::ostream& operator<<(std::ostream &stream, const vec3& vector);
};


#endif
