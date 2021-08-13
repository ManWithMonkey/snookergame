#include "Game.hpp"

BallBallCollision Game::GetClosestBallBallCollision(){

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
                retval.dpos1 = mirror1 * DPOS_LOSS;
                retval.dpos2 = mirror2 * DPOS_LOSS;
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
        auto it = std::min_element(collisions.begin(), collisions.end(), [](const BallBallCollision& lhs, const BallBallCollision& rhs){
            return lhs.scalarOfDeltatime < rhs.scalarOfDeltatime;
        });

        return *it;
    }
    else{
        BallBallCollision ret;
        return ret;
    }
}

BallLineCollision Game::GetClosestBallLineCollision(){

    std::vector<BallLineCollision> collisions;

    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        // find first collision
        for(int j=0; j<lines.size(); j++){
            Line& line = lines[j];

            if(MovingCircleCollidesWithStaticLine(ball.pos, ball.dpos, ball.r, line.a, line.b)){
                vec2 center = MovingCircleCollisionPointWithLine(ball.pos, ball.dpos, ball.r, line.a, line.b);
                vec2 closest = LineClosestPointFromPoint(line.a, line.b, ball.pos);

                float distance = Norm(center - closest);

                vec2 normal = UnitVector(closest - ball.pos);
                vec2 mirror = MirrorVectorFromNormal(ball.pos + ball.dpos - center, normal);

                float totalMotionLength     = Norm(ball.dpos);
                float mirrorMotionLength    = Norm(mirror);

                BallLineCollision collision;
                collision.b = i;
                collision.l = j;
                collision.pos = ball.pos + UnitVector(ball.dpos) * (totalMotionLength - mirrorMotionLength) * MIRROR_LOSS * 0.f;
                collision.dpos = UnitVector(mirror) * mirrorMotionLength * DPOS_LOSS;
                collision.vel = MirrorVectorFromNormal(ball.vel, normal) * VEL_LOSS;
                collision.nocollision = false;
                collision.scalarOfDeltatime = 1.f - mirrorMotionLength / totalMotionLength;

                float scalar = collision.scalarOfDeltatime;
                if(scalar >= 0.f)
                    collisions.push_back(collision);
            }
        }
    }

    if(collisions.size() > 0){
        auto it = std::min_element(collisions.begin(), collisions.end(), [](const BallLineCollision& lhs, const BallLineCollision& rhs){
            return lhs.scalarOfDeltatime < rhs.scalarOfDeltatime;
        });

        return *it;
    }
    else{
        BallLineCollision retval;
        return retval;
    }
}


void Game::HandleCollisions(){

    for(int i=0; i<MAX_COLLISIONS_ITERS; i++){
        BallBallCollision bbcoll = GetClosestBallBallCollision();
        BallLineCollision blcoll = GetClosestBallLineCollision();

        bool dotheball_insteadof_theline;

        bool b = !bbcoll.nocollision;
        bool l = !blcoll.nocollision;

        if(!b && !l){
            break;
        }
        else if(b && l){
            dotheball_insteadof_theline = bbcoll.scalarOfDeltatime < blcoll.scalarOfDeltatime;
        }
        else if(b){
            dotheball_insteadof_theline = true;
        }
        else if(l){
            dotheball_insteadof_theline = false;
        }
        
        if(dotheball_insteadof_theline){
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

        if(!dotheball_insteadof_theline){
            int i = blcoll.b;

            Ball& ball = balls[i];

            ball.pos    = blcoll.pos;
            ball.dpos   = blcoll.dpos;
            ball.vel    = blcoll.vel;
        }
    }

    for(Ball& ball : balls){
        ball.pos.x += ball.dpos.x;
        ball.pos.y += ball.dpos.y;
    }
}
