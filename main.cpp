#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 40

char CONSOLE[SCREEN_HEIGHT*SCREEN_WIDTH];

void Clear(){
    for(int y = 0; y < SCREEN_HEIGHT; y ++){
        for(int x = 0; x < SCREEN_WIDTH; x ++){
            if(x == 0 || x == SCREEN_WIDTH - 1 || y == 0 || y == SCREEN_HEIGHT - 1)
                CONSOLE[y * SCREEN_WIDTH + x] = '#';
            else
                CONSOLE[y * SCREEN_WIDTH + x] = ' ';
        }
    }
}

void Update(double dt){
}

void Draw(){
    for(int y = 0; y < SCREEN_HEIGHT; y ++){
        for(int x = 0; x < SCREEN_WIDTH; x ++){
            std::cout << CONSOLE[y * SCREEN_WIDTH + x];
        }
        std::cout << '\n';
    }
}

// struct Ball;

int main(){
    // while(true){}
    Clear();
    Draw();
    return 0;
}