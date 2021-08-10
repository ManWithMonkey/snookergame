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

bool AABB(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    float x1 = std::min(a1.x, b1.x);
    float y1 = std::min(a1.y, b1.y);
    float w1 = std::max(a1.x, b1.x) - x1;
    float h1 = std::max(a1.y, b1.y) - y1;

    float x2 = std::min(a2.x, b2.x);
    float y2 = std::min(a2.y, b2.y);
    float w2 = std::max(a2.x, b2.x) - x2;
    float h2 = std::max(a2.y, b2.y) - y2;

    return !(
        x1 + w1 < x2 ||
        y1 + h1 < y2 ||
        x2 + w2 < x1 ||
        y2 + h2 < y1
    );
}

bool LineLineCollision(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    if(!AABB(a1, b1, a2, b2))
        return false;
    
    // todo

    return true;
}

float PointPointDistance(vec2 a, vec2 b){
    // todo
    return 0.f;
}

float LinePointDistance(vec2 a, vec2 b, vec2 p){
    // todo
    return 0.f;
}

float LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    // todo
    return 0.f;
}
