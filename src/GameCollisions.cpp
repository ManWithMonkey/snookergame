#include "GameCollisions.hpp"









/* TODO

- make use of GetClosest(&) in GetClosest()

*/











BallBallCollision GameCollisions::GetClosestBallBallCollision(Ball& ball){
    std::vector<BallBallCollision> collisions;

    for(int j = 0; j < balls.size(); j ++){
        Ball& other = balls[j];
        if(!other.active || &other == &ball)
            continue;

        double collisionScalar = GetCollisionPointMovementScalarNewton(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
        vec2 collisionPointCenter1 = ball.pos   + ball.dpos     * collisionScalar;
        vec2 collisionPointCenter2 = other.pos  + other.dpos    * collisionScalar;

        bool collides = MovingCirclesCollide(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
        bool collides2 = (collisionScalar > 0.0) && (collisionScalar <= 1.0);

        if(collides && collides2){
            auto result = GetNewDPositionsAfterCollision(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);

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

            collision.i = std::distance(&balls[0], &ball);
            collision.j = j;
            collision.nocollision = false;
            collisions.push_back(collision);
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

BallLineCollision GameCollisions::GetClosestBallLineCollision(Ball& ball){
    std::vector<BallLineCollision> collisions;

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
            collision.b = std::distance(&balls[0], &ball);
            collision.l = j;
            collision.pos = ball.pos + UnitVector(ball.dpos) * (totalMotionLength - mirrorMotionLength) * MIRROR_LOSS * 0.0;
            collision.dpos = UnitVector(mirror) * mirrorMotionLength * DPOS_LOSS;
            collision.vel = MirrorVectorFromNormal(ball.vel, normal) * line.holeBounceFactor * VEL_LOSS;
            collision.nocollision = false;
            collision.scalarOfDeltatime = 1.0 - mirrorMotionLength / totalMotionLength;

            double scalar = collision.scalarOfDeltatime;
            if(scalar >= 0.0)
                collisions.push_back(collision);
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

BallBallCollision GameCollisions::GetClosestBallBallCollision(){

    std::vector<BallBallCollision> collisions;

    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];
        if(!ball.active)
            continue;

        for(int j = i + 1; j < balls.size(); j ++){
            Ball& other = balls[j];
            if(!other.active)
                continue;

            double collisionScalar = GetCollisionPointMovementScalarNewton(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
            vec2 collisionPointCenter1 = ball.pos   + ball.dpos     * collisionScalar;
            vec2 collisionPointCenter2 = other.pos  + other.dpos    * collisionScalar;

            bool collides = MovingCirclesCollide(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
            bool collides2 = (collisionScalar > 0.0) && (collisionScalar <= 1.0);

            if(collides && collides2){
                auto result = GetNewDPositionsAfterCollision(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);

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
                collision.j = j;
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

BallLineCollision GameCollisions::GetClosestBallLineCollision(){

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
                collision.vel = MirrorVectorFromNormal(ball.vel, normal) * line.holeBounceFactor * VEL_LOSS;
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


void GameCollisions::HandleCollisionsAndApplyMotion(){

    // inefficient, might re-calculate unrelated collisions that would never be affected by one another

    for(int i=0; i<MAX_COLLISIONS_ITERS; i++){
        BallBallCollision bbcoll = GetClosestBallBallCollision();
        BallLineCollision blcoll = GetClosestBallLineCollision();

        bool apply_ballball_instead_of_ballline;

        bool b = !bbcoll.nocollision;
        bool l = !blcoll.nocollision;

        if(!b && !l){
            // no more collisions, no need to iterate
            break;
        }
        else if(b && l){
            apply_ballball_instead_of_ballline = bbcoll.scalarOfDeltatime < blcoll.scalarOfDeltatime;
        }
        else if(b){
            apply_ballball_instead_of_ballline = true;
        }
        else if(l){
            apply_ballball_instead_of_ballline = false;
        }
        
        // apply ball collision
        if(apply_ballball_instead_of_ballline){
            Ball& ball = balls[bbcoll.i];
            Ball& other = balls[bbcoll.j];

            ball.pos    = bbcoll.pos1;
            other.pos   = bbcoll.pos2;

            ball.dpos   = bbcoll.dpos1;
            other.dpos  = bbcoll.dpos2;

            ball.vel  = bbcoll.vel1;
            other.vel = bbcoll.vel2;
        }

        // apply line collision
        if(!apply_ballball_instead_of_ballline){
            int i = blcoll.b;

            Ball& ball = balls[i];

            ball.pos    = blcoll.pos;
            ball.dpos   = blcoll.dpos;
            ball.vel    = blcoll.vel;
        }
    }

    // add rest of motion
    for(Ball& ball : balls){
        ball.pos.x += ball.dpos.x;
        ball.pos.y += ball.dpos.y;
    }

    HandleClipping();
}

void GameCollisions::HandleClipping(){

    // balls inside balls
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        for(int j = i + 1; j < balls.size(); j ++){
            Ball& other = balls[j];

            double minDistance = (other.r + ball.r) * 1.0;
            double distance = Norm(other.pos - ball.pos);

            if(distance < minDistance){
                vec2 u = UnitVector(other.pos - ball.pos);

                double motion = (minDistance - distance) * 0.501;
                
                ball.pos  = ball.pos  - u * motion;
                other.pos = other.pos + u * motion;
            }
        }
    }

    // balls inside lines
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        for(int j = 0; j < lines.size(); j ++){
            Line& line = lines[j];

            double minDistance = ball.r * 1.0;
            double distance = LinePointDistance(line.a, line.b, ball.pos);

            if(distance < minDistance){
                vec2 u = UnitVector(LineClosestPointFromPoint(line.a, line.b, ball.pos) - ball.pos);

                double motion = (minDistance - distance) * 1.001;
                ball.pos  = ball.pos - u * motion;
            }
        }
    }
}
