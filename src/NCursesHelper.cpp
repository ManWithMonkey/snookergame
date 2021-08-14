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
enum cursor_visibility {
	CURS_INVIS  = 0,
	CURS_NORMAL = 1,
	CURS_BRIGHT = 2
};

enum default_colors { // first 8 colors (0 - 7) are reserved
	BLACK   = COLOR_BLACK,
	RED     = COLOR_RED,
	GREEN   = COLOR_GREEN,
	YELLOW  = COLOR_YELLOW,
	BLUE    = COLOR_BLUE,
	MAGENTA = COLOR_MAGENTA,
	CYAN    = COLOR_CYAN,
	WHITE   = COLOR_WHITE,
};

enum color_pairs {
	DEFAULT_RESERVED, // color pair 0 is special; it denotes “no color”.
	WHITE_ON_BLACK,
	BLACK_ON_RED,
	BLACK_ON_GREEN,
	BLACK_ON_BLUE,
};


void Init() {

	initscr();

	// colors
	assert(has_colors());
	assert(can_change_color());
	CHECK(start_color());

	// input settings
	CHECK(keypad(stdscr, true));
	CHECK(noecho());
	CHECK(nodelay(stdscr, true));

	// cursor
	CHECK(curs_set(CURS_INVIS));

	// screen size
	HandleScreenResizing();

	// color pairs
	// syntax : init_pair (color_id, foreground, background)
	init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(BLACK_ON_RED,   COLOR_BLACK, COLOR_RED);
	init_pair(BLACK_ON_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair(BLACK_ON_BLUE,  COLOR_BLACK, COLOR_BLUE);
	attr_on(COLOR_PAIR(BLACK_ON_BLUE), NULL);
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
