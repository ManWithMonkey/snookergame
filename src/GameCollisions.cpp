#include "Game.hpp"

BallBallCollision Game::GetClosestBallBallCollision(){

    std::vector<BallBallCollision> collisions;

    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];
        if(!ball.active)
            continue;

        for(int i2 = i + 1; i2 < balls.size(); i2 ++){
            Ball& other = balls[i2];
            if(!other.active)
                continue;

            double collisionScalar = GetCollisionPointMovementScalarNewton(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
            vec2 collisionPointCenter1 = ball.pos   + ball.dpos     * collisionScalar;
            vec2 collisionPointCenter2 = other.pos  + other.dpos    * collisionScalar;

            bool collides = MovingCirclesCollide(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
            bool collides2 = (collisionScalar > 0.0) && (collisionScalar <= 1.0);

            if(collides && collides2){
                auto result = GetNewVelocities(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);

                vec2 mirror1 = result.first;
                vec2 mirror2 = result.second;

                vec2 u1 = UnitVector(mirror1);
                vec2 u2 = UnitVector(mirror2);

                double dl1 = Norm(mirror1);
                double dl2 = Norm(mirror2);
                double l1 = Norm(ball.vel);
                double l2 = Norm(other.vel);

                double dl = dl1 + dl2;
                double l  = l1  + l2;

                BallBallCollision collision;
                collision.pos1 = collisionPointCenter1;
                collision.pos2 = collisionPointCenter2;
                collision.dpos1 = mirror1 * DPOS_LOSS;
                collision.dpos2 = mirror2 * DPOS_LOSS;
                collision.vel1 = u1 * l * (dl1 / dl) * VEL_LOSS;
                collision.vel2 = u2 * l * (dl2 / dl) * VEL_LOSS;
                collision.scalarOfDeltatime = collisionScalar;

                collision.i = i;
                collision.j = i2;
                collision.nocollision = false;
                collisions.push_back(collision);
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
        BallBallCollision nocollision;
        nocollision.nocollision = true;
        return nocollision;
    }
}

BallLineCollision Game::GetClosestBallLineCollision(){

    std::vector<BallLineCollision> collisions;

    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];
        if(!ball.active)
            continue;

        // find first collision
        for(int j=0; j<lines.size(); j++){
            Line& line = lines[j];

            if(MovingCircleCollidesWithStaticLine(ball.pos, ball.dpos, ball.r, line.a, line.b)){
                vec2 center = MovingCircleCollisionPointWithLine(ball.pos, ball.dpos, ball.r, line.a, line.b);
                vec2 closest = LineClosestPointFromPoint(line.a, line.b, ball.pos);

                double distance = Norm(center - closest);

                vec2 normal = UnitVector(closest - ball.pos);
                vec2 mirror = MirrorVectorFromNormal(ball.pos + ball.dpos - center, normal);

                double totalMotionLength     = Norm(ball.dpos);
                double mirrorMotionLength    = Norm(mirror);

                BallLineCollision collision;
                collision.b = i;
                collision.l = j;
                collision.pos = ball.pos + UnitVector(ball.dpos) * (totalMotionLength - mirrorMotionLength) * MIRROR_LOSS * 0.0;
                collision.dpos = UnitVector(mirror) * mirrorMotionLength * DPOS_LOSS;
                collision.vel = MirrorVectorFromNormal(ball.vel, normal) * VEL_LOSS;
                collision.nocollision = false;
                collision.scalarOfDeltatime = 1.0 - mirrorMotionLength / totalMotionLength;

                double scalar = collision.scalarOfDeltatime;
                if(scalar >= 0.0)
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
        BallLineCollision nocollision;
        nocollision.nocollision = true;
        return nocollision;
    }
}


void Game::UpdatePositionsAndHandleCollisions(){

    for(int i=0; i<MAX_COLLISIONS_ITERS; i++){
        BallBallCollision bbcoll = GetClosestBallBallCollision();
        BallLineCollision blcoll = GetClosestBallLineCollision();

        bool dotheball_insteadof_theline;

        bool b = !bbcoll.nocollision;
        bool l = !blcoll.nocollision;

        if(!b && !l){
            // continue;
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

void Game::HandleClippingIfNecessary(){
    // balls in balls
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        for(int i2 = i + 1; i2 < balls.size(); i2 ++){
            Ball& other = balls[i2];

            double minDistance = (other.r + ball.r) * 1.0;
            double distance = Norm(other.pos - ball.pos);

            if(distance < minDistance){
                vec2 u = UnitVector(other.pos - ball.pos);

                double hdd = (minDistance - distance) * 0.51;
                
                ball.pos  = ball.pos  - u * hdd;
                other.pos = other.pos + u * hdd;

                vec2 rv1 = ball.vel - other.vel;
                vec2 rv2 = other.vel - ball.vel;

                vec2 mirror1 = MirrorVectorFromNormal(rv1, u);
                vec2 mirror2 = MirrorVectorFromNormal(rv2, u);

                vec2 v1 = ball.vel * (1.0 - Norm(mirror1) / Norm(ball.vel)) + mirror1;
                vec2 v2 = other.vel * (1.0 - Norm(mirror2) / Norm(other.vel)) + mirror2;

                // ball.vel  = MirrorVectorFromNormal(ball.vel, u);
                // other.vel = MirrorVectorFromNormal(other.vel, u);
                // ball.vel  = v1;
                // other.vel = v2;

                ball.vel = ball.vel - u * hdd;
                other.vel = other.vel + u * hdd;
            }
        }
    }

    // balls in lines
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        for(int i2 = 0; i2 < lines.size(); i2 ++){
            Line& line = lines[i2];

            double minDistance = ball.r * 1.0;
            double distance = LinePointDistance(line.a, line.b, ball.pos);

            if(distance < minDistance){
                vec2 u = UnitVector(LineClosestPointFromPoint(line.a, line.b, ball.pos) - ball.pos);

                double hdd = (minDistance - distance) * 1.01;
                
                ball.pos  = ball.pos - u * hdd;
                ball.vel  = MirrorVectorFromNormal(ball.vel, u);
            }
        }
    }
}
