#ifndef __INPUT_H__
#define __INPUT_H__

#include "NCursesHelper.hpp"
#include "GameTemplate.hpp"

// todo: this is an ugly wrapper since Terminal cant call Game::KeyEvent itself (i think)

namespace Input{

void InitGameInput(GameTemplate* object);
void InitCallbacks();

void ResizeEvent();
void KeyEvent(int key);

}; // namespace Input

#endif // __INPUT_H__