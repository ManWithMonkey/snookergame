#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <iostream>
#include <cstring>

const char luminosityString[] = " .-~^*:;!xb(){}[]?XB&%#";

char GetLuminosityCharacter(double luminosity);
double GetLuminosityFromCharacter(char c);

class Console{
private:
    int realWidth, realHeight;
    int width, height;
    char* console;

public:
    Console();
    Console(int w, int h);
    ~Console();
    
    void ConsoleClear();

    void PlotPixel(int x, int y, double luminosity);
    void PlotPixelIfBrighter(int x, int y, double luminosity);

    void Draw();
    void Clear();
};

#endif // __CONSOLE_H__