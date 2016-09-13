/*******************************************************************
   $File:    mat4.h
   $Date:    Mon, 12 Sep 2016: 19:35
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(MAT4_H)
#define MAT4_H

#include "math.h"

#define FOUR_BY_FOUR (4 * 4)

struct mat4
{
    float elements[FOUR_BY_FOUR];

    mat4();
    mat4(float diagonal);

    static mat4 identity();

    mat4& multiply(const mat4& other);
    friend mat4 operator*(mat4 left, const mat4& right);
    mat4& operator*=(const mat4& other);

    static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
    static mat4 perspective(float fov, float aspectRatio, float near, float far);

    static mat4 translation(const vec3& translation);
    static mat4 rotation(float angle, const vec3& axis);
    static mat4 scale(const vec3& scale);

};

#endif
