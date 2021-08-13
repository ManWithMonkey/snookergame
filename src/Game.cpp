#include "Game.hpp"

template<typename T>
std::string ToString(const T& rhs){
    std::string result;

    std::stringstream ss;
    ss << rhs;
    result += ss.str();

    return result;
}
static float scalarmax = -1000000000.f;
static float scalarmin = 1000000000.f;
static float lastscalar = 0.f;

Game::Game(){
    Reset();
    ResizeEvent();

    lastUpdate = std::chrono::steady_clock::now();
}

void Game::Draw(){
    for(Ball& ball : balls){
        if(ball.collided)
            DrawBall(ball, '.');
        else
            DrawBall(ball, 'O');
    }

    for(Line& line : lines){
        DrawLine(line, '#');
    }

    DrawFunctions::TypeString(0, 0, ToString(scalarmin) + ", " + ToString(scalarmax) + ", " + ToString(lastscalar));
}

void Game::ResizeEvent(){
    x_factor = (float)GetWidth()    / map_width; 
    y_factor = (float)GetHeight()   / map_height;
}

void Game::Reset(){
    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };

    balls.clear();
    lines.clear();

    const float l = 0.15f * map_width;
    const float t = 0.15f * map_height;
    const float r = map_width - l;
    const float b = map_height - t;
    const float holer = 0.06f;
    const float ballr = 0.9f;

    std::vector<vec2> pointBand;

    vec2 tr = {r, t};
    vec2 br = {r, b};
    vec2 bl = {l, b};
    vec2 tl = {l, t};
    vec2 tr_x = {r,             t + holer};
    vec2 tr_y = {r - holer,     t};
    vec2 br_x = {r,             b - holer};
    vec2 br_y = {r - holer,     b};
    vec2 bl_x = {l,             b - holer};
    vec2 bl_y = {l + holer,     b};
    vec2 tl_x = {l,             t + holer};
    vec2 tl_y = {l + holer,     t};

    vec2 corners[4][3]{
        {tr, tr_x, tr_y},
        {tl, tl_y, tl_x},
        {bl, bl_x, bl_y},
        {br, br_y, br_x}
    };

    float angleOffsets[4] = {
        1.f * 3.14159f * 0.5f,
        0.f * 3.14159f * 0.5f,
        3.f * 3.14159f * 0.5f,
        2.f * 3.14159f * 0.5f
    };

    for(int i=0; i<4; i++){
        pointBand.push_back(corners[i][1]);

        int pc = 8;
        float da = 1.5f * 3.14159f / (float)pc;
        for(int j=0; j<pc; j++){
            float ang = 2.f * 3.14159f - (float)j * da + angleOffsets[i];
            float length = holer;

            vec2 point = corners[i][0] + MakeVector(ang, length);
            pointBand.push_back(point);
        }
        
        pointBand.push_back(corners[i][2]);
    }
    
    lines.push_back({pointBand.back(), pointBand.front()});
    for(int i=1; i<pointBand.size(); i++){
        lines.push_back({
            pointBand[i],
            pointBand[i-1]
        });
    }

    for(int i=0; i<6; i++){
        Ball ball;
        ball.pos = {map_width / 2.f - 5.f * ballr + (float)i * 3.f * ballr, map_height / 2.f};
        ball.vel = vec2{-2.f + 4.f * frand(), -2.f + 4.f * frand()} * (map_width / 2.f);
        ball.r = ballr;

        balls.push_back(ball);
    }
}

void Game::Update(){
    float w = GetWidth();
    float h = GetHeight();

    for(int balli = 0; balli < balls.size(); balli++){
        Ball& ball = balls[balli];
        ball.collided = false;

        float x = ball.pos.x;
        float y = ball.pos.y;

        float velx = std::max(0.1f, std::abs(ball.vel.x));
        float vely = std::max(0.1f, std::abs(ball.vel.y));

        // totally out of bounds
        if(x < 0.f)     ball.vel.x = velx;
        if(y < 0.f)     ball.vel.y = vely;
        if(x >= map_width)  ball.vel.x = -velx;
        if(y >= map_height) ball.vel.y = -vely;

        ball.vel = ball.vel * (1.f - 0.1f * deltaTime);

        // position change
        ball.dpos.x = ball.vel.x * deltaTime;
        ball.dpos.y = ball.vel.y * deltaTime;
    }

    HandleCollisions();

    for(Ball& ball : balls){
        ball.pos.x += ball.dpos.x;
        ball.pos.y += ball.dpos.y;
    }

    // balls clipping with each other
    if(false)
    for(int balli = 0; balli < balls.size(); balli++){
        Ball& ball = balls[balli];

        for(int balli2 = balli + 1; balli2 < balls.size(); balli2 ++){
            Ball& other = balls[balli2];

            float minDistance = (other.r + ball.r) * 1.f;
            float distance = Norm(other.pos - ball.pos);

            if(distance < minDistance){
                vec2 u = UnitVector(other.pos - ball.pos);

                float hdd = (minDistance - distance) * 0.51f;
                
                ball.pos  = ball.pos  - u * hdd;
                other.pos = other.pos + u * hdd;
            }
        }
    }

    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
    lastUpdate = now;
}


void Game::HandleCollisions(){

    for(int i=0; i<MAX_COLLISIONS_ITERS; i++){

        std::vector<collision_t> bbcollisions = GetBallBallCollisions();
        std::vector<collision_t> blcollisions = GetBallLineCollisions();

        // combine
        std::vector<collision_t> collisions = bbcollisions;
        collisions.insert(collisions.end(), blcollisions.begin(), blcollisions.end());

        if(collisions.size() == 0){
            break;
        }

        // find first collision
        collision_t firstCollision = *std::min_element(collisions.begin(), collisions.end(), [](collision_t rhs, collision_t lhs) -> bool {
            return rhs.scalar < lhs.scalar;
        });

        // apply collision
        if(firstCollision.ballcollision){
            ApplyBallBallCollision(firstCollision);
        }
        else{
            ApplyBallLineCollision(firstCollision);
        }
    }
}

std::vector<collision_t> Game::GetBallBallCollisions(){
    std::vector<collision_t> collisions;

    for(int i = 0; i < balls.size(); i++){
        const Ball& ball = balls[i];

        for(int j = j + 1; j < balls.size(); j ++){
            const Ball& other = balls[j];

            float collisionScalar = GetCollisionPointMovementScalarNewton(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
            vec2 collisionPointCenter1 = ball.pos   + ball.dpos     * collisionScalar;
            vec2 collisionPointCenter2 = other.pos  + other.dpos    * collisionScalar;

            bool collides = MovingCirclesCollide(ball.pos, ball.dpos, ball.r, other.pos, other.dpos, other.r);
            bool collides2 = (collisionScalar >= 0.f) && (collisionScalar <= 1.f);

            if(collides){
                scalarmax = std::max(scalarmax, collisionScalar);
                scalarmin = std::min(scalarmin, collisionScalar);
                lastscalar = collisionScalar;

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

                // ball.pos    = collisionPointCenter1 - UnitVector(ball.dpos)     * 0.01f + mirror1 * 0.01f;
                // other.pos   = collisionPointCenter2 - UnitVector(other.dpos)    * 0.01f + mirror2 * 0.01f;

                // ball.dpos   = mirror1 * 1.f + u1 * 0.01f;
                // other.dpos  = mirror2 * 1.f + u2 * 0.01f;

                // ball.vel  = u1 * l * (dl1 / dl) * 1.f;
                // other.vel = u2 * l * (dl2 / dl) * 1.f; 
                
                // ball.collided = true;
                // other.collided = true;

                collision_t collision;
                collision.ballcollision = true;
                collision.ptr1 = (void*)&ball;
                collision.ptr2 = (void*)&other;
                collision.scalar = collisionScalar;
                collision.npos1 = collisionPointCenter1 - UnitVector(ball.dpos)     * 0.01f + mirror1 * 0.01f;
                collision.npos2 = collisionPointCenter2 - UnitVector(other.dpos)    * 0.01f + mirror2 * 0.01f;
                collision.ndpos1 = mirror1 * 1.f + u1 * 0.01f;
                collision.ndpos2 = mirror2 * 1.f + u2 * 0.01f;
                collision.nvel1 = u1 * l * (dl1 / dl) * 1.f;
                collision.nvel2 = u2 * l * (dl2 / dl) * 1.f;
                collisions.push_back(collision);
            }
        }
    }

    return collisions;
}

std::vector<collision_t> Game::GetBallLineCollisions(){
    std::vector<collision_t> collisions;

    for(int balli = 0; balli < balls.size(); balli++){
        Ball& ball = balls[balli];

        bool collisionsLastIteration = true;

        for(int i=0; (i<MAX_COLLISIONS_ITERS) && collisionsLastIteration; i++){
            collisionsLastIteration = false;

            float minDistance = MAXFLOAT;
            int firstCollisionIndex = 0;
            vec2 center;
            vec2 closest;

            // find first collision
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

            if(collisionsLastIteration){
                collision_t coll;
                coll.ballcollision = false;
                coll.ptr1 = (void*)&ball;
                coll.ptr2 = (void*)&(lines[firstCollisionIndex]);

                float totalDistance = Norm(ball.dpos);
                coll.scalar = minDistance / totalDistance;

                // collisions.push_back(coll);
            }

            // // apply collision
            // if(collisionsLastIteration){
            //     Line& line = lines[firstCollisionIndex];

            //     vec2 normal = UnitVector(closest - ball.pos);
            //     vec2 mirror = MirrorVectorFromNormal(ball.pos + ball.dpos - center, normal);

            //     float totalMotionLength     = Norm(ball.dpos);
            //     float mirrorMotionLength    = Norm(mirror);

            //     ball.pos = ball.pos + UnitVector(ball.dpos) * (totalMotionLength - mirrorMotionLength) * MIRROR_LOSS;
            //     ball.dpos = UnitVector(mirror) * mirrorMotionLength * DPOS_LOSS;

            //     ball.vel = MirrorVectorFromNormal(ball.vel, normal) * VEL_LOSS;
            // }
        }
    }

    return collisions;
}

void Game::ApplyBallBallCollision(collision_t collision){
    Ball& ball = *(Ball*)collision.ptr1;
    Ball& other = *(Ball*)collision.ptr2;

    ball.pos    = collision.npos1;
    other.pos   = collision.npos2;
    
    ball.dpos    = collision.ndpos1;
    other.dpos   = collision.ndpos2;

    ball.vel    = collision.nvel1;
    other.vel   = collision.nvel2;
    
    ball.collided = true;
    other.collided = true;
}

void Game::ApplyBallLineCollision(collision_t collision){
    Line& line = *(Line*)collision.ptr1;
    Ball& ball = *(Ball*)collision.ptr2;

    // vec2 normal = UnitVector(closest - ball.pos);
    // vec2 mirror = MirrorVectorFromNormal(ball.pos + ball.dpos - center, normal);

    // float totalMotionLength     = Norm(ball.dpos);
    // float mirrorMotionLength    = Norm(mirror);

    // ball.pos = ball.pos + UnitVector(ball.dpos) * (totalMotionLength - mirrorMotionLength) * MIRROR_LOSS;
    // ball.dpos = UnitVector(mirror) * mirrorMotionLength * DPOS_LOSS;

    // ball.vel = MirrorVectorFromNormal(ball.vel, normal) * VEL_LOSS;
}


void Game::DrawBall(const Ball& ball, char c){
    float x = ball.pos.x    * x_factor;
    float y = ball.pos.y    * y_factor;
    float rx = ball.r       * x_factor;
    float ry = ball.r       * y_factor;

    DrawFunctions::DrawSolidEllipse(x, y, rx, ry, c);
}

void Game::DrawLine(const Line& line, char c){
    float x1 = line.a.x * x_factor;
    float y1 = line.a.y * y_factor;
    float x2 = line.b.x * x_factor;
    float y2 = line.b.y * y_factor;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
}
