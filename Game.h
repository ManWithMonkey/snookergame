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
    double radius;

    Vec2d lastDeltaPosition; // movement at last iteration, useful for collisions

    Ball();
    Ball(double x, double y, double radius);

    bool CollidesWith(const Ball& other) const;
};

class Game{
public:
    Game();
    Game(int w, int h);
    ~Game();

    void Update(double dt);
    void Draw();

private:
    // Constants
    const int cueVelocity = 650.0;
    const int defaultWidth = 100;
    const int defaultHeight = 50;
    const double defaultBallRadius = 2.;
    const double deacceleration = 0.05;

    // Screen
    double width, height;
    Console screen;

    // Game
    std::vector<Ball> balls;

    //Drawing
    void DrawSphere(double x, double y, double r);

    void DrawGame();

    // Logic
    void HandleWallCollisions();
    void HandleBallCollisions();

    // Init functions
    void InitDefaultGame();

    //Misc 
    void DrawTestLuminosity();
};

#endif // __GAME_H__