/*******************************************************************
   $File:    vec2.h
   $Date:    Sun, 11 Sep 2016: 17:30
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include "vec2.h"

vec2::vec2()
{
    x = 0.0f;
    y = 0.0f;
}

vec2::vec2(const float& x, const float& y)
{
    this->x = x;
    this->y = y;
}

vec2& vec2::add(const vec2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

vec2& vec2::subtract(const vec2& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

vec2& vec2::multiply(const vec2& other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

vec2& vec2::divide(const vec2& other)
{
    x /= other.x;
    y /= other.y;

    return *this;
}

// Maths operator overloading
vec2& operator+(vec2 left, const vec2& right)
{
    return left.add(right);
}

vec2& operator-(vec2 left, const vec2& right)
{
    return left.subtract(right);
}

vec2& operator*(vec2 left, const vec2& right)
{
    return left.multiply(right);
}

vec2& operator/(vec2 left, const vec2& right)
{
    return left.divide(right);
}

vec2& vec2::operator+=(const vec2& other)
{
    return this->add(other);
}

vec2& vec2::operator-=(const vec2& other)
{
    return this->subtract(other);
}

vec2& vec2::operator*=(const vec2& other)
{
    return this->multiply(other);
}

vec2& vec2::operator/=(const vec2& other)
{
    return this->divide(other);
}

bool vec2::operator==(const vec2 other) const
{
    return (x == other.x && y == other.y);
}

bool vec2::operator!=(const vec2 other) const
{
    return !(*this == other);
}


// Output operator overloading
std::ostream& operator<<(std::ostream &stream, const vec2& vector)
{
    stream << "vec2: (" << vector.x << ", " << vector.y << ")";

    return stream;
}
