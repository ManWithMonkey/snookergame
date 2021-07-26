#include "NCursesWrapper.h"

void InitNCurses() 
{
    initscr();
    nodelay(stdscr,true);
    keypad(stdscr,true);
    noecho();
    curs_set(0);
    start_color();
    nl();
    
    int colors[8] = {
        COLOR_BLACK,
        COLOR_RED,
        COLOR_GREEN,
        COLOR_YELLOW,
        COLOR_BLUE,
        COLOR_MAGENTA,
        COLOR_CYAN,
        COLOR_WHITE
    };

    for(int bg=0; bg<8; bg++)
    	for(int fg=0; fg<8; fg++)
        	init_pair(FG_BG(fg, bg), colors[fg], colors[bg]);
}

void QuitNCurses() 
{
    nodelay(stdscr,false);
    getch();
    endwin();
}

void Clear(char pixel, int color) 
{
	int w, h;
	getmaxyx(stdscr, h, w);

    for(int x=0; x<w; x++){
        for(int y=0; y<h; y++){
            move(y, x);
    		attrset(color);
            addch(pixel);
        }
    }
}

void SetPixel(int x, int y, char pixel) 
{
	int w, h;
	getmaxyx(stdscr, h, w);
	
    if(x < 0 || y < 0 || x >= w || y >= h)
        return;

    move(y, x);
    addch(pixel);
}
    
void SetPixel(int x, int y, char pixel, int c) 
{
	int w, h;
	getmaxyx(stdscr, h, w);

    if(x < 0 || y < 0 || x >= w || y >= h)
        return;

    chtype color = COLOR_PAIR(c);
    // color |= A_BOLD;

    move(y, x);
    attrset(color);
    addch(pixel);
}

void Render() 
{
    refresh();
}

void MakeBellSound() 
{
	system("echo \007");
}

void DrawCircleOutline(double x, double y, double radius, int color) 
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
	double deltaAngle = 0.999 * two_PI / (double)pointsize;

	int charIndex = 0;

	for (double angle = 0.0; angle < two_PI; angle += deltaAngle) {
		// skip characters that dont describe current angle
		while (angles[charIndex] < angle)
			charIndex++;

		char c = chars[(charIndex + 4) % sizeof(chars)];

		double cx = x + radius * std::cos(angle);
		double cy = y + radius * std::sin(angle);

		SetPixel(cx, cy, c, color);
	}
}

void DrawLine(double x1, double y1, double x2, double y2, char pixel, int color) 
{
	if(y2 < y1){
		std::swap(y1, y2);
		std::swap(x1, x2);
	}

	double dx = x2 - x1;
	double dy = y2 - y1;

	if(dx == 0){
		for(int y = y1; y < y2; y++){
			SetPixel(x1, y, pixel, color);
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
				SetPixel(x, y, pixel, color);
			}
		}
		else{
			for(int x = x2; x < x1; x++){
				double y = k * x + b;
				SetPixel(x, y, pixel, color);
			}
		}
	}
	else{
		for(int y = y1; y < y2; y++){
			double x = (y - b) / k;
            SetPixel(x, y, pixel, color);
		}
	}
}

void DrawSphere(double x, double y, double r, char pixel, int color) 
{
	double cx = x;
	double cy = y;

	for (double ix = -r; ix <= r; ix += 1.0) {
		for (double iy = -r; iy <= r; iy += 1.0) {

			double distance = std::hypot(cx + ix - x, cy + iy - y);
			double luminosity = 1.0 - distance / r;

			int sx = cx + ix;
			int sy = cy + iy;

			if(distance <= r + 0.3){
				SetPixel(sx, sy, pixel, color);
			}
		}
	}
}
