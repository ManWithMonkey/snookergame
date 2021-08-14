#ifndef __INPUT_H__
#define __INPUT_H__

#include "NCursesHelper.hpp"
#include "Game.hpp"

namespace Input{

void InitGameInput(Game* object);
void InitCallbacks();

void ResizeEvent();

void Reset();
void Space();
void Up();
void Down();
void Left();
void Right();
void Key1();
void Key2();

}; // namespace Input

#endif // __INPUT_H__