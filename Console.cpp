#include "Console.h"

Console::Console() 
{
}

Console::Console(int w, int h) {
    width = w;
    height = h;
    console = new char[(w+2) * (h+2)]; // add 2 for the border
}

void Console::PlotPixel(int x, int y, double luminocity) 
{
    if(x < 0 || y < 0 || x >= width || y >= height)
        return;

    // luminocity is between 0.0-1.0
    if(luminocity < 0 || luminocity > 1)
        return;

    const char* options = " .-:;¤%&#";

    int selected = luminocity * sizeof(options);
    char color = options[selected];

    console[(y+1) * width + (x+1)] = color;
}

void Console::Draw() {
    for(int y = 0; y < height+1; y ++){
        for(int x = 0; x < width+1; x ++){
            std::cout << console[y * width + x];
        }
        std::cout << '\n';
    }
}

void Console::Clear() {
    for(int y = 0; y < height+2; y ++){
        for(int x = 0; x < width+2; x ++){
            if(x == 0 || x == width + 1 || y == 0 || y == height + 1)
                console[y * width + x] = '#';
            else
                console[y * width + x] = ' ';
        }
    }
}
