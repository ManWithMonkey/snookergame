#include <unistd.h>
#include "Game.hpp"

// #include "demos.hpp"

int main(){
    Init();

    Game game;

    while(!ShouldQuit()){
        UpdateNCurses();
        DefaultScreen();

        // DrawLineTest();
        // BouncingBallTest();
        // CanvasTest();

        game.Update();
        game.Draw();

        Refresh();
        usleep(1000);
    }

    Quit();

    return 0;
}
