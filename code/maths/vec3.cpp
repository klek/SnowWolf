/*******************************************************************
   $File:    vec3.h
   $Date:    Mon, 12 Sep 2016: 09:16
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "vec3.h"

vec3::vec3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

vec3::vec3(const float& x, const float& y, const float& z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3& vec3::add(const vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

vec3& vec3::subtract(const vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

vec3& vec3::multiply(const vec3& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

vec3& vec3::divide(const vec3& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;

    return *this;
}

// Maths operator overloading
vec3 operator+(vec3 left, const vec3& right)
{
    return left.add(right);
}

vec3 operator-(vec3 left, const vec3& right)
{
    return left.subtract(right);
}

vec3 operator*(vec3 left, const vec3& right)
{
    return left.multiply(right);
}

vec3 operator/(vec3 left, const vec3& right)
{
    return left.divide(right);
}

vec3& vec3::operator+=(const vec3& other)
{
    return this->add(other);
}

vec3& vec3::operator-=(const vec3& other)
{
    return this->subtract(other);
}

vec3& vec3::operator*=(const vec3& other)
{
    return this->multiply(other);
}

vec3& vec3::operator/=(const vec3& other)
{
    return this->divide(other);
}

bool vec3::operator==(const vec3 other) const
{
    return (x == other.x && y == other.y && z == other.z);
}

bool vec3::operator!=(const vec3 other) const
{
    return !(*this == other);
}


// Output operator overloading
std::ostream& operator<<(std::ostream &stream, const vec3& vector)
{
    stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";

    return stream;
}
