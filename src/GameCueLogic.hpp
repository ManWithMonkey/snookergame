#ifndef __GAMECUELOGIC_H__
#define __GAMECUELOGIC_H__

#include "GameData.hpp"
#include "GameDraw.hpp"

class GameCueLogic : public virtual GameData, public virtual GameDraw{
public:
    GameCueLogic();

    void UpdateCue(double dt);

    virtual void InitDefaultCue() = 0;

protected:
    void UpdateCueStuff(double dt);
    void ReleaseCue();

protected:
    // i am good at naming things
    const double rotateCueVel               = 0.5;
    const double pullCuePerClick            = 0.1;
    const double minBallVelForCueToActivate = 0.04;

    const double cueStartAngle = M_PI;
    const double cueDistanceFromBallMinMultipleOfBallr = 0.5;
    const double cueDistanceFromBallMaxMultipleOfBallr = 5.0;
    const double cueLengthOnScreen = 0.2 * map_width;
    const double cueStartPullScale = 0.0;
    const double cueReleaseMinStregth = 0.1;
    const double cueReleaseMaxStregth = 10.0;

};

#endif // __GAMECUELOGIC_H__