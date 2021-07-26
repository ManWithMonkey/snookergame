#ifndef __CUE_H__
#define __CUE_H__

#include "Ball.h"

struct Cue{
    Vec2d target;
    bool inAction;
    
    double strength = 5.0;
    const double lengthOnScreen = 0.5;

    Cue();
    
	void Apply(Ball& ball) const;
};

#endif // __CUE_H__