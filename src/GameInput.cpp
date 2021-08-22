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
    if(IsCueStickValid(cuestick)){
        cuestick.rotationStatus = NO_ROTATION;

        if(buttonStateBits == 2){
            ReleaseCue();
        }

        Ball& ball = balls[cuestick.ballIndex];

        double x = (double)mx / fromMapToScreenScalarX;
        double y = (double)my / fromMapToScreenScalarY;

        double dx = x - ball.pos.x;
        double dy = y - ball.pos.y;

        double length = std::hypot(dx, dy);
        double newAngle = std::atan2(dy, dx) + M_PI;
        double newPullScale = length / map_width * 2.0;

        cuestick.angle = newAngle;
        cuestick.pullScale = std::clamp(newPullScale, 0.0, 1.0);
    }

    if(IsCueHandValid(cuehand)){
        cuehand.pos.x = (double)mx / fromMapToScreenScalarX;
        cuehand.pos.y = (double)my / fromMapToScreenScalarY;
        
        if(buttonStateBits == 2){
            ReleaseHand();
        }
    }
}

void GameInput::LeftEvent(){
    if(!IsCueStickValid(cuestick))
        return;

    // if already rotating, stop
    if(cuestick.rotationStatus == ROTATE_LEFT || cuestick.rotationStatus == ROTATE_RIGHT)
        cuestick.rotationStatus = NO_ROTATION;
    else
        cuestick.rotationStatus = ROTATE_LEFT;
}

void GameInput::RightEvent(){
    if(!IsCueStickValid(cuestick))
        return;
    
    // if already rotating, stop
    if(cuestick.rotationStatus == ROTATE_LEFT || cuestick.rotationStatus == ROTATE_RIGHT)
        cuestick.rotationStatus = NO_ROTATION;
    else
        cuestick.rotationStatus = ROTATE_RIGHT;
}

void GameInput::UpEvent(){
    if(!IsCueStickValid(cuestick))
        return;
   
    cuestick.pullScale = std::max(0.0, cuestick.pullScale - pullCuePerClick);
    cuestick.rotationStatus = NO_ROTATION;
}

void GameInput::DownEvent(){
    if(!IsCueStickValid(cuestick))
        return;
   
    cuestick.pullScale = std::min(1.0, cuestick.pullScale + pullCuePerClick);
    cuestick.rotationStatus = NO_ROTATION;
}

void GameInput::SpaceEvent(){
    ReleaseCue();
}
