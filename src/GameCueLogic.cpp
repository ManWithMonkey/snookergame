#include "GameCueLogic.hpp"

GameCueLogic::GameCueLogic(){
}

void GameCueLogic::UpdateCue(double dt){
    UpdateCueStuff(dt);
}

void GameCueLogic::UpdateCueStuff(double dt){

    if(cue.active && (cue.rotationStatus != NO_ROTATION) && !(cue.ballIndex < 0 || cue.ballIndex >= balls.size())){
        Ball* ball = &balls[cue.ballIndex];
        
        double newAngle = cue.angle + rotateCueVel * dt * (cue.rotationStatus == ROTATE_LEFT ? -1.0 : 1.0);
        cue.angle = newAngle;
    }

    if(!cue.active){
        bool isEverythingSlowEnough = true;

        for(Ball& ball : balls){
            if(!ball.active)
                continue;
            double vel = Norm(ball.vel);

            if(vel > minBallVelForCueToActivate){
                isEverythingSlowEnough = false;
                break;
            }
        }
        
        if(isEverythingSlowEnough){
            InitDefaultCue();
        }
    }
}

void GameCueLogic::ReleaseCue(){
    if(!cue.active || cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;

    double strength = cue.releaseMinStregth + (cue.releaseMaxStregth - cue.distanceFromBallMin) * cue.pullScale;

    Ball* ball = &balls[cue.ballIndex];
    vec2 unit = MakeVector(cue.angle, -1.0);

    ball->vel = unit * strength;

    cue.active = false;
}
