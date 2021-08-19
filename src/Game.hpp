#ifndef __GAME_H__
#define __GAME_H__

#include "GameUtils.hpp"

#include <vector>
#include <chrono>
#include <limits>

class Game{
public:
    Game();

    void Update();
    void Draw();

    void Reset();

    void ResizeEvent();
    void LeftEvent();
    void RightEvent();
    void UpEvent();
    void DownEvent();
    void SpaceEvent();

private:
    BallBallCollision GetClosestBallBallCollision(Ball& ball);
    BallLineCollision GetClosestBallLineCollision(Ball& ball);
    BallBallCollision GetClosestBallBallCollision();
    BallLineCollision GetClosestBallLineCollision();

    void UpdatePositions();
    void HandleClipping();
    void UpdateBallHoleInteraction();
    void UpdateCueStuff();
    void ReleaseCue();

    void InitDefaultBallFormation();
    void InitDefaultCue();

private:
    void DrawBall(double x, double y, double r, char c);
    void DrawLine(double x1, double y1, double x2, double y2, char c);

    void DrawBall(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);
    void DrawHole(const Hole& hole, char c);
    void DrawCue(const Cue& cue, char c, char x);
    void DrawCueGhosts(const Cue& cue, char c);

private:
    std::chrono::steady_clock::time_point lastUpdate;
    double deltaTime = 0.;

    // todo: seperate collision lines and draw lines
    std::vector<Line> lines;
    std::vector<Ball> balls;
    std::vector<Hole> holes;
    Cue cue;

    const int MAX_COLLISIONS_ITERS = 100;

    const double MIRROR_LOSS    = 0.99;
    const double DPOS_LOSS      = 0.99;
    const double VEL_LOSS       = 0.99;

    const double deacceleration = 0.99;

    // normalize game so its uneffected by screensize
    const double map_width      = 2.;
    const double map_height     = 1.;

    const double buffer_x       = 0.02;
    const double buffer_y       = 0.01;
    const double table_left     = 0.1;
    const double table_top      = 0.05;
    const double table_right    = 2. - 0.1;
    const double table_bottom   = 1. - 0.05;
    const double ballr          = 0.04;
    const double wallBounce     = 0.99;

    // holes
    const int holePointCount        = 8;
    const double holer              = 0.08;
    const double realholer          = 0.06;
    const double holeInsideRadius   = ballr *  1.2;
    const double holeSuckMinVel     = 0.2;
    const double holeWallBounce     = 0.4;
    const double holeDeacceleration = 3.0;

    // cue
    const double rotateCueVel       = 0.5;
    const double pullCue            = 0.1;
    const double cueActivationVel   = 0.04;

    // for normalization
    double x_factor;
    double y_factor;

    const double table_w = (table_right - table_left);
    const double table_h = (table_bottom - table_top);

    const double l = table_left      + buffer_x + holer;
    const double t = table_top       + buffer_y + holer;
    const double r = table_right     - buffer_x - holer;
    const double b = table_bottom    - buffer_y - holer;

};

#endif // __GAME_H__