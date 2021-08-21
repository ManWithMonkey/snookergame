#include "GameInput.hpp"

GameInput::GameInput(){
    ResizeEvent();
}

void GameInput::ResizeEvent(){
    fromMapToScreenScalarX = (double)Terminal::GetWidth()   / map_width;
    fromMapToScreenScalarY = (double)Terminal::GetHeight()  / map_height;
}

void GameInput::KeyEvent(int key){
    if(key == KEY_LEFT)
        LeftEvent();
    if(key == KEY_RIGHT)
        RightEvent();
    if(key == KEY_UP)
        UpEvent();
    if(key == KEY_DOWN)
        DownEvent();
    if(key == ' ')
        SpaceEvent();
    if(key == 'r')
        postResetCall = true;
}

void GameInput::MouseEvent(int mx, int my, mmask_t buttonStateBits){
    if(!cue.active)
        return;
    if(cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;
        
    cue.rotationStatus = NO_ROTATION;

    if(buttonStateBits == 2){
        ReleaseCue();
    }

    Ball& ball = balls[cue.ballIndex];

    double x = (double)mx / fromMapToScreenScalarX;
    double y = (double)my / fromMapToScreenScalarY;

    double dx = x - ball.pos.x;
    double dy = y - ball.pos.y;

    double length = std::hypot(dx, dy);
    double newAngle = std::atan2(dy, dx) + M_PI;
    double newPullScale = length / map_width * 2.0;

    cue.angle = newAngle;
    cue.pullScale = std::clamp(newPullScale, 0.0, 1.0);
}

void GameInput::LeftEvent(){
    if(!cue.active)
        return;
    if(cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;

    // if already rotating, stop
    if(cue.rotationStatus == ROTATE_LEFT || cue.rotationStatus == ROTATE_RIGHT)
        cue.rotationStatus = NO_ROTATION;
    else
        cue.rotationStatus = ROTATE_LEFT;
}

void GameInput::RightEvent(){
    if(!cue.active)
        return;
    if(cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;
    
    // if already rotating, stop
    if(cue.rotationStatus == ROTATE_LEFT || cue.rotationStatus == ROTATE_RIGHT)
        cue.rotationStatus = NO_ROTATION;
    else
        cue.rotationStatus = ROTATE_RIGHT;
}

void GameInput::UpEvent(){
    if(!cue.active)
        return;
   
    cue.pullScale = std::max(0.0, cue.pullScale - pullCuePerClick);
    cue.rotationStatus = NO_ROTATION;
}

void GameInput::DownEvent(){
    if(!cue.active)
        return;
   
    cue.pullScale = std::min(1.0, cue.pullScale + pullCuePerClick);
    cue.rotationStatus = NO_ROTATION;
}

void GameInput::SpaceEvent(){
    ReleaseCue();
}
