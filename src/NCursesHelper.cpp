#include "NCursesHelper.hpp"

void Init(){
    keypad(initscr(), true);
    noecho();
    curs_set(0);
    if(nodelay(stdscr, true) == ERR){
        std::cout << "error\n";
    }
    HandleScreenResizing();
}

void Quit(){
    endwin();
}

void UpdateNCurses(){
    HandleInput();
}

void HandleScreenResizing(){
    int nw, nh;
    getmaxyx(stdscr, nh, nw);

    if(nw != CURRENT_SCREEN_WIDTH || nh != CURRENT_SCREEN_HEIGHT){
        // std::cout << "Window resized to: " << nw << "x" << nh << "\n";   
        // wresize(stdscr, nh, nw);

        CURRENT_SCREEN_WIDTH    = nw;
        CURRENT_SCREEN_HEIGHT   = nh;
    }

    for(auto& func : resizeCallbacks){
        func();
    }
}

void HandleInput(){
    int c = getch();

    while(c != ERR){
        if(c == KEY_RESIZE){
            HandleScreenResizing();
            Refresh();
        }
        if(c == 'q'){
            SHOULD_QUIT = true;
        }

        for(auto& pair : callbacksIfKeyPressed){
            if(pair.first == c){
                pair.second();
            }
        }

        c = getch();
    }
}

void AddCallback(char c, void(*func)()){
    std::pair<char, void(*)()> newpair;

    newpair.first = c;
    newpair.second = func;

    callbacksIfKeyPressed.push_back(newpair);
}


void AddResizeCallback(void(*func)()){
    resizeCallbacks.push_back(func);
}

void Refresh(){
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

bool ShouldQuit(){
    return SHOULD_QUIT;
}

int GetWidth(){
    return CURRENT_SCREEN_WIDTH;
}

int GetHeight(){
    return CURRENT_SCREEN_HEIGHT;
}

int GetMaxWidth(){
    return SCREEN_WIDTH_MAX;
}

int GetMaxHeight(){
    return SCREEN_HEIGHT_MAX;
}

void PlotPixel(int x, int y, char c){
    if(x < 0 || y < 0 || x >= GetWidth() || y >= GetHeight()){
        return;
    }

    SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = c;
}

void DefaultScreen(){
    int w = std::min(CURRENT_SCREEN_WIDTH,  SCREEN_WIDTH_MAX);
    int h = std::min(CURRENT_SCREEN_HEIGHT, SCREEN_HEIGHT_MAX);

    char b = '#';
    char a[] = {
        '.', ' ', ' '
    };

    for(int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            if(x == 0 || y == 0 || x == CURRENT_SCREEN_WIDTH - 1 || y == CURRENT_SCREEN_HEIGHT - 1)
                SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = b;
            else
                SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = a[(y + x) % sizeof(a)];
        }
    }
}

void BlankScreen(){
    int w = std::min(CURRENT_SCREEN_WIDTH,  SCREEN_WIDTH_MAX);
    int h = std::min(CURRENT_SCREEN_HEIGHT, SCREEN_HEIGHT_MAX);

    char a = ' ';

    for(int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            SCREEN_DATA[y * SCREEN_WIDTH_MAX + x] = a;
        }
    }
}
