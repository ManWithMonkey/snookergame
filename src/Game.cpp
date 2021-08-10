#include "Game.hpp"

Game::Game(){
    Ball ball;

    ball.pos = {4, 4};
    ball.vel = {-75.f, 20.f};
    ball.r = 3.f;

    balls.push_back(ball);

    Line l1;
    l1.a = {2, 2};
    l1.b = {10, 2};
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

        ball.pos.x += ball.vel.x * deltaTime;
        ball.pos.y += ball.vel.y * deltaTime;

        for(Line& line : lines){
            // float distance = PointDistance(line.a, line.b, balls[0]);
            // if(distance < )
        }
    }

    float t = 2.f;
    float l = 2.f;
    float b = h - 3.f;
    float r = w - 3.f;

    top     = {{l, t}, {r, t}};
    bottom  = {{l, b}, {r, b}};
    left    = {{l, t}, {l, b}};
    right   = {{r, t}, {r, b}};

    lines[0] = top;
    lines[1] = bottom;
    lines[2] = left;
    lines[3] = right;

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

    // DrawLine(bottom, '#');
    // DrawLine(right, '#');
    // DrawLine(left, '#');
    // DrawLine(top, '#');
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
