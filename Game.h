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
    bool striped;

    Vec2d lastDeltaPosition; // movement at last iteration, useful for collisions

    Ball();
    Ball(double x, double y, double radius, char name, bool striped);

    bool CollidesWith(const Ball& other) const;
};

class Game{
public:
    Game(Window* screen, Window* zoomWindow);
    ~Game();

    void Update(double dt);
    void UpdateScreen();

private:
    // Constants
    const bool soundEnabled = true;
    const int cueVelocity = 10.0;
    const double defaultBallRadius = 2.5;
    const double nameAreaRadius = 0.5;
    const double deacceleration = 0.05;
    const double zoomScale = 1.6;

    // Zoom stuff
    Vec2d whiteBallPos = Vec2d(0, 0);

    // Screen
    Window *screen, *zoomWindow;
    double width, height;

    // Game
    std::vector<Ball> balls;

    // Logic
    bool HandleWallCollisions();
    bool HandleBallCollisions();

    // Init functions
    void InitDefaultGame();
};

#endif // __GAME_H__