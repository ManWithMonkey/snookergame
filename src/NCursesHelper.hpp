#ifndef __NCURSESHELPER_H__
#define __NCURSESHELPER_H__

#include "NCursesUtils.hpp"

const int NCURSES_MAX_COLOR = 1000;

namespace Terminal
{
	bool ShouldQuit();
	int GetWidth();
	int GetHeight();

	// wrapper function for getting index of pixel on screen
	int Index(int x, int y);

	void EnableColor();
	void DisableColor();

	void EnableMouse();
	void DisableMouse();

	int GetMouseX();
	int GetMouseY();

	// e.g. cp == BLACK_ON_WHITE, instead of COLOR_PAIR(BLACK_ON_WHITE)
	void SetDrawColor(unsigned short r, unsigned short b, unsigned short g);
	void SetDrawColor(Color color);
	void PlotPixel(int x, int y, char c);

	void Init();
	void Quit();
	void Refresh();	

	void AddCallback(EventCallbackClass* obj);

	void HandleEvents();
	void HandleResizeEvent();
	void HandleMouseEvent();
	void HandleKeyboardEvent(int key);

	// max width and height are just for saving memory, can be arbitrarily large
	inline const int MAX_WIDTH = 300;
	inline const int MAX_HEIGHT = 200;

	// screen pixel and color data
	inline int SCREEN_DATA[MAX_WIDTH * MAX_HEIGHT];
	inline int COLORID_DATA[MAX_WIDTH * MAX_HEIGHT];
};

#endif // __NCURSESHELPER_H__