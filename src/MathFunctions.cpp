#include "MathFunctions.hpp"

vec2 Normal(vec2 v){
    return {v.y, -v.x};
}

vec2 NormalUnit(vec2 v){
    return Normal(UnitVector(v));
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
    return Norm(b - a);
}

float LinePointDistance(vec2 a, vec2 b, vec2 p){
    vec2 u1 = UnitVector(b - a);
    vec2 u2 = UnitVector(a - b);

    float v1 = DotProduct(u1, p - a);
    float v2 = DotProduct(u2, p - b);

    if(v1 == v2){
        vec2 n = Normal(u1);
        float v = DotProduct(n, p - a);
        return v;
    }
    else{
        return std::min(
            Norm(p - a),
            Norm(p - b)
        );
    }
}

float LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    return 0.f;
}

vec2 LineCollisionPoint(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    vec2 d1 = b1 - a1;
    vec2 d2 = b2 - a2;

    vec2 u = UnitVector(d1);
    vec2 n = NormalUnit(d2);

    vec2 v1 = (a1 - a2);
    vec2 v2 = (a1 - a2) + u;

    float scalar1 = DotProduct(n, v1);
    float scalar2 = DotProduct(n, v2);

    float slope = scalar2 - scalar1;

    float t = - scalar1 / slope;

    vec2 p = a1 + u * t;

    return p;
}

vec2 MovingCircleCollisionPointWithLine(vec2 p, vec2 dp, float r, vec2 a, vec2 b){
    return {0.f, 0.f};
}
