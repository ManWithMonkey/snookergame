#include "MathFunctions.hpp"

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
    return vec2{cos(angle), sin(angle)} * length;
}

// REMOVE
vec2 Add(vec2 a, vec2 b){
    return {a.x + b.x, a.y + b.y};
}

vec2 Subtract(vec2 a, vec2 b){
    return {a.x - b.x, a.y - b.y};
}

vec2 Multiply(vec2 a, double s){
    return {a.x * s, a.y * s};
}
// END OF REMOVE

bool AABB(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    double x1 = std::min(a1.x, b1.x);
    double y1 = std::min(a1.y, b1.y);
    double w1 = std::max(a1.x, b1.x) - x1;
    double h1 = std::max(a1.y, b1.y) - y1;

    double x2 = std::min(a2.x, b2.x);
    double y2 = std::min(a2.y, b2.y);
    double w2 = std::max(a2.x, b2.x) - x2;
    double h2 = std::max(a2.y, b2.y) - y2;

    return !(
        x1 + w1 < x2 ||
        y1 + h1 < y2 ||
        x2 + w2 < x1 ||
        y2 + h2 < y1
    );
}

bool LineLineCollision(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    vec2 n1 = NormalUnit(b1 - a1);
    vec2 n2 = NormalUnit(b2 - a2);

    double v1 = DotProduct(n1, a2 - a1);
    double v2 = DotProduct(n1, b2 - a1);
    double v3 = DotProduct(n2, a1 - a2);
    double v4 = DotProduct(n2, b1 - a2);

    return (v1 * v2 < 0.0) && (v3 * v4 < 0.0);
}

bool MovingCircleCollidesWithStaticLine(vec2 p, vec2 dp, double r, vec2 a, vec2 b){
    vec2 p2 = {p.x + dp.x, p.y + dp.y};

    // min distance over movement
    double minDist = LineLineDistance(p, p2, a, b);

    // distance was less than radius at one point -> collided
    if(minDist < r){
        return true;
    }
    else{
        return false;
    }
}

bool MovingCirclesCollide(vec2 p1, vec2 dp1, double r1, vec2 p2, vec2 dp2, double r2){
    // return LineLineDistance(p1, p1 + dp1, p2, p2 + dp2) <= r1 + r2;

    // quick fix
    double scalar = GetCollisionPointMovementScalarNewton(p1, dp1, r1, p2, dp2, r2);
    double distance = Norm(
        (p1 + dp1 * scalar) -
        (p2 + dp2 * scalar)
    );
    return distance <= r1 + r2 + 1E-5f;
}

double PointPointDistance(vec2 a, vec2 b){
    return Norm(b - a);
}

double LinePointDistance(vec2 a, vec2 b, vec2 p){
    vec2 u1 = UnitVector(b - a);
    vec2 u2 = UnitVector(a - b);

    double v1 = DotProduct(u1, p - a);
    double v2 = DotProduct(u2, p - b);

    if(v1 * v2 > 0.0){
        vec2 n = Normal(u1);
        double v = DotProduct(n, p - a);
        return std::abs(v);
    }
    else{
        return std::min(
            Norm(p - a),
            Norm(p - b)
        );
    }
}

double LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2){
    if(LineLineCollision(a1, b1, a2, b2)){
        return 0.0;
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

    double v1 = DotProduct(u1, p - a);
    double v2 = DotProduct(u2, p - b);

    if(v1 * v2 > 0.0){
        vec2 n = Normal(u1);
        double v = DotProduct(n, p - a);

        return p - n * v;
    }
    else{
        double dist1 = Norm(p - a);
        double dist2 = Norm(p - b);

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

    double scalar1 = DotProduct(n, v1);
    double scalar2 = DotProduct(n, v2);

    double slope = scalar2 - scalar1;

    double t = - scalar1 / slope;

    vec2 p = a1 + u * t;

    return p;
}

vec2 MovingCircleCollisionPointWithLine(vec2 p, vec2 dp, double r, vec2 a, vec2 b){
    // assumes that it does collide
    vec2 result = {0, 0};

    vec2 dline = Subtract(b, a);
    vec2 uline = UnitVector(dline);
    vec2 n = Normal(uline);

    vec2 dmotion = dp;
    vec2 umotion = UnitVector(dmotion);
    
    auto CalcVec = [&](double scalar) -> vec2 {
        return p + umotion * scalar;
    };

    auto Calc = [&](double scalar) -> double {
        vec2 cp = CalcVec(scalar);
        return PointPointDistance(LineClosestPointFromPoint(a, b, cp), cp) - r;
    };

    // double l = Norm(dp);
    double t = 0.0;
    double delta = 1E-5;
    double value1 = Calc(t);
    double value2 = Calc(t + delta); 

    // newtons
    for(int i=0; i<6; i++){
        if(value1 <= 0.0){
            return CalcVec(t);
        }

        double slope = (value2 - value1) / delta;

        t = t - value1 / slope;

        value1 = Calc(t);
        value2 = Calc(t + delta);
    }

    result = CalcVec(t);

    return result;
}

double GetCollisionPointMovementScalarNewton(vec2 p1, vec2 dp1, double r1, vec2 p2, vec2 dp2, double r2){
    auto GetDistance = [&](double t){
        vec2 dst1 = p1 + dp1 * t;
        vec2 dst2 = p2 + dp2 * t;

        return Norm(dst2 - dst1) - r1 - r2;
    };
    
    const double dt = 1E-5;
    double t = 0.0;

    const int NEWTON_ITERATIONS = 10;
    for(int i=0; i<NEWTON_ITERATIONS; i++){
        double distance1 = GetDistance(t);
        double distance2 = GetDistance(t + dt);
        double slope = (distance2 - distance1) / dt;

        if(distance1 <= 0.0){
            return t;
        }

        t -= distance1 / slope;
    }

    return t;
}

std::pair<vec2, vec2> GetNewVelocities(vec2 p1, vec2 dp1, double r1, vec2 p2, vec2 dp2, double r2){
    std::pair<vec2, vec2> result;
    
    double collisionScalar = GetCollisionPointMovementScalarNewton(p1, dp1, r1, p2, dp2, r2);
    vec2 collisionPointCenter1 = p1 + dp1 * collisionScalar;
    vec2 collisionPointCenter2 = p2 + dp2 * collisionScalar;

    dp1 = dp1 * (1.0 - collisionScalar);
    dp2 = dp2 * (1.0 - collisionScalar);

    vec2 n = UnitVector(collisionPointCenter2 - collisionPointCenter1);
    vec2 a = dp1;
    vec2 v = dp2 - a;

    vec2 x = Normal(n);
    vec2 y = n;

    double s = DotProduct(v, x);
    double t = DotProduct(v, y);

    vec2 vx = x * s;
    vec2 vy = y * t;

    vec2 resx = vy + a;
    vec2 resy = vx + a;

    resx = resx * (1.0 / (1.0 - collisionScalar));
    resy = resy * (1.0 / (1.0 - collisionScalar));

    result = {resx, resy};

    return result;
}
