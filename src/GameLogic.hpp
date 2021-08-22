#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

#include "GameData.hpp"
#include "GameDraw.hpp"
#include "GameCollisions.hpp"

#include <vector>
#include <chrono>
#include <limits>

class GameLogic : public virtual GameData, public virtual GameDraw, public virtual GameCollisions{
public:
    GameLogic();

    void Update(double dt);

protected:
    void ApplyDeacceleration(double dt);
    void CalculateMotions(double dt);
    void UpdateBallHoleInteraction(double dt);

protected:
    const int MAX_COLLISIONS_ITERS = 100;

    const double MIRROR_LOSS    = 0.99;
    const double DPOS_LOSS      = 0.99;
    const double VEL_LOSS       = 0.99;

    const double deacceleration = 0.95;
    const double wallBounce     = 1.0;

    const double instantStopBelowVelocity = 0.075;

    const double holeDeacceleration = 3.0;
    const double holeSuckMinVel     = 0.2;

};

#endif // __GAMELOGIC_H__