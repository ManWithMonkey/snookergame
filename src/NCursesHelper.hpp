#ifndef __NCURSESHELPER_H__
#define __NCURSESHELPER_H__

#include "NCursesUtils.hpp"

// todo: should be namespace Terminal instead of struct, static variables should not exist or should be in a better structure or be in cpp file instead, everything in this file should be under one namespace

const int MAX_COLOR = 1000;

namespace Terminal
{
	bool ShouldQuit();
	int GetWidth();
	int GetHeight();

	// wrapper function for getting index of pixel on screen
	int Index(int x, int y);

	void EnableColor();
	void DisableColor();

	// e.g. cp == BLACK_ON_WHITE, instead of COLOR_PAIR(BLACK_ON_WHITE)
	void SetDrawColor(int cp);
	void PlotPixel(int x, int y, char c);

	void Init();
	void Quit();
	void Refresh();	

	void AddCallback(int c, void(*func)());
	void AddKeyCallback(void(*func)(int));
	void AddResizeCallback(void(*func)());

	// template<typename T>
	// void AddObjectCallBack(ObjectCallbackFunction<T> callback);

	void HandleEvents();
	void HandleInput();
	void HandleScreenResizing();

	// max width and height are just for saving memory, can be arbitrarily large
	inline const int MAX_WIDTH = 300;
	inline const int MAX_HEIGHT = 200;

	// screen pixel and color data
	inline int SCREEN_DATA[MAX_WIDTH * MAX_HEIGHT];
	inline int COLOR_DATA[MAX_WIDTH * MAX_HEIGHT];
};


#endif // __NCURSESHELPER_H__