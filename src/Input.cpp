#include "Input.hpp"

using namespace Terminal;

namespace Input{

static GameTemplate* inputObject = nullptr;

void InitGameInput(GameTemplate* object){
    inputObject = object;
}

void ResizeEvent(){
    if(inputObject != nullptr)
        inputObject->ResizeEvent();
}

};
