#include "Window.h"

char GetLuminosityCharacter(double luminosity)
{
	// luminosity is between 0.0-1.0
	if (luminosity >= 0 && luminosity <= 1) {
		if (luminosity == 1)
			luminosity -= 0.0001; // crude fix
		return luminosityString[(int)(luminosity * (sizeof(luminosityString) - 1))];
	} else
		return luminosityString[0];
}

double GetLuminosityFromCharacter(char c)
{
	const char *index = strchr(luminosityString, c);
	if (index) {
		return (double)(index - luminosityString) / (double)(sizeof(luminosityString) - 1);
	} else {
		return 0.0; // not found
	}
}

ConsolePanel::~ConsolePanel()
{
}

void ConsolePanel::MakeBellSound()
{
	// system("echo -ne \007");
	system("echo \007");
}

void ConsolePanel::PlotPixel(int x, int y, char pixel, COLOR color)
{
	canvas.ChangePixelAndColor(x, y, pixel, color);
}

bool ConsolePanel::PlotPixelIfBrighter(int x, int y, double luminosity, COLOR color){
	if (x < 0 || y < 0 || x >= width || y >= height)
		return false;

	if (luminosity > GetLuminosityFromCharacter(canvas.pixelAt(x, y))){
		canvas.ChangePixelAndColor(x, y, GetLuminosityCharacter(luminosity), color);
		return true;
	}

	return false;
}

void ConsolePanel::DrawSphere(double x, double y, double r, COLOR color)
{
	double cx = (int)(x);
	double cy = (int)(y);

	for (double ix = -r; ix <= r; ix += 1.0) {
		for (double iy = -r; iy <= r; iy += 1.0) {

			double distance = std::hypot(cx + ix - x, cy + iy - y);
			double luminosity = 1.0 - distance / r;

			int sx = cx + ix;
			int sy = cy + iy;

			if(PlotPixelIfBrighter(sx, sy, luminosity) && color != nullptr){
				canvas.ChangeColor(sx, sy, color);
			}
		}
	}
}

void ConsolePanel::DrawCircleOutline(double x, double y, double r, COLOR color)
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

	int pointsize = two_PI * r;
	double deltaAngle = two_PI / (double)pointsize;

	int charIndex = 0;

	for (double angle = 0.0; angle < two_PI; angle += deltaAngle) {
		// skip characters that dont describe current angle
		while (angles[charIndex] < angle)
			charIndex++;

		char c = chars[(charIndex + 4) % sizeof(chars)];

		double cx = x + r * cos(angle);
		double cy = y + r * sin(angle);

		PlotPixel(cx, cy, c, color);
	}
}

void ConsolePanel::DrawLine(double x1, double y1, double x2, double y2, PIXEL pixel, COLOR color) 
{
	if(y2 < y1){
		std::swap(y1, y2);
		std::swap(x1, x2);
	}

	double dx = x2 - x1;
	double dy = y2 - y1;

	if(dx == 0){
		for(int y = y1; y < y2; y++){
			PlotPixel(x1, y, pixel);
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
				PlotPixel(x, y, pixel, color);
			}
		}
		else{
			for(int x = x2; x < x1; x++){
				double y = k * x + b;
				PlotPixel(x, y, pixel, color);
			}
		}
	}
	else{
		for(int y = y1; y < y2; y++){
			double x = (y - b) / k;
			PlotPixel(x, y, pixel, color);
		}
	}
}

ConsolePanel::ConsolePanel(int x, int y, int w, int h) : x(x), y(y), width(w), height(h), canvas(width, height)
{
	Clear();
}

void ConsolePanel::Clear()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			canvas.ChangePixelAndColor(x, y, ' ', WHT);
		}
	}
}
