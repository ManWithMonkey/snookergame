#include <unistd.h>
#include "Game.hpp"
#include "MathFunctions.hpp"

#include <random>
#include <sstream>

template<typename T>
std::string ToString(const T& rhs){
    std::string result;

    std::stringstream ss;
    ss << rhs;
    result += ss.str();

    return result;
}

static vec2 p1 = {23, 12}, p2 = {30, 30};
static vec2 p3, p4;

void Randomize(){
    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };

    float w = GetWidth();
    float h = GetHeight();

    float x1 = frand() * w;
    float y1 = frand() * h;
    float x2 = frand() * w;
    float y2 = frand() * h;

    p3 = {x1, y1};
    p4 = {x2, y2};
}

void SetOther(){
    p2 = p1;
}

void MoveL(){
    p1.x -= 1.f;
}

void MoveR(){
    p1.x += 1.f;
}

void MoveU(){
    p1.y -= 1.f;
}

void MoveD(){
    p1.y += 1.f;
}

int main(){
    Init();

    Randomize();

    AddCallback('r', Randomize);
    AddCallback('a', MoveL);
    AddCallback('d', MoveR);
    AddCallback('w', MoveU);
    AddCallback('s', MoveD);
    AddCallback(' ', SetOther);

    while(!ShouldQuit()){
        UpdateNCurses();
        BlankScreen();

        DrawFunctions::DrawLine(p3.x, p3.y, p4.x, p4.y, 176);
        DrawFunctions::DrawLine(p1.x, p1.y, p2.x, p2.y, 176);
        DrawFunctions::DrawPoint(p1.x, p1.y, 'X');

        bool collides = LineLineCollision(p1, p2, p3, p4);
        std::string s = (collides ? "collides" : "doesnt collide");
        DrawFunctions::TypeString(0, 0, s);

        Refresh();
        usleep(1000);
    }

    Quit();

    return 0;
}
