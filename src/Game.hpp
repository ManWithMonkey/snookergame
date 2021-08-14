#ifndef __GAME_H__
#define __GAME_H__

#include "GameUtils.hpp"

#include <vector>
#include <chrono>
#include <limits>

struct BallBallCollisionInfo{
    double scalarOfDeltatime;
    vec2 pos1, pos2;
    vec2 dpos1, dpos2;
    vec2 vel1, vel2;
};

struct BallBallCollision : public BallBallCollisionInfo{
    int i = 0, j = 0;
    bool nocollision = true;
};

struct BallLineCollisionInfo{
    double scalarOfDeltatime;
    vec2 pos;
    vec2 dpos;
    vec2 vel;
};

struct BallLineCollision : public BallLineCollisionInfo{
    int b = 0, l = 0;
    bool nocollision = true;
};

class Game{
public:
    Game();

    void Update();
    void Draw();

    void ResizeEvent();
    void Reset();

private:
    BallBallCollision GetClosestBallBallCollision();
    BallLineCollision GetClosestBallLineCollision();

    void UpdatePositions();
    void HandleClipping();
    void UpdateBallHoleInteraction();

    void InitDefaultBallFormation();

private:
    void DrawBall(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);
    void DrawHole(const Hole& hole, char c);

private:
    std::chrono::steady_clock::time_point lastUpdate;
    double deltaTime = 0.f;

    // todo: seperate collision lines and draw lines
    std::vector<Line> lines;
    std::vector<Ball> balls;
    std::vector<Hole> holes;

    const int MAX_COLLISIONS_ITERS = 100;

    const double MIRROR_LOSS    = 0.99f;
    const double DPOS_LOSS      = 0.99f;
    const double VEL_LOSS       = 0.99f;

    const double deacceleration = 0.95f;

    // normalize game so its uneffected by screensize
    const double map_width      = 2.f;
    const double map_height     = 1.f;

    const double buffer_x       = 0.02f;
    const double buffer_y       = 0.01f;
    const double table_left     = 0.1f;
    const double table_top      = 0.05f;
    const double table_right    = 2.f - 0.1f;
    const double table_bottom   = 1.f - 0.05f;
    const double holer          = 0.08f;
    const double ballr          = 0.04f;

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