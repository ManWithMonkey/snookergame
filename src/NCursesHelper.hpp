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
#define CHECK(expr) do {assert(expr != ERR);} while (false)

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
	// wrapper function for getting index of pixel on screen
	static int Index(int x, int y);

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