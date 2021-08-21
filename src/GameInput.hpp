#ifndef __GAMEINPUT_H__
#define __GAMEINPUT_H__

#include "GameLogic.hpp"
#include "GameCueLogic.hpp"

class GameInput : public virtual GameLogic, public virtual GameCueLogic{
public:
    GameInput();

    void ResizeEvent();
    void KeyEvent(int key);
    void LeftEvent();
    void RightEvent();
    void UpEvent();
    void DownEvent();
    void SpaceEvent();

protected:
    // child class will handle this, since this class has not Reset() defined
    bool postResetCall = false;
};

#endif // __GAMEINPUT_H__