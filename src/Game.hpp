#ifndef __GAME_H__
#define __GAME_H__

#include "GameUtils.hpp"

#include <vector>
#include <chrono>

class Game{
    std::chrono::steady_clock::time_point lastUpdate;
    float deltaTime = 0.f;

    std::vector<Ball> balls;
    std::vector<Line> lines;

public:
    Game();

    void Update();
    void Draw();
};

#endif // __GAME_H__