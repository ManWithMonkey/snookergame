#include "GameUtils.hpp"

void DrawBall(const Ball& ball){
    DrawSolidBall(ball.pos.x, ball.pos.y, ball.r, '#');
}

void DrawLine(const Line& line){
    float x1 = line.a.x;
    float y1 = line.a.y;
    float x2 = line.b.x;
    float y2 = line.b.y;

    DrawLine(x1, y1, x2, y2, '%');
}
