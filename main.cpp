#include <chrono>
#include <thread> // std::this_thread::sleep_for

#define GAME_X (0)
#define GAME_Y (0)
#define GAME_W (100)
#define GAME_H (50)

#include "Game.h"
#include "NCursesWrapper.h"

int main()
{
    Game game(GAME_X, GAME_Y, GAME_W, GAME_H);

	using clock = std::chrono::high_resolution_clock;
	auto time_start = clock::now();

	while (true) {
		auto now = clock::now();
		auto dt = now - time_start;
		time_start = now;

		double dt_seconds = (double)std::chrono::duration_cast<std::chrono::microseconds>(dt).count() / 1E+6;

		game.Update(dt_seconds);
		game.UpdateScreen();
		// console.Render();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}