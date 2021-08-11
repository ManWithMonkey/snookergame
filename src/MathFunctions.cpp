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

vec2 Add(vec2 a, vec2 b){
    return {a.x + b.x, a.y + b.y};
}

vec2 Subtract(vec2 a, vec2 b){
    return {a.x - b.x, a.y - b.y};
}

vec2 Multiply(vec2 a, float s){
    return {a.x * s, a.y * s};
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
    // todo operator overloads 
    vec2 d1 = Subtract(b1, a1);
    vec2 d2 = Subtract(b2, a2);

    vec2 u = UnitVector(d1);
    vec2 n = NormalUnit(d2);

    vec2 v1 = Subtract(a1, a2);
    vec2 v2 = Subtract(Add(a1, u), a2);

    float value1 = DotProduct(n, v1);
    float value2 = DotProduct(n, v2);

    float slope = value2 - value1;

    float t = - value1 / slope;

    vec2 p = Add(a1, Multiply(u1, t));

    return p;
}

vec2 MovingCircleCollisionPointWithLine(vec2 p, vec2 dp, float r, vec2 a, vec2 b){
    return {0.f, 0.f};
}
