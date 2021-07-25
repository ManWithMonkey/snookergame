#include "NCursesWrapper.h"

void InitNCurses(int w, int h) 
{
    initscr();
    nodelay(stdscr,true);
    keypad(stdscr,true);
    noecho();
    curs_set(0);
    // getmaxyx(stdscr,w,h);

    CONSOLE_WIDTH = w;
    CONSOLE_HEIGHT = h;
}

void QuitNCurses() 
{
    nodelay(stdscr,false);
    getch();
    endwin();
}

void Clear(char pixel) 
{
    for(int x=0; x<CONSOLE_WIDTH; x++){
        for(int y=0; y<CONSOLE_HEIGHT; y++){
            move(x, y);
            addch(pixel);
        }
    }
}

void SetPixel(int x, int y, char pixel) 
{
    if(x < 0 || y < 0 || x >= CONSOLE_WIDTH || y >= CONSOLE_HEIGHT)
        return;

    move(y, x);
    addch(pixel);
}

void Render() 
{
    refresh();
}

void DrawCircleOutline(double x, double y, double radius) 
{
	/*
		   ----\
	     /		\
	    (		 )
	     \       /
		  \----/
	*/

	double two_PI = 2.0 * 3.14159;

	double angles[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	const char chars[] = {'-', '~', '\\', '|', ')', '|', '/', '~', '-', '~', '\\', '|', '(', '|', '/', '~'};
	double dangle = two_PI / (double)(sizeof(chars));

	// Initialize angles
	for (size_t i = 0; i < sizeof(chars); i++) {
		angles[i] = (double)i * dangle;
	}

	int pointsize = two_PI * radius;
	double deltaAngle = two_PI / (double)pointsize;

	int charIndex = 0;

	for (double angle = 0.0; angle < two_PI; angle += deltaAngle) {
		// skip characters that dont describe current angle
		while (angles[charIndex] < angle)
			charIndex++;

		char c = chars[(charIndex + 4) % sizeof(chars)];

		double cx = x + radius * std::cos(angle);
		double cy = y + radius * std::sin(angle);

		SetPixel(cx, cy, c);
	}
}

void DrawLine(double x1, double y1, double x2, double y2, char pixel) 
{
	if(y2 < y1){
		std::swap(y1, y2);
		std::swap(x1, x2);
	}

	double dx = x2 - x1;
	double dy = y2 - y1;

	if(dx == 0){
		for(int y = y1; y < y2; y++){
			SetPixel(x1, y, pixel);
		}
		return;
	}

	double stepx = (dx > 0 ? 1.0 : -1.0);

	// y = kx + b
	double k = dy / dx;
	double b = y1 - x1 * k;

	// x = (y - b) / k

	if(std::abs(dx) >= std::abs(dy)){
		if(dx > 0){
			for(int x = x1; x < x2; x++){
				double y = k * x + b;
				SetPixel(x, y, pixel);
			}
		}
		else{
			for(int x = x2; x < x1; x++){
				double y = k * x + b;
				SetPixel(x, y, pixel);
			}
		}
	}
	else{
		for(int y = y1; y < y2; y++){
			double x = (y - b) / k;
            SetPixel(x, y, pixel);
		}
	}
}
