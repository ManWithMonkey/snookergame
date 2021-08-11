#ifndef __GAME_H__
#define __GAME_H__

#include "GameUtils.hpp"

#include <vector>
#include <chrono>

class Game{
public:
    Game();

    void Update();
    void Draw();

    void Reset();

private:
    std::chrono::steady_clock::time_point lastUpdate;
    float deltaTime = 0.f;

    Line top, bottom, left, right;
    std::vector<Line> lines;
    std::vector<Ball> balls;

    const int MAX_COLLISIONS_ITERS = 5;
    const float MIRROR_LOSS = 0.95f;
    const float DPOS_LOSS   = 0.5f;
    const float VEL_LOSS    = 0.99f;

private:
    void DrawBall(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);

};

#endif // __GAME_H__