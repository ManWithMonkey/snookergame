#include "NCursesHelper.hpp"

namespace Terminal{

// static variables

// width and height updated from HandleScreenResizing on runtime
static int WIDTH = 0;
static int HEIGHT = 0;

static bool SHOULD_QUIT = false;

static bool USE_COLOR = false;
static int  CURRENT_DRAW_COLOR = COLOR_PAIR(WHITE_ON_BLACK);

static std::vector<std::pair<int, void(*)()>> callbacksIfKeyPressed;
static std::vector<void(*)()> resizeCallbacks;
static std::vector<void(*)(int)> keyCallbacks;

void EnableColor(){
	USE_COLOR = true;
}

void DisableColor(){
	USE_COLOR = false;
}


int Index(int x, int y){
    return (y * MAX_WIDTH + x);
}

void SetDrawColor(int cp){
	CURRENT_DRAW_COLOR = COLOR_PAIR(cp);
}

void PlotPixel(int x, int y, char c){
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;

    SCREEN_DATA[Index(x, y)] = c;

	if(USE_COLOR){
    	COLOR_DATA[Index(x, y)] = CURRENT_DRAW_COLOR;
	}
}


void Init() {
	// window
	assert(initscr() != NULL);

	// colors
	assert(has_colors());
	assert(can_change_color());
	CHECK(start_color());

	// input settings
	CHECK(keypad(stdscr, true));
	CHECK(noecho());
	CHECK(nodelay(stdscr, true));

	// cursor
	CHECK(curs_set(CURS_INVIS));

	// screen size
	HandleScreenResizing();

	// color pairs
	// syntax : init_pair (color_id, foreground, background)
	init_pair(WHITE_ON_BLACK, WHITE, BLACK);
	init_pair(BLACK_ON_RED,   BLACK, RED);
	init_pair(BLACK_ON_GREEN, BLACK, GREEN);
	init_pair(BLACK_ON_BLUE,  BLACK, BLUE);

	attr_on(COLOR_PAIR(BLACK_ON_RED), NULL);

	EnableColor();
}

void Quit() {
	endwin();
}

void HandleEvents() {
	HandleInput();
}

void HandleScreenResizing() {
	int nw, nh;
	getmaxyx(stdscr, nh, nw);

	WIDTH = nw;
	HEIGHT = nh;

    for(auto& func : resizeCallbacks){
        func();
    }
}

void HandleInput() {
	int c;

	while ((c = getch()) != ERR) {
		switch (c) {
		case KEY_RESIZE:
			HandleScreenResizing();
			Refresh();
			break;
		case 'q':
		case 'Q':
			SHOULD_QUIT = true;
			break;
		}

        for(auto& pair : callbacksIfKeyPressed){
            if(pair.first == c){
                pair.second();
            }
        }

        for(auto& callback : keyCallbacks){
			callback(c);
        }
	}
}

void AddCallback(int c, void(*func)()){
    std::pair<int, void(*)()> newpair;

    newpair.first = c;
    newpair.second = func;

    callbacksIfKeyPressed.push_back(newpair);
}

void AddResizeCallback(void(*func)()){
    resizeCallbacks.push_back(func);
}

// template<typename T>
// void AddObjectCallBack(ObjectCallbackFunction<T> callback){
// 	objectCallbacks.push_back(callback);
// }

void AddKeyCallback(void(*func)(int)){
	keyCallbacks.push_back(func);
}

void Refresh() {
	int w = std::min(WIDTH,   MAX_WIDTH);
	int h = std::min(HEIGHT,  MAX_HEIGHT);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++){
			int index = Index(x, y);

			char pixel = SCREEN_DATA[index];
			int color = COLOR_DATA[index];

			if(USE_COLOR){
				attr_on(color, NULL);
				mvaddch(y, x, pixel);
				attr_off(color, NULL);
			}
			else{
				mvaddch(y, x, pixel);
			}

		}
	}

	refresh();
}

bool ShouldQuit() {
	return SHOULD_QUIT;
}

int GetWidth() {
	return WIDTH;
}

int GetHeight() {
	return HEIGHT;
}

}; // namespace Terminal
