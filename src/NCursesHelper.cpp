#include "NCursesHelper.hpp"

/* 
       The curs_set routine sets the cursor state to invisible, normal, or
       very visible for visibility equal to 0, 1, or 2 respectively.
*/
enum cursor_visibility
{
	CURS_INVIS  = 0,
	CURS_NORMAL = 1,
	CURS_BRIGHT = 2,
};

void Init()
{
	initscr();
	keypad(stdscr, true);
	noecho();
	curs_set(CURS_INVIS);
	if (nodelay(stdscr, true) == ERR) {
		std::cout << "unable to enable nodelay mode\n";
	}
}

void Quit()
{
	endwin();
}

void UpdateNCurses()
{
	HandleInput();
}

void HandleScreenResizing()
{
	int nw, nh;
	getmaxyx(stdscr, nh, nw);

	// this check is probably redundant since the function gets called when a resize event occurred
	if (nw != CURRENT_SCREEN_WIDTH || nh != CURRENT_SCREEN_HEIGHT)
	{
		// std::cout << "Window resized to: " << nw << "x" << nh << "\n";
		// wresize(stdscr, nh, nw);

		CURRENT_SCREEN_WIDTH = nw;
		CURRENT_SCREEN_HEIGHT = nh;
	}
}

void HandleInput()
{
	int c;

	while ((c = getch()) != ERR)
	{
		switch (c)
		{
		case KEY_RESIZE:
			HandleScreenResizing();
			Refresh();
			break;
		case 'q':
		case 'Q':
			SHOULD_QUIT = true;
			break;
		}
	}
}

void Refresh()
{
	int w = std::min(CURRENT_SCREEN_WIDTH, SCREEN_WIDTH_MAX);
	int h = std::min(CURRENT_SCREEN_HEIGHT, SCREEN_HEIGHT_MAX);

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			move(y, x);
			char c = SCREEN_DATA[y * SCREEN_WIDTH_MAX + x];
			addch(c);
		}
	}

	refresh();
}

bool ShouldQuit()
{
	return SHOULD_QUIT;
}

int GetWidth()
{
	return CURRENT_SCREEN_WIDTH;
}

int GetHeight()
{
	return CURRENT_SCREEN_HEIGHT;
}

int GetMaxWidth()
{
	return SCREEN_WIDTH_MAX;
}

int GetMaxHeight()
{
	return SCREEN_HEIGHT_MAX;
}

void PlotPixel(int x, int y, char c)
{
	if (x < 0 || y < 0 || x >= GetWidth() || y >= GetHeight())
	{
		return;
	}

	SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = c;
}

void DefaultScreen()
{
	int w = std::min(CURRENT_SCREEN_WIDTH, SCREEN_WIDTH_MAX);
	int h = std::min(CURRENT_SCREEN_HEIGHT, SCREEN_HEIGHT_MAX);

	char b = '#';
	char a[] = {
	    '.', ' ', ' '};

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (x == 0 || y == 0 || x == CURRENT_SCREEN_WIDTH - 1 || y == CURRENT_SCREEN_HEIGHT - 1)
				SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = b;
			else
				SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = a[(y + x) % sizeof(a)];
		}
	}
}