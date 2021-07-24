#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <iostream>

class Console{
private:
    int realWidth, realHeight;
    int width, height;
    char* console;

public:
    Console();
    Console(int w, int h);

    void PlotPixel(int x, int y, double luminosity);

    void Draw();
    void Clear();
};

#endif // __CONSOLE_H__