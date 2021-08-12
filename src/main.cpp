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
}

void Up(){
}

void Down(){
}

void Left(){
}

void Right(){
}

int main(){
    Init();
    ResizeEvent();
    Reset();
    // AddCallback('r', Reset);
    // AddCallback('a', Left);
    // AddCallback('d', Right);
    // AddCallback('w', Up);
    // AddCallback('s', Down);
    AddResizeCallback(ResizeEvent);

    while(!ShouldQuit()){
        UpdateNCurses();
        BlankScreen();

        game.Update();
        game.Draw();

        Refresh();
        usleep(1000);
    }

    Quit();

    return 0;
}
