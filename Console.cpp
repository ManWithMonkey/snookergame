#include "Console.h"

Console::Console()
{
	ConsoleFullClear();
}

Console::Console(int w, int h)
{
	width = w;
	height = h;
    realWidth = w + 2; // add 2 for the border
	realHeight = h + 2;
	console = new char[realWidth * realHeight];
	ConsoleFullClear();
}

void Console::PlotPixel(int x, int y, double luminosity)
{
	if(x < 0 || y < 0 || x >= width || y >= height)
		return;

	char color = ' ';

	// luminosity is between 0.0-1.0
	if(luminosity >= 0 && luminosity < 1){ 
		const char *options = " .-:;&%#";
		int selected = luminosity * sizeof(options);
		color = options[selected];
	}

	console[(y + 1) * realWidth + (x + 1)] = color;
}

void Console::Draw()
{
	for (int y = 0; y < realHeight; y++)
	{
		for (int x = 0; x < realWidth; x++)
		{
			std::cout << console[y * realWidth + x];
		}
		std::cout << '\n';
	}
}

void Console::ConsoleFullClear() 
{
	// std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::flush;
	system("clear");
	Clear();
}

void Console::Clear()
{
	std::cout << "\e[3J\e[1;1H";

	for (int y = 0; y < realHeight; y++)
	{
		for (int x = 0; x < realWidth; x++)
		{
			if (x == 0 || x == realWidth - 1 || y == 0 || y == realHeight - 1)
				console[y * realWidth + x] = '#';
			else
				console[y * realWidth + x] = ' ';
		}
	}
}
