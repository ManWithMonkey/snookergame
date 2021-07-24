#include "Game.h"

Game::Game(int w, int h) 
{
    width = w;
    height = h;
    screen = Console(w, h);
}

void Game::Update(double dt) 
{
    
}

void Game::Draw() 
{
    screen.Clear();
    DrawSphere(10, 10, 5);
    screen.Draw();
}

void Game::DrawTestLuminocity() 
{
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            screen.PlotPixel(x, y, (double)x / (double)width);
        }
    }
}

void Game::DrawSphere(double x, double y, double r) 
{
    for(double ix = x - r; ix <= x + r; ix += 1.0){
        for(double iy = y - r; iy <= y + r; iy += 1.0){
            double distance = std::hypot(ix - x, iy - y);
            double luminocity = 1.0 - distance / r;
            
            screen.PlotPixel(ix, iy, luminocity);
        }
    }
}
