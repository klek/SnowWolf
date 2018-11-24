/*******************************************************************
   $File:    mat4.cpp
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

/*
  Matrix multiplikation:
     - Row x column or column x row is the way we multiply matrices
     - Since OpenGL uses column-major as the indexing system of the matrices
       we will aswell.
     - We will adress the elements in the matrix as follows
       4 * column + row

     - Is there a way to do this more efficient than a 3-nested loop?
     
 */
mat4& mat4::multiply(const mat4& other)
{
    float data[16];
    // Row wise
    for (int y = 0; y < 4; y++) {
        // Column wise
        for (int x = 0; x < 4; x++) {
            float sum = 0.0f;
            // Sum up all the elements to this particular element
            // There should be a total of 4 elements summed up??
            for (int e = 0; e < 4; e++) {
                // Multiplying column x row here
                sum += elements[4 * e + x] * other.elements[4 * y + e];
            }
            data[4 * y + x] = sum;
        }
    }
    memcpy(elements, data, 4 * 4 * sizeof(float));

    return *this;
}

mat4 operator*(mat4 left, const mat4& right)
{
    return left.multiply(right);
}


mat4& mat4::operator*=(const mat4& other)
{
    return multiply(other);
}

/*
  The orthographics matrix is used to decide what is actually in our "scope" or what we
  can actually display on the screen. It should "clip" away stuff that is outside of our
  defined planes.
  The matrix looks like:

      2/(R-L)  0     0       -(L+R)/(R-L)
      0     2/(T-B)  0       -(B+T)/(T-B)
      0     0     -2/(F-N)   -(F+N)/(F-N)
      0     0     0          1
 */
mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
    mat4 result(1.0f);

    // Setting diagonal
    result.elements[4 * 0 + 0] = 2.0f / (right - left);
    result.elements[4 * 1 + 1] = 2.0f / (top - bottom);
    result.elements[4 * 2 + 2] = 2.0f / (near - far);

    // Setting last column
    result.elements[4 * 3 + 0] = (left + right) / (left - right);
    result.elements[4 * 3 + 1] = (bottom + top) / (bottom - top);    
    result.elements[4 * 3 + 2] = (far + near) / (near - far);

    return result;
}

/*
  The perspective matrix is used to show stuff in a perspective to were the
  camera is. It should essentially filter out stuff we cannot see, and make
  stuff in the distance smaller etc etc.
  The matrix looks like:

      1/(ar*tan(fov/2)  0    0    0
      0     1/(tan(fov/2)    0    0
      0     0     -(F+N)/(F-N)    -(2*F*N)/(F - N)
      0     0     -1              0

 */
mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
    mat4 result;

    float index5 = 1.0f / maths_tan(toRadians(0.5f *fov));
    float index0 = index5 / aspectRatio;
    float index10 = (near + far) / (near - far);
    float index14 = (2.0f * near * far) / (near - far);

    result.elements[4 * 0 + 0] = index0;
    result.elements[4 * 1 + 1] = index5;
    result.elements[4 * 2 + 2] = index10;
    result.elements[4 * 2 + 3] = -1.0f;
    result.elements[4 * 3 + 2] = index14;

    return result;
}

/*
  The translation matrix is basically an identity matrix
  with the last column containing the translation
 */
mat4 mat4::translation(const vec3& translation)
{
    mat4 result(1.0f);

    // Set the last column
    result.elements[4 * 3 + 0] = translation.x;
    result.elements[4 * 3 + 1] = translation.y;
    result.elements[4 * 3 + 2] = translation.z;

    return result;
}

/*
  The rotation matrix is used to rotate stuff around an axis by the
  specified amount of degrees

 */
mat4 mat4::rotation(float angle, const vec3& axis)
{
    mat4 result(1.0f);

    float rad = toRadians(angle);
    float c = maths_cos(rad);
    float s = maths_sin(rad);
    float omc = 1.0f - c;

    result.elements[4 * 0 + 0] = axis.x * omc + c;
    result.elements[4 * 1 + 0] = axis.y * axis.x * omc + axis.z * s;
    result.elements[4 * 2 + 0] = axis.x * axis.z * omc - axis.y * s;

    result.elements[4 * 0 + 1] = axis.x * axis.y * omc - axis.z * s;
    result.elements[4 * 1 + 1] = axis.y * omc + c;
    result.elements[4 * 2 + 1] = axis.y * axis.z * omc + axis.x * s;

    result.elements[4 * 0 + 2] = axis.x * axis.z * omc + axis.y * s;
    result.elements[4 * 1 + 2] = axis.y * axis.z * omc - axis.x * s;
    result.elements[4 * 2 + 2] = axis.z * omc + c;
    
    return result;
}

/*
  The scale matrix is basically an identity matrix with the
  diagonal set to the scale and finishing of with a 1
 */
mat4 mat4::scale(const vec3& scale)
{
    mat4 result(1.0f);

    // Set the diagonal
    result.elements[4 * 0 + 0] = scale.x;
    result.elements[4 * 3 + 1] = scale.y;
    result.elements[4 * 3 + 2] = scale.z;
    
    return result;
}
