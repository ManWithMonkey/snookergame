#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include <cstring>
#include <math.h>

const char luminosityString[] = " .-~^*:;!xb(){}[]?XB&%#";

char GetLuminosityCharacter(double luminosity);
double GetLuminosityFromCharacter(char c);

class Window{
private:
    int x, y;
    int width, height;
    char* canvas;
    
public:
    Window(int x, int y, int w, int h);
    ~Window();

    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    const char* GetCanvas() const;

    void PlotPixel(int x, int y, double luminosity);
    void PlotPixelIfBrighter(int x, int y, double luminosity);

    void DrawSphere(double x, double y, double r);

    void Draw();
    void Clear();
};

#endif // __WINDOW_H__