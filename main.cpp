#include <chrono>
#include <thread> // std::this_thread::sleep_for

#define CONSOLE_WIDTH 90
#define CONSOLE_HEIGHT 40

#define GAME_X 7
#define GAME_Y 5
#define GAME_WIDTH 76
#define GAME_HEIGHT 30

#include "Console.h"
#include "Window.h"
#include "Game.h"

int main(){
    Console console(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    Window* gameWindow = new Window(GAME_X, GAME_Y, GAME_WIDTH, GAME_HEIGHT);
    Game game(gameWindow);
    console.AddWindow(gameWindow);
    
    using clock = std::chrono::high_resolution_clock;
    auto time_start = clock::now();

    while(true){
        auto now = clock::now();
        auto dt = now - time_start;
        time_start = now;

        double dt_seconds = (double)std::chrono::duration_cast<std::chrono::microseconds>(dt).count() / 1E+6;
        // std::cout << dt_seconds << "\n";

        game.Update(dt_seconds);
        game.UpdateScreen();

        console.Render();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}