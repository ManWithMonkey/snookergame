#ifndef __CUE_H__
#define __CUE_H__

#include "Ball.h"

struct Cue{
	double x, y;
	double angle;
	double strength;
    bool beingDragged;

    double lengthOnScreen = 8.0;

    double oscillationAngle = 0.0; // for game logic when figuring out how much being dragged

    Cue();

	void Apply(Ball& ball) const;
};

#endif // __CUE_H__