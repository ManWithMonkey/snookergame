#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Vec2d.h"
#include "Console.h"

struct Ball{
    Vec2d pos;
    Vec2d vel;
};

class Game{
    Console screen;
    std::vector<Ball> balls;

public:
    Game(int w, int h);

    void Update(double dt);
    void Draw();
};

#endif // __GAME_H__