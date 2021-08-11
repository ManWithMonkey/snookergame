#include "Game.hpp"
#include <unistd.h>

int main() {
	Init();

	Game game;

	while (!ShouldQuit()) {
		UpdateNCurses();
		DefaultScreen();

		game.Update();
		game.Draw();

		Refresh();
		usleep(1000);
	}

	Quit();

	return 0;
}
