#include "NCursesHelper.hpp"

namespace Terminal{

// width and height updated from HandleScreenResizing on runtime
static int WIDTH = 0;
static int HEIGHT = 0;

// terminal should be closing
static bool SHOULD_QUIT = false;

// color stuff
static bool USE_COLOR = false;
static int  CURRENT_DRAW_COLOR = COLOR_PAIR(WHITE_ON_BLACK);
static TerminalColorModule colorTable;

// mouse
static bool USE_MOUSE = true;
static MEVENT MOUSE_EVENT;

// callback object
static std::vector<EventCallbackClass*> callbacks;


void EnableColor(){
	USE_COLOR = true;
}

void DisableColor(){
	USE_COLOR = false;
}

void EnableMouse(){
	USE_MOUSE = true;
	printf("\033[?1003h\n");
	Refresh();
}

void DisableMouse(){
	USE_MOUSE = false;
	printf("\033[?1003l\n");
	Refresh();
}

int Index(int x, int y){
    return (y * MAX_WIDTH + x);
}

// static const int OFFSET = 20;
// static const int MAXIMUM_COLOR = 200;
// static std::vector<Color> InitializedColors;

void SetDrawColor(unsigned short r, unsigned short b, unsigned short g){
	int colorId = colorTable.GetIdOfColorPair(r, g, b);

	if(colorId < 0)
		return;
	
	CURRENT_DRAW_COLOR = colorId;
}

void PlotPixel(int x, int y, char c){
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;

    SCREEN_DATA[Index(x, y)] = c;

	if(USE_COLOR){
    	COLORID_DATA[Index(x, y)] = CURRENT_DRAW_COLOR;
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

	// mouse
	mouseinterval(0);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

	// screen size
	HandleResizeEvent();

	// color pairs
	// syntax : init_pair (color_id, foreground, background)
	init_pair(WHITE_ON_BLACK, WHITE, BLACK);
	init_pair(BLACK_ON_RED,   BLACK, RED);
	init_pair(BLACK_ON_GREEN, BLACK, GREEN);
	init_pair(BLACK_ON_BLUE,  BLACK, BLUE);

	attr_on(COLOR_PAIR(WHITE_ON_BLACK), NULL);

	EnableColor();
	EnableMouse();
}

void Quit() {
	DisableColor();
	DisableMouse();

	endwin();
}

void HandleEvents() {
	int key;

	while ((key = getch()) != ERR) {
		switch (key) {
		case KEY_RESIZE:
			HandleResizeEvent();
			break;

		case KEY_MOUSE:
			HandleMouseEvent();
			break;

		default:
			HandleKeyboardEvent(key);
		}
	}
}

void HandleResizeEvent() {
	int nw, nh;
	getmaxyx(stdscr, nh, nw);

	WIDTH = nw;
	HEIGHT = nh;

    for(auto& objCallback : callbacks){
        objCallback->ResizeEvent();
    }

	Refresh();
}

void HandleMouseEvent(){
	getmouse(&MOUSE_EVENT);

	for(auto& objCallback : callbacks){
		objCallback->MouseEvent(MOUSE_EVENT.x, MOUSE_EVENT.y, MOUSE_EVENT.bstate);
	}
}

void HandleKeyboardEvent(int key){
	if(key == 'q' || key == 'Q'){
		SHOULD_QUIT = true;
		return;
	}

	for(auto& objCallback : callbacks){
		objCallback->KeyEvent(key);
	}
}

void AddCallback(EventCallbackClass* obj){
	callbacks.push_back(obj);
}

void Refresh() {
	if(USE_COLOR)
		colorTable.RefreshStart();
	
	int w = std::min(WIDTH,   MAX_WIDTH);
	int h = std::min(HEIGHT,  MAX_HEIGHT);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++){
			int index = Index(x, y);

			char pixel = SCREEN_DATA[index];
			int colorid = COLORID_DATA[index];
			int color = COLOR_PAIR(colorid);

			if(USE_COLOR){
				attr_on(color, NULL);
				mvaddch(y, x, pixel);
				attr_off(color, NULL);

				colorTable.MarkColorAsUsed(colorid);
			}
			else{
				mvaddch(y, x, pixel);
			}

		}
	}

	refresh();

	if(USE_COLOR)
		colorTable.RemoveUnused();
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
