#include "Game.hpp"

void Game::LeftEvent(){
    if(!cue.active)
        return;
    if(cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;

    Ball* ball = &balls[cue.ballIndex];
    vec2 dpos = cue.targetPosition - ball->pos;
    
    double angle = atan2(dpos.y, dpos.x);
    double newAngle = angle - rotateCueVel;

    cue.targetPosition = ball->pos + MakeVector(newAngle, Norm(dpos));
}

void Game::RightEvent(){
    if(!cue.active)
        return;
    if(cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;

    Ball* ball = &balls[cue.ballIndex];
    vec2 dpos = cue.targetPosition - ball->pos;
    
    double angle = atan2(dpos.y, dpos.x);
    double newAngle = angle + rotateCueVel;

    cue.targetPosition = ball->pos + MakeVector(newAngle, Norm(dpos));
}

void Game::UpEvent(){
    if(!cue.active)
        return;
   
    cue.pullScale = std::max(0.0, cue.pullScale - pullCue);
}

void Game::DownEvent(){
    if(!cue.active)
        return;
   
    cue.pullScale = std::min(1.0, cue.pullScale + pullCue);
}

void Game::SpaceEvent(){
    ReleaseCue();
}
