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
		return 0.f; // not found
	}
}

Window::~Window()
{
	if (canvas) {
		delete[] canvas;
		canvas = nullptr;
	}
}

void Window::MakeBellSound()
{
	// system("echo -ne \007");
	system("echo \007");
}

int Window::GetX() const
{
	return x;
}

int Window::GetY() const
{
	return y;
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

const char *Window::GetCanvas() const
{
	return canvas;
}

void Window::PlotPixel(int x, int y, char pixel)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return;

	canvas[y * width + x] = pixel;
}

void Window::PlotPixelIfBrighter(int x, int y, double luminosity)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return;

	if (luminosity > GetLuminosityFromCharacter(canvas[y * width + x]))
		canvas[y * width + x] = GetLuminosityCharacter(luminosity);
}

void Window::PlotPixel(Vec2d p, char pixel)
{
	PlotPixel(p.x, p.y, pixel);
}

void Window::PlotPixelIfBrighter(Vec2d p, double luminosity)
{
	PlotPixelIfBrighter(p.x, p.y, luminosity);
}

void Window::DrawSphere(double x, double y, double r)
{
	double cx = (int)(x);
	double cy = (int)(y);

	for (double ix = -r; ix <= r; ix += 1.0) {
		for (double iy = -r; iy <= r; iy += 1.0) {

			double distance = std::hypot(cx + ix - x, cy + iy - y);
			double luminosity = 1.0 - distance / r;

			PlotPixelIfBrighter(cx + ix, cy + iy, luminosity);
		}
	}
}

void Window::DrawHollowSphere(double x, double y, double r_outer, double r_inner)
{
	double cx = (int)(x);
	double cy = (int)(y);

	double max_distance = r_outer - r_inner;
	double mid_radius = (r_outer + r_inner) / 2.0;

	for (double ix = -r_outer; ix <= r_outer; ix += 1.0) {
		for (double iy = -r_outer; iy <= r_outer; iy += 1.0) {

			double distance = std::hypot(cx + ix - x, cy + iy - y);
			double luminosity = 0.25 - 0.75 * std::abs(distance - mid_radius) / max_distance;

			PlotPixelIfBrighter(cx + ix, cy + iy, luminosity);
		}
	}
}

void Window::DrawSphere(Vec2d p, double r)
{
	DrawSphere(p.x, p.y, r);
}

void Window::DrawHollowSphere(Vec2d p, double r_outer, double r_inner)
{
	DrawHollowSphere(p.x, p.y, r_outer, r_inner);
}

void Window::DrawCircleOutline(double x, double y, double r)
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

		PlotPixel(cx, cy, c);
	}
}

void Window::DrawCircleOutline(Vec2d p, double r)
{
	DrawCircleOutline(p.x, p.y, r);
}

void Window::Draw()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			std::cout << canvas[y * width + x];
		}
		std::cout << '\n';
	}
}

Window::Window(int x, int y, int w, int h) : x(x), y(y), width(w), height(h)
{
	canvas = new char[width * height];

	Clear();
}

void Window::Clear()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			canvas[y * width + x] = ' ';
		}
	}
}
