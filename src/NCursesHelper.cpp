#include "NCursesHelper.h"

void Init(){
    initscr();
    noecho();
    curs_set(0);
}

void Quit(){
    endwin();
}

void UpdateScreenVariables(){
    int nw, nh;
    getmaxyx(stdscr, nh, nw);

    if(nw != CURRENT_SCREEN_WIDTH || nh != CURRENT_SCREEN_HEIGHT){
        // std::cout << "Window resized to: " << nw << "x" << nh << "\n";
        
        wresize(stdscr, nh, nw);

        CURRENT_SCREEN_WIDTH    = nw;
        CURRENT_SCREEN_HEIGHT   = nh;
    }
}

void Refresh() {
    UpdateScreenVariables();

    int w = std::min(CURRENT_SCREEN_WIDTH,  SCREEN_WIDTH_MAX);
    int h = std::min(CURRENT_SCREEN_HEIGHT, SCREEN_HEIGHT_MAX);

    for(int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            move(y, x);
            char c = SCREEN_DATA[y * SCREEN_WIDTH_MAX + x];
            addch(c);
        }
    }

    refresh();
}

void DefaultScreenTest(){
    int w = std::min(CURRENT_SCREEN_WIDTH,  SCREEN_WIDTH_MAX);
    int h = std::min(CURRENT_SCREEN_HEIGHT, SCREEN_HEIGHT_MAX);

    char a[] = {
        ' ', '!', '#'
    };

    for(int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = a[(y + x) % sizeof(a)];
        }
    }
}

void TestPlotScreenResize() {
    int w = std::min(CURRENT_SCREEN_WIDTH,  SCREEN_WIDTH_MAX);
    int h = std::min(CURRENT_SCREEN_HEIGHT, SCREEN_HEIGHT_MAX);

    for(int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            char c = ".-!#"[(CURRENT_SCREEN_WIDTH + CURRENT_SCREEN_HEIGHT) % 4];
            SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = c;
        }
    }
}
