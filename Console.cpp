#include "Console.h"
#include "ANSI-color-codes.h"

void Console::UpdateCanvas() 
{
	// draw background
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1){
				pixelData[y * width + x] = BORDER_PIXEL;
				colorData[y * width + x] = BORDER_COLOR;
			}
			else{
				pixelData[y * width + x] = ((y + x) % 2 ? '.' : ' ');
				colorData[y * width + x] = BACKGROUND_COLOR;
			}
		}
	}

	// draw title
	{
		for (int y = 0; y < height; y++){
			for (int x = 0; x < width; x++){
				if (y == title_y && x >= title_x_start && x <= title_x_end) {
					pixelData[y * width + x] = title[x - title_x_start];
					colorData[y * width + x] = TITLE_COLOR;
				}
			}
		}
	}
	
	// draw window content
	for (ConsolePanel *window : windows) {
		int x = window->x;
		int y = window->y;
		int w = window->width;
		int h = window->height;

		int sx = std::max(0, x), ex = std::min(width - 1, x + w - 1);
		int sy = std::max(0, y), ey = std::min(height - 1, y + h - 1);

		for (int ix = sx; ix <= ex; ix++) {
			for (int iy = sy; iy <= ey; iy++) {
				
				char pixel = window->canvas.pixelAt(ix - sx, iy - sy);
				const char* color = window->canvas.colorAt(ix - sx, iy - sy);

				pixelData[(iy) * width + ix] = pixel;
				colorData[(iy) * width + ix] = (color == nullptr ? DEFAULT_DRAW_COLOR : color);
			}
		}

		// draw border, will cause seg err!!!!
		for (int y = sy - 1; y <= ey + 1; y++) {
			pixelData[y * width + sx - 1] = BORDER_PIXEL;
			pixelData[y * width + ex + 1] = BORDER_PIXEL;
			colorData[y * width + sx - 1] = BORDER_COLOR;
			colorData[y * width + ex + 1] = BORDER_COLOR;
		}
		for (int x = sx - 1; x <= ex + 1; x++) {
			pixelData[(sy - 1) * width + x] = BORDER_PIXEL;
			pixelData[(ey + 1) * width + x] = BORDER_PIXEL;
			colorData[(sy - 1) * width + x] = BORDER_COLOR;
			colorData[(ey + 1) * width + x] = BORDER_COLOR;
		}
	}
}

Console::Console(int w, int h, std::string title) :
	width(w), height(h), title(title),
	// center title in the middle of the top of the screen
	title_y(1),
	title_x_start((width - title.size()) / 2),
	title_x_end(title_x_start + (int)title.size() - 1)
{
	Terminal::ClearHard();
	
	pixelData = new PIXEL[width * height];
	colorData = new COLOR[width * height];
}

Console::~Console()
{
	Terminal::ClearHard();

	for (ConsolePanel *window : windows) {
		if (window) {
			delete window;
		}
	}
	windows.clear();

	if (pixelData) {
		delete[] pixelData;
		pixelData = nullptr;
	}
	if (colorData) {
		delete[] colorData;
		colorData = nullptr;
	}
}

void Console::AddWindow(ConsolePanel *window)
{
	windows.push_back(window);
}

void Console::Render()
{
	// update canvas
	UpdateCanvas();

	// clear screen
	Terminal::ClearSoft();

	// draw canvas
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			std::cout << colorData[y * width + x] << pixelData[y * width + x];
		}
		std::cout << '\n';
	}
}
