#include "Cue.h"

void Cue::Apply(Ball& ball) const
{
    if(target == ball.pos)
        return;
        
    Vec2d delta = target - ball.pos;

    double length = delta.norm();
    double angle = delta.angle();

    ball.vel += strength * Vec2d(
        cos(angle),
        sin(angle)
    );
}

Cue::Cue() :
    target(0, 0), inAction(false)
{
    
}
