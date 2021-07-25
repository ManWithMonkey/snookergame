#include <chrono>
#include <thread> // std::this_thread::sleep_for

#define CONSOLE_WIDTH (6+80+6+40+12)
#define CONSOLE_HEIGHT 48

#define GAME_X 6
#define GAME_Y 4
#define GAME_WIDTH 86
#define GAME_HEIGHT 40

#define ZOOM_X (6 + 80 + 12)
#define ZOOM_Y 4
#define ZOOM_W 40
#define ZOOM_H 30

#include "Console.h"
#include "Game.h"
#include "Window.h"

int main()
{
	Console console(CONSOLE_WIDTH, CONSOLE_HEIGHT, " ---~:~--- [ BILLIARDS ] ---~:~--- ");
	ConsolePanel *gameWindow = new ConsolePanel(GAME_X, GAME_Y, GAME_WIDTH, GAME_HEIGHT);
	ConsolePanel* zoomWindow = new ConsolePanel(ZOOM_X, ZOOM_Y, ZOOM_W, ZOOM_H);
	Game game(gameWindow, zoomWindow);
	console.AddWindow(gameWindow);
	console.AddWindow(zoomWindow);

	using clock = std::chrono::high_resolution_clock;
	auto time_start = clock::now();

	while (true) {
		auto now = clock::now();
		auto dt = now - time_start;
		time_start = now;

		double dt_seconds = (double)std::chrono::duration_cast<std::chrono::microseconds>(dt).count() / 1E+6;
		// std::cout << dt_seconds << "\n";

		game.Update(dt_seconds);
		game.UpdateScreen();

		console.Render();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}