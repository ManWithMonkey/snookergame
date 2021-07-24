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
    DrawTestLuminocity();
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
