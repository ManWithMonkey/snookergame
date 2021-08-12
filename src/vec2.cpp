#include "vec2.hpp"

vec2 vec2::operator+(const vec2& rhs) const{
    return {x + rhs.x, y + rhs.y};
}

vec2 vec2::operator-(const vec2& rhs) const{
    return {x - rhs.x, y - rhs.y};
}

vec2 vec2::operator*(double s) const{
    return {x * s, y * s};
}
