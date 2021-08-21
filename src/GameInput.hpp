#ifndef __GAMEINPUT_H__
#define __GAMEINPUT_H__

#include "GameLogic.hpp"
#include "GameCueLogic.hpp"

// debug
#include <sstream>

class GameInput : public virtual GameLogic, public virtual GameCueLogic, public virtual NCursesCallbackClass{
public:
    GameInput();

    virtual void ResizeEvent() override;
    virtual void KeyEvent(int key) override;
    virtual void MouseEvent(int x, int y, mmask_t buttonStateBits) override;

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