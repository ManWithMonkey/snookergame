#include "Game8Ball.hpp"
#include "Input.hpp"

static Game8Ball game;

int main(){
    Input::InitCallbacks();
    Input::InitGameInput(&game);

    Terminal::Init();

    while(!Terminal::ShouldQuit()){
        Terminal::HandleEvents();
        DrawFunctions::PaintBlankScreen();

		game.Update();
		game.Draw();

		Terminal::Refresh();
		napms(1);
	}

	Terminal::Quit();

	return 0;
}
