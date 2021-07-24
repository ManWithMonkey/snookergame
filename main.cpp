#include "Game.h"

#include <chrono>
#include <thread> // std::this_thread::sleep_for

// #define SCREEN_WIDTH 60
// #define SCREEN_HEIGHT 40

int main(){
    Game game;
    
    using clock = std::chrono::high_resolution_clock;
    auto time_start = clock::now();

    while(true){
        auto now = clock::now();
        auto dt = now - time_start;
        time_start = now;

        double dt_seconds = (double)std::chrono::duration_cast<std::chrono::microseconds>(dt).count() / 1E+6;
        // std::cout << dt_seconds << "\n";

        game.Update(dt_seconds);
        game.Draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}