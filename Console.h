#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Window.h"
#include <algorithm> // std::memcpy
#include <string>
#include <vector>

class Console
{
public:
	int width, height;
	char *background;
	char *canvas;
	std::string title;

	std::vector<Window *> windows;

	void ClearConsoleFully();
	void ClearConsole();

	void InitBackground();
	void DrawBorderAroundWindowOnBackground(Window *window);

public:
	Console(int w, int h, std::string title = "");
	~Console();

	void AddWindow(Window *window);
	void Render();
};

#endif // __CONSOLE_H__