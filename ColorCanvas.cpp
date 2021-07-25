#include "ColorCanvas.h"

ColorCanvas::ColorCanvas(int w, int h):
    width(w), height(h)
{
    pixelData = new PIXEL[w * h];
    colorData = new COLOR[w * h];
}

ColorCanvas::~ColorCanvas() 
{
    if(pixelData){ delete[] pixelData; pixelData = nullptr; }
    if(colorData){ delete[] colorData; colorData = nullptr; }
    width = 0;
    height = 0;
}

void ColorCanvas::ClearPixel(PIXEL change_to) 
{
    for(int y = 0; y < height; y ++ )
        for(int x = 0; x < width; x ++ ){
            pixelData[y * width + x] = change_to;
        }
}

void ColorCanvas::ClearColor(COLOR change_to) 
{
    for(int y = 0; y < height; y ++ )
        for(int x = 0; x < width; x ++ ){
            colorData[y * width + x] = change_to;
        }
}

void ColorCanvas::ChangePixel(int x, int y, char pixel) 
{
    if(x < 0 || y < 0 || x >= width || y >= height)
        ;
    else
        pixelData[y * width + x] = pixel;
}

void ColorCanvas::ChangeColor(int x, int y, const char* color) 
{
    if(x < 0 || y < 0 || x >= width || y >= height)
        ;
    else
        colorData[y * width + x] = color;
}

void ColorCanvas::ChangePixelAndColor(int x, int y, char pixel, const char* color) 
{
    if(x < 0 || y < 0 || x >= width || y >= height)
        ;
    else{
        pixelData[y * width + x] = pixel;
        colorData[y * width + x] = color;
    }
}

char ColorCanvas::pixelAt(int x, int y) {
    if(x < 0 || y < 0 || x >= width || y >= height)
        return ' ';
    else
        return pixelData[y * width + x];
}

const char* ColorCanvas::colorAt(int x, int y) {
    if(x < 0 || y < 0 || x >= width || y >= height)
        return nullptr;
    else
        return colorData[y * width + x];
}
