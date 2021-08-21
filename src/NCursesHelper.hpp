#ifndef __NCURSESHELPER_H__
#define __NCURSESHELPER_H__

#include <curses.h>

#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
#include <assert.h>

// ncurses error checking macro
#define CHECK(expr) do {assert((expr) != ERR);} while (false)

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

const int MAX_COLOR = 1000; // why 1000 ???

struct Terminal
{
	static bool SHOULD_QUIT;

	// max width and height are just for saving memory, can be arbitrarily large
	static const int MAX_WIDTH = 300;
	static const int MAX_HEIGHT = 200;

	// width and height updated from HandleScreenResizing on runtime
	static int WIDTH;
	static int HEIGHT;

	static int SCREEN_DATA[MAX_WIDTH * MAX_HEIGHT];
	static int COLOR_DATA[MAX_WIDTH * MAX_HEIGHT];
	// wrapper function for getting index of pixel on screen
	static int Index(int x, int y);

	static void EnableColor();
	static void DisableColor();

	// e.g. cp == BLACK_ON_WHITE, instead of COLOR_PAIR(BLACK_ON_WHITE)
	static void SetDrawColor(int cp);
	static void PlotPixel(int x, int y, char c);
};

void Init();
void Quit();
void Refresh();

bool ShouldQuit();
int GetWidth();
int GetHeight();

void HandleEvents(); // formerly UpdateNCurses
void HandleScreenResizing();
void HandleInput();

#endif // __NCURSESHELPER_H__