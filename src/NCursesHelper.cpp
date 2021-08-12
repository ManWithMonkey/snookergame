#include "NCursesHelper.hpp"

// static variables
const int   Terminal::MAX_WIDTH;
const int   Terminal::MAX_HEIGHT;
int         Terminal::WIDTH = 0;
int         Terminal::HEIGHT = 0;
bool        Terminal::SHOULD_QUIT = false;
int         Terminal::SCREEN_DATA[MAX_WIDTH * MAX_HEIGHT];

int Terminal::Index(int x, int y){
    return (y * MAX_WIDTH + x);
}

void Terminal::PlotPixel(int x, int y, char c){
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;

    SCREEN_DATA[Index(x, y)] = c;
}

/*
	The curs_set routine sets the cursor state to invisible, normal, or
	very visible for visibility equal to 0, 1, or 2 respectively.
*/
enum cursor_visibility_t {
	CURS_INVIS  = 0,
	CURS_NORMAL = 1,
	CURS_BRIGHT = 2
};

void Init() {
	initscr();
	keypad(stdscr, true);
	noecho();
	curs_set(CURS_INVIS);
	if (nodelay(stdscr, true) == ERR) {
		std::cout << "unable to enable nodelay mode\n";
	}
	HandleScreenResizing();
}

void Quit() {
	endwin();
}

void HandleEvents() {
	HandleInput();
}

void HandleScreenResizing() {
	int nw, nh;
	getmaxyx(stdscr, nh, nw);

	Terminal::WIDTH = nw;
	Terminal::HEIGHT = nh;
}

void HandleInput() {
	int c;

	while ((c = getch()) != ERR) {
		switch (c) {
		case KEY_RESIZE:
			HandleScreenResizing();
			Refresh();
			break;
		case 'q':
		case 'Q':
			Terminal::SHOULD_QUIT = true;
			break;
		}
	}
}

void Refresh() {
	int w = std::min(Terminal::WIDTH,   Terminal::MAX_WIDTH);
	int h = std::min(Terminal::HEIGHT,  Terminal::MAX_HEIGHT);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			char c = Terminal::SCREEN_DATA[Terminal::Index(x, y)];
			mvaddch(y, x, c);
		}
	}

	refresh();
}

bool ShouldQuit() {
	return Terminal::SHOULD_QUIT;
}

int GetWidth() {
	return Terminal::WIDTH;
}

int GetHeight() {
	return Terminal::HEIGHT;
}
