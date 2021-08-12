#ifndef __NCURSESHELPER_H__
#define __NCURSESHELPER_H__

#include <curses.h>

#include <math.h>
#include <algorithm>
#include <iostream>

static const int SCREEN_WIDTH_MAX = 200;
static const int SCREEN_HEIGHT_MAX = 100;

static int SCREEN_DATA[SCREEN_WIDTH_MAX * SCREEN_HEIGHT_MAX];

static int CURRENT_SCREEN_WIDTH = 0;
static int CURRENT_SCREEN_HEIGHT = 0;

static bool SHOULD_QUIT = false;

void Init();
void Quit();
void Refresh();

bool ShouldQuit();
int GetWidth();
int GetHeight();
int GetMaxWidth();
int GetMaxHeight();

void UpdateNCurses();
void HandleScreenResizing();
void HandleInput();

void PlotPixel(int x, int y, char c);

void DefaultScreen();

#endif // __NCURSESHELPER_H__