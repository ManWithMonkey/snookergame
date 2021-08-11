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

float DotProduct(vec2 a, vec2 b){
    return a.x * b.x + a.y * b.y;
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
    vec2 p = {0.f, 0.f}; // collision point
    
    // i refuse to google
    vec2 d1 = {b1.x - a1.x, b1.y - a1.y};
    vec2 d2 = {b2.x - a2.x, b2.y - a2.y};

    vec2 u1 = UnitVector(d1);
    vec2 u2 = UnitVector(d2);

    vec2 n1 = Normal(u1);
    vec2 n2 = Normal(u2);

    // p = a1 + t * d1 = a2 + s * d2
    float t = 1.f;
    float s = 1.f;

    float tvalue1 = 100.f;
    float tvalue2 = 100.f;

    vec2 r1 = {a1.x + tvalue1 * d1.x, a1.y + tvalue1 * d1.y};
    vec2 r2 = {a1.x + tvalue2 * d1.x, a2.y + tvalue2 * d1.y};

    // normalize to origin
    r1 = {r1.x - a2.x, r1.y - a2.y};
    r2 = {r2.x - a2.x, r2.y - a2.y};

    // scalar projection
    float v1 = DotProduct(r1, n2);
    float v2 = DotProduct(r2, n2);

    float dt = tvalue2 - tvalue1;
    float dv = v2 - v1;

    // v = kt + b
    float slope = dv / dt;
    // b = v - kt
    float offset = v1 - slope * 0.f;

    // kt + b = v = 0
    // t = -b / k
    float vzero = -offset / slope;

    // (a1 + t * d1 - a2) * n2 = vzero
    // (a1.x + t * d1.x - a2.x) * n2.x + (a1.y + t * d1.y - a2.y) * n2.y = vzero
    // t * d1.x * n2.x + (a1.x - a2.x) * n2.x + t * d1.y * n2.y + (a1.y - a2.y) * n2.y = vzero
    // t * (d1.x * n2.x + d1.y * n2.y) + (a1.x - a2.x) * n2.x + (a1.y - a2.y) * n2.y = vzero
    // t * (d1.x * n2.x + d1.y * n2.y) = vzero - (a1.x - a2.x) * n2.x + (a1.y - a2.y) * n2.y
    // t = (vzero - (a1.x - a2.x) * n2.x + (a1.y - a2.y) * n2.y) / (d1.x * n2.x + d1.y * n2.y)

    float realt = (vzero - (a1.x - a2.x) * n2.x + (a1.y - a2.y) * n2.y) / (d1.x * n2.x + d1.y * n2.y);

    // newton
    // for(int i=0; i<3; i++){
    // }

    p = {a1.x * realt * d1.x, a1.y + realt * d1.y};

    return p;
}

vec2 MovingCircleCollisionPointWithLine(vec2 p, vec2 dp, float r, vec2 a, vec2 b){
    
}
