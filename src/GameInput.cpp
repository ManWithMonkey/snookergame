#include "Game.hpp"

void Game::LeftEvent(){
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

void Game::RightEvent(){
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

void Game::UpEvent(){
    if(!cue.active)
        return;
   
    cue.pullScale = std::max(0.0, cue.pullScale - pullCue);
    cue.rotationStatus = NO_ROTATION;
}

void Game::DownEvent(){
    if(!cue.active)
        return;
   
    cue.pullScale = std::min(1.0, cue.pullScale + pullCue);
    cue.rotationStatus = NO_ROTATION;
}

void Game::SpaceEvent(){
    ReleaseCue();
}
