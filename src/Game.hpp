#ifndef __GAME_H__
#define __GAME_H__

#include "GameUtils.hpp"

#include <vector>
#include <chrono>
#include <limits>

struct BallCollisionInfo{
    float scalarOfDeltatime;
    vec2 pos1, pos2;
    vec2 dpos1, dpos2;
    vec2 vel1, vel2;
};

struct BallBallCollision : public BallCollisionInfo{
    int i = 0, j = 0;
    bool nocollision = true;
};

struct BallLineCollision{
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

    void HandleCollisions();
    void HandleClippingIfNecessary();

private:
    std::chrono::steady_clock::time_point lastUpdate;
    float deltaTime = 0.f;

    // seperate collision lines and draw lines
    std::vector<Line> lines;
    std::vector<Ball> balls;

    const int MAX_COLLISIONS_ITERS = 5;
    const float MIRROR_LOSS = 0.99f;
    const float DPOS_LOSS   = 0.5f;
    const float VEL_LOSS    = 0.95f;

private:
    // normalize game so its uneffected by screensize
    float map_width     = 2.f;
    float map_height    = 1.f;
    float x_factor = 0.f;
    float y_factor = 0.f;

    void DrawBall(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);

};

#endif // __GAME_H__