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
#include "Cue.h"

const bool soundEnabled = true;

const double nameAreaRadius = 1.5;
const double deacceleration = 1.5;
const double zoomScale = 1.6;

class Game{
public:
	Game(int w, int h, ConsolePanel *screen, ConsolePanel *zoomWindow);
	~Game();

	void KeyPressed(char c);

	void DragCue(double amount);
	void ResetAndActivateCue();
	void ReleaseCue();

	void Update(double dt);
	void UpdateScreen();

private:
	double cueMultiplier = 50.0;

	// Zoom window
	ConsolePanel *zoomWindow;

	// Screen
	ConsolePanel *screen;
	double width, height;

	// Game
	COLOR cueColor = WHT;
	Cue cue;
	Vec2d cueBallPosition = Vec2d(0, 0);
	double cueBallVel = 0.0;

	std::vector<Ball> balls;
	int table_side_x = 20;
	int table_side_y = 10;
	double ballRadius = 0.0;
	int table_x, table_y, table_w, table_h;

	void DrawBall(Ball& ball);

	// Logic
	bool HandleWallCollisions();
	bool HandleBallCollisions();

	// Init functions
	void InitDefaultGame();
};

#endif // __GAME_H__