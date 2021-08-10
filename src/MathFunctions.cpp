#include "MathFunctions.hpp"

vec2 Normal(vec2 v){
    return {v.y, -v.x};
}

float Norm(vec2 v){
    return std::sqrt(v.x * v.x + v.y * v.y);
}

vec2 UnitVector(vec2 v){
    float l = Norm(v);

    if(l == 0.f){
        return {0.f, 0.f};
    }

    return {v.x / l, v.y / l};
}

bool LineLineCollision(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    return false;
}

float PointPointDistance(vec2 a, vec2 b){
    return 0.f;
}

float LinePointDistance(vec2 a, vec2 b, Vec2 p){
    return 0.f;
}

float LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    return 0.f;
}
