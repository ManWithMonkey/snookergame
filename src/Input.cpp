#include "Input.hpp"

using namespace Terminal;

namespace Input{

static GameTemplate* inputObject = nullptr;

void InitCallbacks(){
    AddResizeCallback(ResizeEvent);
    AddKeyCallback(KeyEvent);
}

void InitGameInput(GameTemplate* object){
    inputObject = object;
}

void ResizeEvent(){
    if(inputObject != nullptr)
        inputObject->ResizeEvent();
}

void KeyEvent(int key){
    if(inputObject != nullptr)
        inputObject->KeyEvent(key);
}

};
