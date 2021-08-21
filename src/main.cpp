#include "Game8Ball.hpp"
#include "Input.hpp"

static Game8Ball game;

int main(){
    Terminal::Init();
	Terminal::AddObjectCallback(&game);

	// temporary fix, add GameTemplate::InitScreenSize() or something
	game.ResizeEvent();
	//

    while(!Terminal::ShouldQuit()){
        Terminal::HandleEvents();
        DrawFunctions::PaintBlankScreen(COLOR_PAIR(BLACK_ON_RED));
		
		game.Update();
		game.Draw();

		Terminal::Refresh();
		napms(1);
	}

	Terminal::Quit();

	return 0;
}
