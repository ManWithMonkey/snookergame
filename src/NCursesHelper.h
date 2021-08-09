#ifndef __NCURSESHELPER_H__
#define __NCURSESHELPER_H__

#include "ncurses.h"

#include <math.h>
#include <algorithm>
#include <iostream>

static const int SCREEN_WIDTH_MAX = 200;
static const int SCREEN_HEIGHT_MAX = 100;

static int SCREEN_DATA[SCREEN_WIDTH_MAX * SCREEN_HEIGHT_MAX];

static int CURRENT_SCREEN_WIDTH = 0;
static int CURRENT_SCREEN_HEIGHT = 0;

void Init();
void Quit();
void UpdateScreenVariables();
void Refresh();

void DefaultScreenTest();
void TestPlotScreenResize();

#endif // __NCURSESHELPER_H__