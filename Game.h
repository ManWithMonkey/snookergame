#ifndef __GAME_H__
#define __GAME_H__

#include "Console.h"
#include "Vec2d.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "Window.h"
#include "Ball.h"

const bool soundEnabled = true;

const int cueVelocity = 10.0;
const double nameAreaRadius = 1.5;
const double deacceleration = 0.05;
const double zoomScale = 1.6;

class Game{
public:
	Game(int w, int h, ConsolePanel *screen, ConsolePanel *zoomWindow);
	~Game();

	void Update(double dt);
	void UpdateScreen();

private:
	// Zoom window
	ConsolePanel *zoomWindow;

	// Screen
	ConsolePanel *screen;
	double width, height;

	// Game
	std::vector<Ball> balls;
	Vec2d cueBallPosition = Vec2d(0, 0);
	int table_side = 4;
	int table_x, table_y, table_w, table_h;

	void DrawBall(Ball& ball);

	// Logic
	bool HandleWallCollisions();
	bool HandleBallCollisions();

	// Init functions
	void InitDefaultGame();
};

#endif // __GAME_H__