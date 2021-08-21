#ifndef __VEC2_H__
#define __VEC2_H__

struct vec2{
    double x, y;

    vec2 operator+(const vec2& rhs) const;
    vec2 operator-(const vec2& rhs) const;
    vec2 operator*(double s) const;
};

struct vec3{
    double x, y, z;
};

#endif // __VEC2_H__