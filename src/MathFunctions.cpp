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

float Angle(vec2 v){
    return std::atan2(v.y, v.x);
}

vec2 MirrorVectorFromNormal(vec2 v, vec2 n){
    float l = Norm(v);

    float a1 = Angle(v);
    float a2 = Angle(n);

    float da = std::fmod(a2 - a1 + 2.f * 3.14159f, 3.14159f);

    float a = a1 + da;

    vec2 result = {l * cos(a), l * sin(a)};

    return result;
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
    vec2 n1 = NormalUnit(b1 - a1);
    vec2 n2 = NormalUnit(b2 - a2);

    float v1 = DotProduct(n1, a2 - a1);
    float v2 = DotProduct(n1, b2 - a1);
    float v3 = DotProduct(n2, a1 - a2);
    float v4 = DotProduct(n2, b1 - a2);

    return (v1 * v2 < 0.f) && (v3 * v4 < 0.f);
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

    if(v1 * v2 > 0.f){
        vec2 n = Normal(u1);
        float v = DotProduct(n, p - a);
        return std::abs(v);
    }
    else{
        return std::min(
            Norm(p - a),
            Norm(p - b)
        );
    }
}

float LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    if(LineLineCollision(a1, b1, a2, b2)){
        return 0.f;
    }

    return std::min({
        LinePointDistance(a1, b1, a2),
        LinePointDistance(a1, b1, b2),
        LinePointDistance(a2, b2, a1),
        LinePointDistance(a2, b2, b1)
    });
}

vec2 LineClosestPointFromPoint(vec2 a, vec2 b, vec2 p){
    vec2 u1 = UnitVector(b - a);
    vec2 u2 = UnitVector(a - b);

    float v1 = DotProduct(u1, p - a);
    float v2 = DotProduct(u2, p - b);

    if(v1 * v2 > 0.f){
        vec2 n = Normal(u1);
        float v = DotProduct(n, p - a);

        return p - n * v;
    }
    else{
        float dist1 = Norm(p - a);
        float dist2 = Norm(p - b);

        if(dist1 < dist2){
            return a;
        }
        else{
            return b;
        }
    }
}

vec2 LineCollisionPoint(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    // assumes that it does collide
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
    // assumes that it does collide
    vec2 result = {0, 0};

    vec2 dline = Subtract(b, a);
    vec2 uline = UnitVector(dline);
    vec2 n = Normal(uline);

    vec2 dmotion = dp;
    vec2 umotion = UnitVector(dmotion);
    
    auto CalcVec = [&](float scalar) -> vec2 {
        return p + umotion * scalar;
    };

    auto Calc = [&](float scalar) -> float {
        vec2 cp = CalcVec(scalar);
        return PointPointDistance(LineClosestPointFromPoint(a, b, cp), cp) - r;
    };

    // float l = Norm(dp);
    float t = 0.f;
    float delta = 0.01f;
    float value1 = Calc(t);
    float value2 = Calc(t + delta); 

    // newtons
    for(int i=0; i<3; i++){
        float slope = (value2 - value1) / delta;

        t = t - value1 / slope;

        value1 = Calc(t);
        value2 = Calc(t + delta);
    }

    result = CalcVec(t);

    return result;
}
