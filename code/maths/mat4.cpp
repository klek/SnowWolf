/*******************************************************************
   $File:    mat4.h
   $Date:    Tue, 13 Sep 2016: 11:17
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "mat4.h"

mat4::mat4()
{
    for (int i = 0; i < FOUR_BY_FOUR; i++) {
        elements[i] = 0.0f;
    }
}

mat4::mat4(float diagonal)
{
    for (int i = 0; i < FOUR_BY_FOUR; i++) {
        elements[i] = 0.0f;
    }

    elements[4 * 0 + 0] = diagonal;
    elements[4 * 1 + 1] = diagonal;
    elements[4 * 2 + 2] = diagonal;
    elements[4 * 3 + 3] = diagonal;
}

mat4 mat4::identity()
{
    return mat4(1.0f);
}

mat4& mat4::multiply(const mat4& other)
{
    mat4 result;

    // Columnwise
    for (int y = 0; y < 4; y++) {
        // Row wise
        for (int x = 0; x < 4; x++) {
            float sum = 0.0f;
            // Sum up all the elements to this particular element
            // There should be a total of 4 elements summed up??
            for (int e = 0; e < 4; e++) {
                sum += elements[4 * e + x] * other.elements[4 * y + e];
            }
            elements[4 * y + x] = sum;
        }
    }
                                                            
}

mat4 operator*(mat4 left, const mat4& right)
{
    return left.multiply(right)
}


mat4& mat4::operator*=(const mat4& other)
{
    return multiply(other);
}

