#ifndef __GAMECOLLISIONS_H__
#define __GAMECOLLISIONS_H__

#include "GameData.hpp"

class GameCollisions : public virtual GameData{
protected:
    void HandleCollisionsAndApplyMotion();

protected: // should be private?
    BallBallCollision GetClosestBallBallCollision(Ball& ball);
    BallLineCollision GetClosestBallLineCollision(Ball& ball);
    BallBallCollision GetClosestBallBallCollision();
    BallLineCollision GetClosestBallLineCollision();

    void HandleClipping();

protected:
    const int MAX_COLLISIONS_ITERS = 100;

    const double MIRROR_LOSS    = 0.99;
    const double DPOS_LOSS      = 0.99;
    const double VEL_LOSS       = 0.99;

    const double deacceleration = 0.99;
    const double wallBounce     = 1.0;

    const double holeDeacceleration = 3.0;
    const double holeSuckMinVel     = 0.2;
};

#endif // __GAMECOLLISIONS_H__