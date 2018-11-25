/*******************************************************************
   $File:    mat4.h
   $Date:    Mon, 12 Sep 2016: 19:35
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(MAT4_H)
#define MAT4_H

#include <cstring>

#include "math.h"
#include "vec4.h"

#define FOUR_BY_FOUR (4 * 4)

struct mat4
{
    union {
        float elements[FOUR_BY_FOUR];
        vec4 columns[FOUR_BY_FOUR/FOUR_BY_FOUR];
        vec4 rows[FOUR_BY_FOUR/FOUR_BY_FOUR];
    };

    mat4();
    mat4(float diagonal);

    vec4 getColumn(int index)
    {
        index *= 4;
        return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
    }
    
    static mat4 identity();

    mat4& multiply(const mat4& other);
    friend mat4 operator*(mat4 left, const mat4& right);
    mat4& operator*=(const mat4& other);

    vec3 multiply(const vec3& other) const;
    friend vec3 operator*(const mat4& left, const vec3& right);

    vec4 multiply(const vec4& other) const;
    friend vec4 operator*(const mat4& left, const vec4& right);
    
    static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
    static mat4 perspective(float fov, float aspectRatio, float near, float far);

    static mat4 translation(const vec3& translation);
    static mat4 rotation(float angle, const vec3& axis);
    static mat4 scale(const vec3& scale);

};

#endif
