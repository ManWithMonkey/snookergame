#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <algorithm> // std::memcpy
#include <string>
#include <vector>

#include "TerminalHelper.h"
#include "Window.h"
#include "ANSI-color-codes.h"

const COLOR DEFAULT_DRAW_COLOR = BLU;
const PIXEL BORDER_PIXEL = '#';
const COLOR BORDER_COLOR = YEL;
const COLOR BACKGROUND_COLOR = BLU;
const COLOR TITLE_COLOR = WHT;

class Console{
public:
	int width, height;

	int title_y, title_x_start, title_x_end;
	std::string title;

	PIXEL* pixelData;
	COLOR* colorData;

	std::vector<ConsolePanel*> windows;

	void UpdateCanvas();

public:
	Console(int w, int h, std::string title = "");
	~Console();

	void AddWindow(ConsolePanel *window);
	void Render();
};

#endif // __CONSOLE_H__