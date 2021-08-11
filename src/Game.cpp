#include "Game.hpp"

Game::Game(){
    Ball ball;

    ball.pos = {20, 20};
    ball.vel = {-75.f, 20.f};
    ball.r = 3.f;

    balls.push_back(ball);

    Line l1;
    l1.a = {4, 2};
    l1.b = {10, 2};
    l1.UpdateNormal();
    lines.push_back(l1);
    lines.push_back(l1);
    lines.push_back(l1);
    lines.push_back(l1);

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

        // position change
        ball.dpos.x = ball.vel.x * deltaTime;
        ball.dpos.y = ball.vel.y * deltaTime;

        // correct collisions
        const int MAX_COLLISIONS_ITERS = 3;
        bool collisionsLastIteration = true;
        for(int i=0; (i<MAX_COLLISIONS_ITERS) && collisionsLastIteration; i++){
            collisionsLastIteration = false;

            for(Line& line : lines){
                if(MovingCircleCollidesWithStaticLine(ball.pos, ball.dpos, ball.r, line.a, line.b)){
                    vec2 collision = MovingCircleCollisionPointWithLine(ball.pos, ball.dpos, ball.r, line.a, line.b);
                    // vec2 normal = UnitVector(collision - ball.pos);
                    vec2 mirror = MirrorVectorFromNormal(ball.pos + ball.dpos - collision, line.nu);
                    vec2 mirroredDst = collision + mirror;
                    float l = Norm(ball.dpos);
                    float mirrorl = Norm(mirror);

                    ball.pos = ball.pos + UnitVector(ball.dpos) * (l - mirrorl) * 0.9f;

                    ball.dpos = UnitVector(mirror) * mirrorl;
                    ball.vel = MirrorVectorFromNormal(ball.vel, line.nu);

                    collisionsLastIteration = true;
                }
            }
        }

        // add position change
        ball.pos.x += ball.dpos.x;
        ball.pos.y += ball.dpos.y;
    }

    float t = 3.f;
    float l = 5.f;
    float b = h - 4.f;
    float r = w - 6.f;

    top     = {{l, t}, {r, t}};
    bottom  = {{l, b}, {r, b}};
    left    = {{l, t}, {l, b}};
    right   = {{r, t}, {r, b}};

    lines[0] = top;
    lines[1] = bottom;
    lines[2] = left;
    lines[3] = right;

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

void Game::Randomize(){
    const int extra = 4;

    if(lines.size() < 4 + extra){
        lines.resize(4 + extra);
    }
    
    balls[0].pos = {20, 20};
    balls[0].vel = {-75.f, 20.f};

    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };

    for(int i=0; i<extra; i++){
        lines[4 + i].a.x = 3.f + frand() * (GetWidth() - 6.f);
        lines[4 + i].a.y = 3.f + frand() * (GetHeight() - 6.f);
        lines[4 + i].b.x = 3.f + frand() * (GetWidth() - 6.f);
        lines[4 + i].b.y = 3.f + frand() * (GetHeight() - 6.f);
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
