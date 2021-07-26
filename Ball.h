#ifndef __BALL_H__
#define __BALL_H__

#include "Vec2d.h"

struct BallInfo{
public:
	bool cueball;
	char id;
	int type;
	int color;
	int color2;

public:
	BallInfo();
	BallInfo(bool isCueBall, char id, int type, int color, int color2);
};

struct Ball : public BallInfo{
public:
	Vec2d pos;
	double radius;

	Vec2d vel;
	Vec2d lastPositionChange;

public:
	bool CollidesWith(const Ball &other) const;

	Ball();
	Ball(double x, double y, double radius, char id, int type, int color, int color2);
};

#endif // __BALL_H__