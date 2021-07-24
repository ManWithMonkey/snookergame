#include "Game.h"

Game::Game(int w, int h) 
{
    width = w;
    height = h;
    screen = Console(w, h);

    InitDefaultGame();
}

void Game::Update(double dt) 
{
    for(Ball& ball : balls){
        ball.pos += ball.vel * dt;
        ball.vel *= (1.f - deacceleration * dt);
        HandleWallCollisions();
    }
}

void Game::Draw() 
{
    screen.Clear();
    DrawGame();
    screen.Draw();
}

void Game::DrawTestLuminosity() 
{
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            screen.PlotPixel(x, y, (double)(width - x) / (double)width);
        }
    }
}

void Game::InitDefaultGame() 
{
    auto _randScalar = []() -> double {
        return 2.0 * (double)(rand()) / (double)RAND_MAX - 1.0;
    };

    balls.clear();
    for(int i=0; i<10; i++){
        balls.push_back(Ball(2 + i * 6, 3));
        balls.back().vel = 100.0 * Vec2d(_randScalar(), _randScalar());
    }
}

void Game::DrawSphere(double x, double y, double r) 
{
    for(double ix = x - r; ix <= x + r; ix += 1.0){
        for(double iy = y - r; iy <= y + r; iy += 1.0){
            double distance = std::hypot(ix - x, iy - y);
            double luminosity = 1.0 - distance / r;
            
            screen.PlotPixel(ix, iy, luminosity);
        }
    }
}

void Game::DrawGame() 
{
    // for(Ball& ball : balls){
    //     DrawSphere(ball.pos.x, ball.pos.y, ballRadius);
    // }
    DrawTestLuminosity();
}

void Game::HandleWallCollisions() 
{
    for(Ball& ball : balls){
        if(ball.pos.x - ballRadius < 0)         { ball.vel.x *= -1.0; ball.pos.x = 2.0 * ballRadius - ball.pos.x; }
        if(ball.pos.y - ballRadius < 0)         { ball.vel.y *= -1.0; ball.pos.y = 2.0 * ballRadius - ball.pos.y; }
        if(ball.pos.x + ballRadius >= width)    { ball.vel.x *= -1.0; ball.pos.x = width - ((ball.pos.x + ballRadius) - width); }
        if(ball.pos.y + ballRadius >= height)   { ball.vel.y *= -1.0; ball.pos.y = height - ((ball.pos.y + ballRadius) - height); }
    }
}

Ball::Ball(double x, double y) :
    pos(Vec2d(x, y)), vel(Vec2d(0, 0))
{
}
