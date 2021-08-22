#include "MathFunctions.hpp"

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
    // todo: make this better

    double scalar = GetCollisionPointMovementScalarNewton(p1, dp1, r1, p2, dp2, r2);
    double distance = Norm(
        (p1 + dp1 * scalar) -
        (p2 + dp2 * scalar)
    );
    return distance <= r1 + r2 + 1E-5;
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

    vec2 dline = b - a;
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

std::pair<vec2, vec2> GetNewDPositionsAfterCollision(vec2 p1, vec2 dp1, double r1, vec2 p2, vec2 dp2, double r2){
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

BallBallCollision GetBallsDuringCollision(const Ball& ball, const Ball& other){
    BallBallCollision result;

    double collisionScalar = GetCollisionPointMovementScalarNewton(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
    vec2 collisionPointCenter1 = ball.pos   + ball.dpos     * collisionScalar;
    vec2 collisionPointCenter2 = other.pos  + other.dpos    * collisionScalar;

    bool collides = MovingCirclesCollide(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
    bool collides2 = (collisionScalar > 0.0) && (collisionScalar <= 1.0);

    if(!collides || !collides2){
        result.nocollision = true;
        return result;
    }

    auto collResults = GetNewDPositionsAfterCollision(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);

    vec2 mirror1 = collResults.first;
    vec2 mirror2 = collResults.second;

    vec2 u1 = UnitVector(mirror1);
    vec2 u2 = UnitVector(mirror2);

    double dl1 = Norm(mirror1);
    double dl2 = Norm(mirror2);
    double l1 = Norm(ball.vel);
    double l2 = Norm(other.vel);

    double dl = dl1 + dl2;
    double l  = l1  + l2;

    result.pos1 = collisionPointCenter1;
    result.pos2 = collisionPointCenter2;
    result.dpos1 = mirror1;
    result.dpos2 = mirror2;
    result.vel1 = u1 * l * (dl1 / dl);
    result.vel2 = u2 * l * (dl2 / dl);
    result.scalarOfDeltatime = collisionScalar;
    result.nocollision = false;

    return result;
}
