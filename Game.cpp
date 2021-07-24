#include "Game.h"

Game::Game(int w, int h) 
{
    screen = Console(w, h);
}

void Game::Update(double dt) 
{
    
}

void Game::Draw() 
{
    screen.Draw();
}
