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

    void Randomize();

private:
    std::chrono::steady_clock::time_point lastUpdate;
    float deltaTime = 0.f;

    Line top, bottom, left, right;
    std::vector<Line> lines;
    std::vector<Ball> balls;

private:
    void DrawBall(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);

};

#endif // __GAME_H__