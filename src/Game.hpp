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

    void ResizeEvent();
    void Reset();

private:
    void HandleCollisions();

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
    float map_width     = 20.f;
    float map_height    = 10.f;
    float x_factor = 0.f;
    float y_factor = 0.f;

    void DrawBall(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);

};

#endif // __GAME_H__