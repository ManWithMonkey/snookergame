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

static Game game;

void ResizeEvent(){
    game.ResizeEvent();
}

void Reset(){
    game.Reset();

    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };
}

void Space(){
    // p2 = p1;
}

void Up(){
    // p1.y -= 1.f;
}

void Down(){
    // p1.y += 1.f;
}

void Left(){
    // p1.x -= 1.f;
}

void Right(){
    // p1.x += 1.f;
}

void Key1(){
    // p4 = p1;
}

void Key2(){
    // p3 = p1;
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

        game.Update();
        game.Draw();

        Refresh();
        napms(50);
    }

    Quit();

    return 0;
}
