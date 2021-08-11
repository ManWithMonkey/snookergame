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

bool MovingCircleCollidesWithStaticLine(vec2 p, vec2 dp, float r, vec2 a, vec2 b){
    vec2 p2 = {p.x + dp.x, p.y + dp.y};

    // min distance over movement
    float minDist = LineLineDistance(p, p2, a, b);

    // distance was less than radius at one point -> collided
    if(minDist < r){
        return true;
    }
    else{
        return false;
    }
}

float PointPointDistance(vec2 a, vec2 b){
    return 0.f;
}

float LinePointDistance(vec2 a, vec2 b, vec2 p){
    return 0.f;
}

float LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    return 0.f;
}

vec2 LineCollisionPoint(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    vec2 result = {0.f, 0.f};

    vec2 d1 = {b1.x - a1.x, b1.y - a1.y};
    vec2 d2 = {b2.x - a2.x, b2.y - a2.y};

    // magic here

    return result;
}

vec2 MovingCircleCollisionPointWithLine(vec2 p, vec2 dp, float r, vec2 a, vec2 b){
    
}
