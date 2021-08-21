#ifndef __GAMECUELOGIC_H__
#define __GAMECUELOGIC_H__

#include "GameData.hpp"
#include "GameDraw.hpp"

class GameCueLogic : public virtual GameData, public virtual GameDraw{
protected:
    virtual void InitDefaultCue() = 0;

    void UpdateCue(double dt);
    void ReleaseCue();

protected:
    // rename everything
    const double rotateCueVel               = 0.5;
    const double pullCuePerClick            = 0.1;
    const double minBallVelForCueToActivate = 0.04;

    const double cueStartAngle = M_PI;
    const double cueDistanceFromBallMinMultipleOfBallr = 0.5;
    const double cueDistanceFromBallMaxMultipleOfBallr = 7.5;
    const double cueLengthOnScreen = 0.2 * map_width;
    const double cueStartPullScale = 0.0;
    const double cueReleaseMinStregth = 0.1;
    const double cueReleaseMaxStregth = 10.0;

};

#endif // __GAMECUELOGIC_H__