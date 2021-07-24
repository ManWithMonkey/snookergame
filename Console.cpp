#include "Console.h"

char GetLuminosityCharacter(double luminosity) 
{
	// luminosity is between 0.0-1.0
	if(luminosity >= 0 && luminosity <= 1){
		if(luminosity == 1) luminosity -= 0.0001; // crude fix
		return luminosityString[(int)(luminosity * (sizeof(luminosityString) - 1))];
	}
	else
		return luminosityString[0];
}

double GetLuminosityFromCharacter(char c) 
{
	const char* index = strchr(luminosityString, c);
	if(index){
		return (double)(index - luminosityString) / (double)(sizeof(luminosityString) - 1);
	}
	else{
		return 0.f; // not found
	}
}

Console::Console()
{
	ConsoleClear();
}

Console::Console(int w, int h)
{
	width = w;
	height = h;
    realWidth = w + 2; // add 2 for the border
	realHeight = h + 2;
	console = new char[realWidth * realHeight];
	ConsoleClear();
}

void Console::PlotPixel(int x, int y, double luminosity)
{
	if(x < 0 || y < 0 || x >= width || y >= height)
		return;

	console[(y + 1) * realWidth + (x + 1)] = GetLuminosityCharacter(luminosity);
}

void Console::PlotPixelIfBrighter(int x, int y, double luminosity) 
{
	if(x < 0 || y < 0 || x >= width || y >= height)
		return;

	if(luminosity > GetLuminosityFromCharacter(console[(y + 1) * realWidth + (x + 1)]))
		console[(y + 1) * realWidth + (x + 1)] = GetLuminosityCharacter(luminosity);
}

void Console::Draw()
{
	for(int y = 0; y < realHeight; y++){
		for (int x = 0; x < realWidth; x++){
			std::cout << console[y * realWidth + x];
		}
		std::cout << '\n';
	}
}

void Console::ConsoleClear() 
{
	// std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::flush;
	system("clear");
	// Clear();
}

void Console::Clear()
{
	std::cout << "\e[3J\e[1;1H";

	for (int y = 0; y < realHeight; y++){
		for (int x = 0; x < realWidth; x++){
			
			if (x == 0 || x == realWidth - 1 || y == 0 || y == realHeight - 1)
				console[y * realWidth + x] = '#';
			else
				console[y * realWidth + x] = ' ';
		}
	}
}

Console::~Console() {
	ConsoleClear();
}
