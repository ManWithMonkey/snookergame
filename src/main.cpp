#include "Game.hpp"
#include "Input.hpp"

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

int main(){
    Input::InitCallbacks();
    Input::InitGameInput(&game);

    Init();

    while(!ShouldQuit()){
        UpdateNCurses();
        BlankScreen();

        game.Update();
        game.Draw();

        Refresh();
        napms(5);
    }

    Quit();

    return 0;
}
