#ifndef __BALL_H__
#define __BALL_H__

#include "Vec2d.h"

const int STRIPED 	= 0;
const int OTHER 	= 1; //rename this to something else

struct BallInfo{
public:
	bool cueball; 	// white ball
	char id;		// number on ball
	int type;

public:
	BallInfo();
	BallInfo(bool isCueBall, char id, int type);
};

struct Ball : public BallInfo{
public:
	Vec2d pos;
	Vec2d vel; // per second
	double radius;
	Vec2d lastDeltaPosition; // movement at last iteration, useful for collisions

public:
	bool CollidesWith(const Ball &other) const;

	Ball();
	Ball(double x, double y, double radius, char name, bool striped);
};

#endif // __BALL_H__