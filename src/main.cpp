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

void Randomize(){
    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };

    game.Reset();
}

void SetOther(){
}

void MoveL(){
}

void D(){
}

void W(){
}

void S(){
}

int main(){
    Init();

    Randomize();
    AddCallback('r', Randomize);
    // AddCallback('a', MoveL);
    // AddCallback('d', MoveR);
    // AddCallback('w', MoveU);
    // AddCallback('s', MoveD);
    // AddCallback(' ', SetOther);

    while(!ShouldQuit()){
        UpdateNCurses();
        BlankScreen();

        game.Update();
        game.Draw();

        Refresh();
        usleep(20000);
    }

    Quit();

    return 0;
}
