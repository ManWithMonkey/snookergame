#ifndef __COLORCANVAS_H__
#define __COLORCANVAS_H__

#include "ColorPixel.h"

class ColorCanvas{
public:
    int width = 0, height = 0;
    COLOR* colorData;
    PIXEL* pixelData;
    // ColorPixel* data = nullptr;

public:
    ColorCanvas(int w, int h);
    ~ColorCanvas();

    void ClearPixel(PIXEL change_to);
    void ClearColor(COLOR change_to);

    void ChangePixel(int x, int y, char pixel);
    void ChangeColor(int x, int y, const char* color);
    void ChangePixelAndColor(int x, int y, char pixel, const char* color);

    // maybe unnecessary? 
    char pixelAt(int x, int y);
    const char* colorAt(int x, int y);
};

#endif // __COLORCANVAS_H__