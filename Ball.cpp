#include "Ball.h"

Ball::Ball(double x, double y, double radius, char name, bool striped) :
	pos(Vec2d(x, y)), vel(Vec2d(0, 0)), radius(radius), lastDeltaPosition(Vec2d(0, 0)), BallInfo(false, name, striped)
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
	this->type = STRIPED;
}

BallInfo::BallInfo(bool isCueBall, char id, int type) 
{
	this->cueball = isCueBall;
	this->id = id;
	this->type = type;
}
