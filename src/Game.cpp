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

    lastUpdate = std::chrono::steady_clock::now();
}

void Game::Update(){
    for(Ball& ball : balls){
        float x = ball.pos.x;
        float y = ball.pos.y;

        float velx = std::abs(ball.vel.x);
        float vely = std::abs(ball.vel.y);

        if(x < ball.r)                              ball.vel.x = velx;
        if(y < ball.r)                              ball.vel.y = vely;
        if(x > (float)GetWidth()  - 1.f - ball.r)   ball.vel.x = -velx;
        if(y > (float)GetHeight() - 1.f - ball.r)   ball.vel.y = -vely;

        ball.pos.x += ball.vel.x * deltaTime;
        ball.pos.y += ball.vel.y * deltaTime;
    }

    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
    lastUpdate = now;
}

void Game::Draw(){
    for(Ball& ball : balls){
        DrawBall(ball);
    }

    for(Line& line : lines){
        DrawLine(line);
    }
}
