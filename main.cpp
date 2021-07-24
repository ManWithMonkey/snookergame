#include "Game.h"

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 40

int main(){
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

    double dt = 0;

    while(true){
        game.Update(dt);
        game.Draw();

        break;
    }
    return 0;
}