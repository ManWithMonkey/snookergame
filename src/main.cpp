#include "Game8Ball.hpp"
#include "Input.hpp"

static Game8Ball game;

int main(){
    Input::InitCallbacks();
    Input::InitGameInput(&game);

    Init();

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
