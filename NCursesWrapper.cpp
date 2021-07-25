#include "NCursesWrapper.h"

void InitNCurses(int w, int h) 
{
    initscr();
    nodelay(stdscr,true);
    keypad(stdscr,true);
    noecho();
    curs_set(0);
    getmaxyx(stdscr,w,h);

    CONSOLE_WIDTH = w;
    CONSOLE_HEIGHT = h;
}

void QuitNCurses() 
{
    nodelay(stdscr,false);
    getch();
    endwin();
}

void Clear(char pixel) 
{
    for(int x=0; x<CONSOLE_WIDTH; x++){
        for(int y=0; y<CONSOLE_HEIGHT; y++){
            move(x, y);
            addch(pixel);
        }
    }
}



void SetPixel(int x, int y, char pixel) 
{
    if(x < 0 || y < 0 || x >= CONSOLE_WIDTH || y >= CONSOLE_HEIGHT)
        return;

    move(x, y);
    addch(pixel);
}

void Render() 
{
    refresh();
}
