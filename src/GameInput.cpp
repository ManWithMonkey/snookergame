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
