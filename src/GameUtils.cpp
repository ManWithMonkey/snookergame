#include "GameUtils.hpp"

bool Hole::IsClose(const Ball& ball){
    return Norm(ball.pos - pos) <= holeRadius;
}

bool Hole::IsInside(const Ball& ball){
    return Norm(ball.pos - pos) <= insideRadius - ball.r;
}
