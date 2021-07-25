#include <chrono>
#include <thread> // std::this_thread::sleep_for

#define CONSOLE_WIDTH (130)
#define CONSOLE_HEIGHT (50)

#define GAME_X (5)
#define GAME_Y (3)
#define GAME_W (120)
#define GAME_H (44)

#define ZOOM_X (12 + 80)
#define ZOOM_Y (4)
#define ZOOM_W (40)
#define ZOOM_H (30)

#include "Console.h"
#include "Game.h"
#include "Window.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

int kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}


char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

int main()
{
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
			char c = getch();
			// std::cout << "this: " << c << "\n";
			game.KeyPressed(c);
		}

		game.Update(dt_seconds);
		game.UpdateScreen();
		console.Render();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}