#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <iostream>

class Console{
private:
    int width, height;
    char* console;

public:
    Console();
    Console(int w, int h);

    void Draw();
    void Clear();
};

#endif // __CONSOLE_H__