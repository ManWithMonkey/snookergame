#include "Console.h"

Console::Console()
{
}

Console::Console(int w, int h)
{
	width = w;
	height = h;
	console = new char[(w + 2) * (h + 2)]; // add 2 for the border
}

void Console::PlotPixel(int x, int y, double luminosity)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return;

	// luminosity is between 0.0-1.0
	if (luminosity < 0 || luminosity >= 1)
		return;

	const char *options = " .-:;&%#";

	int selected = luminosity * sizeof(options);
	char color = options[selected];

	console[(y + 1) * width + (x + 1)] = color;
}

void Console::Draw()
{
	for (int y = 0; y < height + 2; y++)
	{
		for (int x = 0; x < width + 2; x++)
		{
			std::cout << console[y * width + x];
		}
		std::cout << '\n';
	}
}

void Console::Clear()
{
	//system("clear");
	std::cout << "\e[3J\e[1;1H";

	for (int y = 0; y < height + 2; y++)
	{
		for (int x = 0; x < width + 2; x++)
		{
			if (x == 0 || x == width + 1 || y == 0 || y == height + 1)
				console[y * width + x] = '#';
			else
				console[y * width + x] = ' ';
		}
	}
}
