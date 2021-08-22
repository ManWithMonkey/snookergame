#include "Game8Ball.hpp"

int main(){
    Terminal::Init();
	
	Game8Ball game;
	Terminal::AddCallback(&game);

    while(!Terminal::ShouldQuit()){
        Terminal::HandleEvents();
		
		game.Update();
		game.Draw();

		Terminal::Refresh();
		napms(1);
	}

	Terminal::Quit();

	return 0;
}
