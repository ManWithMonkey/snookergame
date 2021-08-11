#include "Game.hpp"

Game::Game(){
    Reset();

    lastUpdate = std::chrono::steady_clock::now();
}

void Game::Update(){
    float w = GetWidth();
    float h = GetHeight();

    for(Ball& ball : balls){
        float x = ball.pos.x;
        float y = ball.pos.y;

        float velx = std::abs(ball.vel.x);
        float vely = std::abs(ball.vel.y);

        // totally out of bounds
        if(x < 0.f)     ball.vel.x = velx;
        if(y < 0.f)     ball.vel.y = vely;
        if(x > w - 1.f) ball.vel.x = -velx;
        if(y > h - 1.f) ball.vel.y = -vely;

        // const float deacceleration = 0.9f;
        // ball.vel.x *= (1.f - deltaTime * deacceleration);
        // ball.vel.y *= (1.f - deltaTime * deacceleration);

        // position change
        ball.dpos.x = ball.vel.x * deltaTime;
        ball.dpos.y = ball.vel.y * deltaTime;

        // correct collisions
        bool collisionsLastIteration = true;
        for(int i=0; (i<MAX_COLLISIONS_ITERS) && collisionsLastIteration; i++){
            collisionsLastIteration = false;

            float minDistance = 10000000.f;
            int lineIndex = 0;
            vec2 normalMin, centerMin, closestMin, mirrorMin;

            for(Line& line : lines){
                if(MovingCircleCollidesWithStaticLine(ball.pos, ball.dpos, ball.r, line.a, line.b)){
                    vec2 collisionCircleCenter = MovingCircleCollisionPointWithLine(ball.pos, ball.dpos, ball.r, line.a, line.b);
                    vec2 closest = LineClosestPointFromPoint(line.a, line.b, ball.pos);

                    float distance = Norm(collisionCircleCenter - closest);

                    if(distance > minDistance)
                        continue;

                    minDistance = distance;
                    centerMin = collisionCircleCenter;
                    closestMin = closest;
                    normalMin = UnitVector(closest - ball.pos); // line.nu
                    mirrorMin = MirrorVectorFromNormal(ball.pos + ball.dpos - collisionCircleCenter, normalMin);
                    // vec2 mirroredDst = collisionCircleCenter + mirror;

                    collisionsLastIteration = true;
                }
            }

            if(collisionsLastIteration){
                float l = Norm(ball.dpos);
                float mirrorl = Norm(mirrorMin);

                ball.pos = ball.pos + UnitVector(ball.dpos) * (l - mirrorl) * MIRROR_LOSS;

                ball.dpos = UnitVector(mirrorMin) * mirrorl            * DPOS_LOSS;
                ball.vel = MirrorVectorFromNormal(ball.vel, normalMin) * VEL_LOSS;
            }
        }

        // add position change
        ball.pos.x += ball.dpos.x;
        ball.pos.y += ball.dpos.y;
    }

    for(Line& line : lines)
        line.UpdateNormal();

    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
    lastUpdate = now;
}

void Game::Draw(){
    for(Ball& ball : balls){
        DrawBall(ball, 'O');
    }

    for(Line& line : lines){
        DrawLine(line, '#');
    }
}

void Game::Reset(){
    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };

    balls.clear();
    lines.clear();

    Ball ball;

    ball.pos = {20, 20};
    ball.vel = {-125.f, 63.f};
    ball.r = 2.f;

    balls.push_back(ball);

    float t = 5.f;
    float l = 8.f;
    float b = GetHeight() - t - 1.f;
    float r = GetWidth() - l - 1.f;

    float holer = 3.5f;

    top     = {{l + holer, t}, {r - holer, t}};
    bottom  = {{l + holer, b}, {r - holer, b}};
    left    = {{l, t + holer}, {l, b - holer}};
    right   = {{r, t + holer}, {r, b - holer}};

    lines.push_back(top);
    lines.push_back(bottom);
    lines.push_back(left);
    lines.push_back(right);

    for(vec3 p : {
        vec3{l, t, 1.f * 3.14159f * 0.5f},
        vec3{l, b, 0.f * 3.14159f * 0.5f},
        vec3{r, b, 3.f * 3.14159f * 0.5f},
        vec3{r, t, 2.f * 3.14159f * 0.5f}
    }){
        int pc = 8;
        float da = 1.5f * 3.14159f / (float)pc;
        vec2 point = vec2{cos(p.z), sin(p.z)} * holer;
        for(int i=0; i<=pc; i++){
            vec2 center = {p.x, p.y};
            vec2 next = vec2{cos(p.z + da * (float)i), sin(p.z + da * (float)i)} * holer;
            lines.push_back({point + center, next + center});
            point = next;
        }
    }

    const int extra = 0;

    for(int i=0; i<extra; i++){
        lines.push_back({});
        lines.back().a.x = 3.f + frand() * (GetWidth()  - 6.f);
        lines.back().a.y = 3.f + frand() * (GetHeight() - 6.f);
        lines.back().b.x = 3.f + frand() * (GetWidth()  - 6.f);
        lines.back().b.y = 3.f + frand() * (GetHeight() - 6.f);
    }
}

void Game::DrawBall(const Ball& ball, char c){
    DrawFunctions::DrawSolidBall(ball.pos.x, ball.pos.y, ball.r, c);
}

void Game::DrawLine(const Line& line, char c){
    float x1 = line.a.x;
    float y1 = line.a.y;
    float x2 = line.b.x;
    float y2 = line.b.y;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
}
