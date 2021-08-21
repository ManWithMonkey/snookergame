#include "Input.hpp"

namespace Input{

static GameTemplate* inputObject = nullptr;

void InitCallbacks(){
    AddResizeCallback(ResizeEvent);
    
    AddCallback('r', Reset);
    AddCallback(' ', Space);
    AddCallback(KEY_UP, Up);
    AddCallback(KEY_DOWN, Down);
    AddCallback(KEY_LEFT, Left);
    AddCallback(KEY_RIGHT, Right);
    AddCallback('1', Key1);
    AddCallback('2', Key2);
}

void InitGameInput(GameTemplate* object){
    inputObject = object;
}

void ResizeEvent(){
    if(inputObject != nullptr)
        inputObject->ResizeEvent();
}

void Reset(){
    if(inputObject != nullptr)
        inputObject->Reset();
}

void Space(){
    if(inputObject != nullptr)
        inputObject->SpaceEvent();
}

void Up(){
    if(inputObject != nullptr)
        inputObject->UpEvent();
}

void Down(){
    if(inputObject != nullptr)
        inputObject->DownEvent();
}

void Left(){
    if(inputObject != nullptr)
        inputObject->LeftEvent();
}

void Right(){
    if(inputObject != nullptr)
        inputObject->RightEvent();
}

void Key1(){
}

void Key2(){
}

};
