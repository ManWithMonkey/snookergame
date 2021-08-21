#include "Game.hpp"
#include "MathFunctions.hpp"

#include <random>

static Game game;

void ResizeEvent(){
    game.ResizeEvent();
}

void Reset(){
    game.Reset();
}

int main(){
    Init();
    ResizeEvent();
    Reset();

    while(!ShouldQuit()){
        HandleEvents();
        DrawFunctions::PaintBlankScreen();

		game.Update();
		game.Draw();

		Refresh();
		napms(1);
	}

	Quit();

	return 0;
}
