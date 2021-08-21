#ifndef __GAME8BALL_H__
#define __GAME8BALL_H__

#include "GameTemplate.hpp"

class Game8Ball final : public virtual GameTemplate{
public:
    Game8Ball();

private:
    virtual void InitDefaultMapFormation() override;
    virtual void InitDefaultBallFormation() override;
    virtual void InitDefaultCue() override;

private:
    const double buffer_x       = 0.02;
    const double buffer_y       = 0.01;
    const double table_left     = 0.1;
    const double table_top      = 0.05;
    const double table_right    = 2. - 0.1;
    const double table_bottom   = 1. - 0.05;
    const double ballr          = 0.04;

    // holes
    const int holePointCount        = 8;
    const double holer              = 0.08;
    const double realholer          = 0.06;
    const double holeInsideRadius   = ballr *  1.2;
    const double holeWallBounce     = 0.4;

    const double table_w = (table_right - table_left);
    const double table_h = (table_bottom - table_top);

    const double l = table_left      + buffer_x + holer;
    const double t = table_top       + buffer_y + holer;
    const double r = table_right     - buffer_x - holer;
    const double b = table_bottom    - buffer_y - holer;

};

#endif // __GAME8BALL_H__