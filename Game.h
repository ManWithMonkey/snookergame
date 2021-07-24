#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "Vec2d.h"
#include "Console.h"
#include <random>

#include "Window.h"

struct Ball{
    Vec2d pos;
    Vec2d vel; // per second
    double radius;
    bool white;
    char name;

    Vec2d lastDeltaPosition; // movement at last iteration, useful for collisions

    Ball();
    Ball(double x, double y, double radius, char name);

    bool CollidesWith(const Ball& other) const;
};

class Game{
public:
    Game(Window* screen);
    ~Game();

    void Update(double dt);
    void UpdateScreen();

private:
    // Constants
    const int cueVelocity = 1000.0;
    const double defaultBallRadius = 3.5;
    const double nameAreaRadius = 1.5;
    const double deacceleration = 0.05;

    // Screen
    Window* screen;
    double width, height;

    // Game
    std::vector<Ball> balls;

    // Logic
    void HandleWallCollisions();
    void HandleBallCollisions();

    // Init functions
    void InitDefaultGame();
};

#endif // __GAME_H__