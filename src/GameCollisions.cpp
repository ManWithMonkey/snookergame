#include "Game.hpp"

BallBallCollision Game::GetClosestBallBallCollision(){
    // BallBallCollision retval;

    std::vector<BallBallCollision> collisions;

    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        for(int i2 = i + 1; i2 < balls.size(); i2 ++){
            Ball& other = balls[i2];

            float collisionScalar = GetCollisionPointMovementScalarNewton(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
            vec2 collisionPointCenter1 = ball.pos   + ball.dpos     * collisionScalar;
            vec2 collisionPointCenter2 = other.pos  + other.dpos    * collisionScalar;

            bool collides = MovingCirclesCollide(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);

            if(collides && (collisionScalar <= 1.f) && (collisionScalar > 0.f)){
                auto result = GetNewVelocities(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);

                vec2 mirror1 = result.first;
                vec2 mirror2 = result.second;

                vec2 u1 = UnitVector(mirror1);
                vec2 u2 = UnitVector(mirror2);

                float dl1 = Norm(ball.dpos);
                float dl2 = Norm(other.dpos);
                float l1 = Norm(ball.vel);
                float l2 = Norm(other.vel);

                float dl = dl1 + dl2;
                float l  = l1  + l2;

                // ball.pos    = collisionPointCenter1;
                // other.pos   = collisionPointCenter2;

                // ball.dpos   = mirror1;
                // other.dpos  = mirror2;

                // ball.vel  = u1 * l * (dl1 / dl);
                // other.vel = u2 * l * (dl2 / dl);

                BallBallCollision retval;
                retval.pos1 = collisionPointCenter1;
                retval.pos2 = collisionPointCenter2;
                retval.dpos1 = mirror1;
                retval.dpos2 = mirror2;
                retval.vel1 = u1 * l * (dl1 / dl);
                retval.vel2 = u2 * l * (dl2 / dl);
                retval.scalarOfDeltatime = collisionScalar;

                retval.i = i;
                retval.j = i2;
                retval.nocollision = false;
                // return retval;
                collisions.push_back(retval);
            }
        }
    }

    if(collisions.size()){
        return collisions[0];
    }
    else{
        BallBallCollision ret;
        return ret;
    }
}

BallLineCollision Game::GetClosestBallLineCollision(){
    BallLineCollision retval;

    return retval;
}


void Game::HandleCollisions(){
    // ball collisions

    BallBallCollision bbcoll = GetClosestBallBallCollision();

    if(!bbcoll.nocollision){
        int i = bbcoll.i;
        int i2 = bbcoll.j;

        Ball& ball = balls[i];
        Ball& other = balls[i2];

        ball.pos    = bbcoll.pos1;
        other.pos   = bbcoll.pos2;

        ball.dpos   = bbcoll.dpos1;
        other.dpos  = bbcoll.dpos2;

        ball.vel  = bbcoll.vel1;
        other.vel = bbcoll.vel2;
    }

    // line collisions
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        bool collisionsLastIteration = true;

        for(int i=0; (i<MAX_COLLISIONS_ITERS) && collisionsLastIteration; i++){
            collisionsLastIteration = false;

            float minDistance = MAXFLOAT;
            int firstCollisionIndex = 0;
            vec2 center;
            vec2 closest;

            // find fist collision
            for(int i=0; i<lines.size(); i++){
                Line& line = lines[i];

                if(MovingCircleCollidesWithStaticLine(ball.pos, ball.dpos, ball.r, line.a, line.b)){
                    vec2 collisionCircleCenter = MovingCircleCollisionPointWithLine(ball.pos, ball.dpos, ball.r, line.a, line.b);
                    vec2 closestPoint = LineClosestPointFromPoint(line.a, line.b, ball.pos);

                    float distance = Norm(collisionCircleCenter - closestPoint);

                    if(distance < minDistance){
                        minDistance             = distance;
                        firstCollisionIndex     = i;
                        center                  = collisionCircleCenter;
                        closest                 = closestPoint;

                        collisionsLastIteration = true;
                    }
                }
            }

            // apply collision
            if(collisionsLastIteration){
                Line& line = lines[firstCollisionIndex];

                vec2 normal = UnitVector(closest - ball.pos);
                vec2 mirror = MirrorVectorFromNormal(ball.pos + ball.dpos - center, normal);

                float totalMotionLength     = Norm(ball.dpos);
                float mirrorMotionLength    = Norm(mirror);

                ball.pos = ball.pos + UnitVector(ball.dpos) * (totalMotionLength - mirrorMotionLength) * MIRROR_LOSS;
                ball.dpos = UnitVector(mirror) * mirrorMotionLength * DPOS_LOSS;

                ball.vel = MirrorVectorFromNormal(ball.vel, normal) * VEL_LOSS;
            }
        }
    }

    for(Ball& ball : balls){
        ball.pos.x += ball.dpos.x;
        ball.pos.y += ball.dpos.y;
    }
}
