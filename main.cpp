#include <chrono>
#include <thread> // std::this_thread::sleep_for

#include "Game.h"
#include "NCursesWrapper.h"

int main()
{
	InitNCurses();
    Game game;

	using clock = std::chrono::high_resolution_clock;
	auto time_start = clock::now();

	while (true) {
		auto now = clock::now();
		auto dt = now - time_start;
		time_start = now;

		double dt_seconds = (double)std::chrono::duration_cast<std::chrono::microseconds>(dt).count() / 1E+6;

		int c = getch();
		while(c != ERR){
			game.KeyPressed(c);
			c = getch();
		}

		// get terminal width and height
		int w, h;
    	getmaxyx(stdscr, h, w);

		game.Update(dt_seconds);

		Clear(' ', 0);
		game.Draw(w, h);

		// attrset(COLOR_PAIR(FG_BG(COLOR_RED, COLOR_WHITE)));
		// mvprintw(1, 1, "%d, %d", w, h);

		Render();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	QuitNCurses();

	return 0;
}