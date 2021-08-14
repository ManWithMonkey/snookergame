#ifndef __GAME_H__
#define __GAME_H__

#include "GameUtils.hpp"

#include <vector>
#include <chrono>
#include <limits>

struct BallBallCollisionInfo{
    float scalarOfDeltatime;
    vec2 pos1, pos2;
    vec2 dpos1, dpos2;
    vec2 vel1, vel2;
};

struct BallBallCollision : public BallBallCollisionInfo{
    int i = 0, j = 0;
    bool nocollision = true;
};

struct BallLineCollisionInfo{
    float scalarOfDeltatime;
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

    void UpdatePositionsAndHandleCollisions();
    void HandleClippingIfNecessary();
    void UpdateHoleStuff();

    void InitDefaultBallFormation();

private:
    std::chrono::steady_clock::time_point lastUpdate;
    float deltaTime = 0.f;

    // todo: seperate collision lines and draw lines
    std::vector<Line> lines;
    std::vector<Ball> balls;
    std::vector<Hole> holes;

    const int MAX_COLLISIONS_ITERS = 4;
    const float MIRROR_LOSS = 0.01f;
    const float DPOS_LOSS   = 0.01f;
    const float VEL_LOSS    = 0.99f;

private:
    // normalize game so its uneffected by screensize
    const float map_width     = 2.f;
    const float map_height    = 1.f;
    float x_factor = 0.f;
    float y_factor = 0.f;

    const float table_left   = 0.0f;
    const float table_top    = 0.0f;
    const float table_right  = map_width - table_left;
    const float table_bottom = map_height - table_top;

    const float table_w = (table_right - table_left);
    const float table_h = (table_bottom - table_top);

    const float buffer_x = 0.10f;
    const float buffer_y = 0.05f;

    const float holer = 0.12f;
    const float ballr = 0.04f;

    const float l = table_left      + buffer_x + holer;
    const float t = table_top       + buffer_y + holer;
    const float r = table_right     - buffer_x - holer;
    const float b = table_bottom    - buffer_y - holer;

    const float deacceleration = 0.95f;

    void DrawBall(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);
    void DrawHole(const Hole& hole, char c);

};

#endif // __GAME_H__