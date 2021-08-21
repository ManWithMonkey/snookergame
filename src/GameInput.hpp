#ifndef __GAMEINPUT_H__
#define __GAMEINPUT_H__

#include "GameLogic.hpp"
#include "GameCueLogic.hpp"

class GameInput : public virtual GameLogic, public virtual GameCueLogic{
public:
    GameInput();

    void ResizeEvent();
    void LeftEvent();
    void RightEvent();
    void UpEvent();
    void DownEvent();
    void SpaceEvent();
};

#endif // __GAMEINPUT_H__