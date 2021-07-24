#include "Console.h"

void Console::ClearConsoleFully() 
{
	system("clear");
}

void Console::ClearConsole() 
{
	// std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::flush;
	// system("clear");
	// Clear();
	std::cout << "\e[3J\e[1;1H";
}

void Console::InitBackground() 
{
	for(int y=0; y<height; y++)
		for(int x=0; x<width; x++)
			if (x == 4 || x == width - 5 || y == 3 || y == height - 3 || x == 0 || y == 0 || x == width - 1 || y == height - 1)
				background[y * width + x] = '#';
			else
				background[y * width + x] = ((y + x) % 2 ? '/' : '\\');
}

Console::Console(int w, int h) :
	width(w), height(h)
{
	background 	= new char[width * height];
	canvas 		= new char[width * height];

	InitBackground();

	ClearConsoleFully();
}

Console::~Console() 
{
	for(Window* window : windows){
		if(window){
			delete window;
		}
	}
	windows.clear();

	if(background){
		delete[] background;
		background = nullptr;
	}
	if(canvas){
		delete[] canvas;
		canvas = nullptr;
	}

	ClearConsoleFully();
}

void Console::AddWindow(Window* window) 
{
	windows.push_back(window);
}

void Console::Render() 
{
	// clear canvas with background
	std::memcpy(canvas, background, width * height * sizeof(char));
	// for(int ix = 0; ix < width; ix ++){
	// 	for(int iy = 0; iy < height; iy ++){
	// 	}
	// }

	// apply windows canvas to console canvas
	for(Window* window : windows){
		const char* window_canvas = window->GetCanvas();
		int x = window->GetX();
		int y = window->GetY();
		int w = window->GetWidth();
		int h = window->GetHeight();

		int sx = std::max(0, x), ex = std::min(width,  x + w);
		int sy = std::max(0, y), ey = std::min(height, y + h);

		for(int ix = sx; ix < ex; ix ++){
			for(int iy = sy; iy < ey; iy ++){
				canvas[iy * width + ix] = window_canvas[(iy - sy) * w + (ix - sx)];
			}
		}
	}

	// clear screen
	ClearConsole();

	// draw canvas
	for(int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			std::cout << canvas[y * width + x];
		}
		std::cout << '\n';
	}
}
