#include "GameCueLogic.hpp"

bool GameCueLogic::IsValidBallDropArea(vec2 pos){
    // return false if collides with anything
    
    return true;
}

bool GameCueLogic::IsCueStickValid(const CueStick& cue) const{
    if(!cue.active || cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return false;
    else
        return true;
}

bool GameCueLogic::IsCueHandValid(const CueHand& hand) const{
    if(!hand.active || hand.ballIndex < 0 || hand.ballIndex >= balls.size())
        return false;
    else
        return true;
}

void GameCueLogic::UpdateCue(double dt){
    if(cuestick.active && (cuestick.rotationStatus != NO_ROTATION) && !(cuestick.ballIndex < 0 || cuestick.ballIndex >= balls.size())){
        Ball* ball = &balls[cuestick.ballIndex];
        
        double newAngle = cuestick.angle + rotateCueVel * dt * (cuestick.rotationStatus == ROTATE_LEFT ? -1.0 : 1.0);
        cuestick.angle = newAngle;
    }

    if(!cuestick.active && !cuehand.active){
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

    if(cuehand.active){
        // keyboard stuff here?
    }
}

void GameCueLogic::ReleaseCue(){
    if(!cuestick.active || cuestick.ballIndex < 0 || cuestick.ballIndex >= balls.size())
        return;

    double strength = cuestick.releaseMinStregth + (cuestick.releaseMaxStregth - cuestick.distanceFromBallMin) * cuestick.pullScale;

    Ball* ball = &balls[cuestick.ballIndex];
    vec2 unit = MakeVector(cuestick.angle, -1.0);

    ball->vel = unit * strength;

    cuestick.active = false;
}

void GameCueLogic::ReleaseHand(){
    if(!cuehand.active || cuestick.ballIndex < 0 || cuestick.ballIndex >= balls.size() || !IsValidBallDropArea(cuehand.pos))
        return;

    Ball* ball = &balls[cuehand.ballIndex];

    ball->pos = cuehand.pos;
    ball->vel = {0, 0};
    ball->dpos = {0, 0};
    ball->active = true;
    cuehand.active = false;

    // activate stick after putting down ball
    cuestick.active = true;
}
