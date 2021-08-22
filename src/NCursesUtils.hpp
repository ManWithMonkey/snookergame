#ifndef __NCURSESUTILS_H__
#define __NCURSESUTILS_H__

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

struct EventCallbackClass{
	virtual void KeyEvent(int key);
	virtual void ResizeEvent();
	virtual void MouseEvent(int x, int y, mmask_t buttonStateBits);
};

struct Color{
	unsigned long colorKey;
	int colorpair_id;
	bool usedInLastRefresh = false;
};

struct TerminalColorModule{
	// seems to work with 20-255
	static const int minColorIndex = 20;
	static const int maxColorIndex = 255;
	static const int colorCacheSize = maxColorIndex - minColorIndex;

	unsigned long GetColorKey(unsigned short r, unsigned short g, unsigned short b);
	void MarkColorAsUsed(unsigned long key);

	int colorsUsedCounter = 0;
	std::vector<Color> colorCache;

	TerminalColorModule();

	void RemoveUnused();
	void RefreshStart();

	// returns -1 if couldnt find or create
	int GetIdOfColorPair(unsigned short r, unsigned short g, unsigned short b);
};

#endif // __NCURSESUTILS_H__