#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "Vec2d.h"
#include "Console.h"

struct Ball{
    Vec2d pos;
    Vec2d vel;
};

class Game{
    int width, height;
    Console screen;
    std::vector<Ball> balls;

    void DrawSphere(double x, double y, double r);
    void DrawTestLuminocity();

public:
    Game(int w, int h);

    void Update(double dt);
    void Draw();
};

#endif // __GAME_H__