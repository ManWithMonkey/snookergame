#ifndef __GAMETEMPLATE_H__
#define __GAMETEMPLATE_H__

#include "GameLogic.hpp"
#include "GameCueLogic.hpp"
#include "GameInput.hpp"
#include "GameDraw.hpp"

class GameTemplate : public virtual GameLogic, public virtual GameCueLogic, public virtual GameInput, public virtual GameDraw{
public:
    GameTemplate();

    void Update();
    void Reset();

    // no need to overwrite, but you can
    virtual void InitializeGame();

    // override these when inheriting
    virtual void InitDefaultMapFormation();
    virtual void InitDefaultCue();
    virtual void InitDefaultBallFormation();
    
protected:
    std::chrono::steady_clock::time_point lastUpdate;
    double deltaTime = 0.;
};

#endif // __GAMETEMPLATE_H__