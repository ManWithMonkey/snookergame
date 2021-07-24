#include "Console.h"

Console::Console() 
{
}

Console::Console(int w, int h) {
    width = w;
    height = h;
    console = new char[w * h];
}

void Console::Draw() {
    for(int y = 0; y < height; y ++){
        for(int x = 0; x < width; x ++){
            if(x == 0 || x == width - 1 || y == 0 || y == height - 1)
                console[y * width + x] = '#';
            else
                console[y * width + x] = ' ';
        }
    }
}

void Console::Clear() {
    for(int y = 0; y < height; y ++){
        for(int x = 0; x < width; x ++){
            std::cout << console[y * width + x];
        }
        std::cout << '\n';
    }
}
