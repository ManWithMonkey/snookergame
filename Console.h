#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Window.h"
#include <vector>
#include <algorithm> // std::memcpy

class Console{
public:
    int width, height;
    char* background;
    char* canvas;

    std::vector<Window*> windows;

    void ClearConsoleFully();
    void ClearConsole();

    void InitBackground();

public:
    Console(int w, int h);
    ~Console();

    void AddWindow(Window* window);
    void Render();
};

#endif // __CONSOLE_H__