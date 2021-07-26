#include "Ball.h"

Ball::Ball(double x, double y, double radius, char id, int type, int color, int color2) :
	pos(Vec2d(x, y)), vel(Vec2d(0, 0)), radius(radius), lastPositionChange(Vec2d(0, 0)), BallInfo(false, id, type, color, color2)
{
}

bool Ball::CollidesWith(const Ball &other) const
{
	return (other.pos - pos).norm() <= other.radius + radius;
}

Ball::Ball()
{
}

BallInfo::BallInfo() 
{
	this->cueball = false;
	this->id = 0;
	this->type = 0;
}

BallInfo::BallInfo(bool isCueBall, char id, int type, int color, int color2)
{
	this->cueball = isCueBall;
	this->id = id;
	this->type = type;
	this->color = color;
	this->color2 = color2;
}
