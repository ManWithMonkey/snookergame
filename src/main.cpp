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

// static Game game;

void ResizeEvent(){
    // game.ResizeEvent();
}

static vec2 p1 = {40, 30}, p2 = {20, 20};
static vec2 p3, p4;

static float r1 = 5.f;
static float r2 = 5.f;

void Reset(){
    // game.Reset();

    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };

    r2 = 1.f + 9.f * frand();
    p3.x = frand() * GetWidth();
    p3.y = frand() * GetHeight();
    // p4.x = frand() * GetWidth();
    // p4.y = frand() * GetHeight();
    p4 = p3;
}

void Space(){
    p2 = p1;
}

void Up(){
    p1.y -= 1.f;
}

void Down(){
    p1.y += 1.f;
}

void Left(){
    p1.x -= 1.f;
}

void Right(){
    p1.x += 1.f;
}

void Key1(){
    p4 = p1;
}

void Key2(){
    p3 = p1;
}

int main(){
    Init();
    ResizeEvent();
    Reset();
    AddCallback('r', Reset);
    AddCallback(' ', Space);
    AddCallback('a', Left);
    AddCallback('d', Right);
    AddCallback('w', Up);
    AddCallback('s', Down);
    AddCallback('1', Key1);
    AddCallback('2', Key2);
    AddResizeCallback(ResizeEvent);

    while(!ShouldQuit()){
        UpdateNCurses();
        BlankScreen();

        // game.Update();
        // game.Draw();

        // vec2 u1 = UnitVector(p1 - p2);
        // vec2 u2 = UnitVector(p3 - p4);
        // vec2 dp1 = u1 * 250.f;
        // vec2 dp2 = u2 * 250.f;
        vec2 dp1 = p1 - p2;
        vec2 dp2 = p3 - p4;
        vec2 end1 = p2 + dp1;
        vec2 end2 = p4 + dp2;

        bool collides = MovingCirclesCollide(p2, dp1, r1, p4, dp2, r2);
        float collisionScalar = GetCollisionPointMovementScalarNewton(p2, dp1, r1, p4, dp2, r2);
        vec2 collisionPointCenter1 = p2 + dp1 * collisionScalar;
        vec2 collisionPointCenter2 = p4 + dp2 * collisionScalar;

        DrawFunctions::DrawSolidBall(p2.x, p2.y, r1, '1');
        DrawFunctions::DrawSolidBall(p4.x, p4.y, r2, '2');
        
        //collision ghost
        if(collides){
            DrawFunctions::DrawSolidBall(collisionPointCenter1.x, collisionPointCenter1.y, r1, '.');
            DrawFunctions::DrawSolidBall(collisionPointCenter2.x, collisionPointCenter2.y, r2, '.');
        }

        DrawFunctions::DrawLine(p2.x, p2.y, end1.x, end1.y, '-');
        DrawFunctions::DrawLine(p4.x, p4.y, end2.x, end2.y, '-');
        DrawFunctions::DrawPoint(p1.x, p1.y, '#');
        DrawFunctions::DrawPoint(p3.x, p3.y, '#');

        Refresh();
        usleep(1000);
    }

    Quit();

    return 0;
}
