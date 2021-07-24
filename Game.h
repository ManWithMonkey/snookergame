#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "Vec2d.h"
#include "Console.h"
#include <random>

struct Ball{
    Vec2d pos;
    Vec2d vel; // per second

    Ball(double x, double y);
};

class Game{
    // Screen
    double width, height;
    Console screen;

    // Game
    std::vector<Ball> balls;

    // Constants
    const double ballRadius = 2.0;
    const double deacceleration = 0.3;

    //Drawing
    void DrawSphere(double x, double y, double r);

    void DrawGame();

    // Logic
    void HandleWallCollisions();

    // Init functions
    void InitDefaultGame();

    //Misc 
    void DrawTestLuminosity();

public:
    Game(int w, int h);

    void Update(double dt);
    void Draw();
};

#endif // __GAME_H__