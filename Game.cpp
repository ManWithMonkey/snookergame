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
            screen.PlotPixel(x, y, (double)x / (double)width);
        }
    }
}

void Game::InitDefaultGame() 
{
    balls.clear();
    for(int i=0; i<3; i++){
        balls.push_back(Ball(3 + i * 6, 3));
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
    for(Ball& ball : balls){
        DrawSphere(ball.pos.x, ball.pos.y, ballRadius);
    }
}

Ball::Ball(double x, double y) :
    pos(Vec2d(x, y))
{
}
