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

vec2 Normal(vec2 v){
    return {v.y, -v.x};
}

vec2 NormalUnit(vec2 v){
    return Normal(UnitVector(v));
}

double Norm(vec2 v){
    return std::sqrt(v.x * v.x + v.y * v.y);
}

vec2 UnitVector(vec2 v){
    double l = Norm(v);

    if(l == 0.0){
        return {0.0, 0.0};
    }

    return {v.x / l, v.y / l};
}

double DotProduct(vec2 a, vec2 b){
    return a.x * b.x + a.y * b.y;
}

double Angle(vec2 v){
    return std::atan2(v.y, v.x);
}

vec2 MirrorVectorFromNormal(vec2 v, vec2 n){
    // https ://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    return v - n * 2.0 * DotProduct(v, n);
}

vec2 MakeVector(double angle, double length){
    return vec2{std::cos(angle), std::sin(angle)} * length;
}