#ifndef __GAME_H__
#define __GAME_H__

#include "Vec2d.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "Ball.h"
#include "Cue.h"

#include "NCursesWrapper.h"

const bool useSounds = false;

class Game{
public:
	Game();
	~Game();

	void KeyPressed(int key);

	void Update(double dt);
	void Draw(int w, int h);

private:
	void InitDefaultGame();

	bool CollidesWithWalls(const Ball& ball) const;
	bool CollidesWithOtherBalls(const Ball& ball) const;

	// returns true if cueball was in a collision
	bool HandleWallCollisions();
	bool HandleBallCollisions();

	void DrawBall(Ball& ball);

	void MoveCue(double dx, double dy);
	void ResetAndActivateCue();
	void ReleaseCue();

private:
	const int TABLE_COLOR_PAIR 		= FG_BG(COLOR_BLACK, COLOR_RED);
	const int PLAYAREA_COLOR_PAIR 	= FG_BG(COLOR_BLACK, COLOR_WHITE);
	const int CUE_COLOR_PAIR 		= FG_BG(COLOR_WHITE, COLOR_YELLOW);
	const int CUE_TARGET_COLOR_PAIR = FG_BG(COLOR_RED, COLOR_WHITE);
	const int BALL_ID_COLOR			= COLOR_BLACK;

	const double deacceleration = 1.5;

	const int table_side_x = 12;
	const int table_side_y = 8;

	// normalized values
	double game_width = 2.0;
	double game_height = 1.0;
	double x_scalar = 1.0;
	double y_scalar = 1.0;
	double table_x = 0.15;
	double table_y = 0.1;
	double table_w = 1.7;
	double table_h = 0.8;

	// game variables
	std::vector<Ball> balls;
	Cue cue;
	int cueBallIndex = 0;
};

#endif // __GAME_H__