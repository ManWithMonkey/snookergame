#include <chrono>
#include <thread> // std::this_thread::sleep_for
#include <ncurses.h>

#define CONSOLE_WIDTH (140)
#define CONSOLE_HEIGHT (52)

#define GAME_X (20)
#define GAME_Y (6)
#define GAME_W (100)
#define GAME_H (40)

#define ZOOM_X (12 + 80)
#define ZOOM_Y (4)
#define ZOOM_W (40)
#define ZOOM_H (30)

#include "Console.h"
#include "Game.h"
#include "Window.h"

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main()
{
    initscr();
    noecho();
	
	Console console(CONSOLE_WIDTH, CONSOLE_HEIGHT, " ---~:~--- [ BILLIARDS ] ---~:~--- ");
	
	ConsolePanel *gameWindow = new ConsolePanel(GAME_X, GAME_Y, GAME_W, GAME_H);
	console.AddWindow(gameWindow);

	ConsolePanel* zoomWindow = nullptr;
	// ConsolePanel* zoomWindow = new ConsolePanel(ZOOM_X, ZOOM_Y, ZOOM_W, ZOOM_H);
	// console.AddWindow(zoomWindow);

	Game game(GAME_W, GAME_H, gameWindow, zoomWindow);

	using clock = std::chrono::high_resolution_clock;
	auto time_start = clock::now();

	while (true) {
		auto now = clock::now();
		auto dt = now - time_start;
		time_start = now;

		double dt_seconds = (double)std::chrono::duration_cast<std::chrono::microseconds>(dt).count() / 1E+6;
		
		if(kbhit()){
			auto c = getch();

			std::cout << "this: " << c << "\n";
		}

		game.Update(dt_seconds);
		game.UpdateScreen();

		// console.Render();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}