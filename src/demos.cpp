#include "demos.hpp"

void BouncingBallTest(){
    const float vel = 0.03f;

    static float x = 0;
    static float y = 0;
    static float velx = vel;
    static float vely = vel;
    static float r = 5.f;

    if(x < r) velx = vel;
    if(y < r) vely = vel;
    if(x > (float)(GetWidth()   - 1) - r) velx = -vel;
    if(y > (float)(GetHeight()  - 1) - r) vely = -vel;

    x += velx;
    y += vely;

    DrawSolidBall(x, y, r, '#');
}

void CanvasTest(){
    const float vel = 0.05f;

    static float x = 0;
    static float y = 0;
    static float velx = vel;
    static float vely = vel;

    static Canvas canvas = Canvas(
        7, 5, 3, 2,

        " /---\\ \n" \
        "/     \\\n" \
        "|  X  |\n" \
        "\\     /\n" \
        " \\---/ \n"
    );

    if(x < 2) velx = vel;
    if(y < 3) vely = vel;
    if(x > GetWidth() - 3)    velx = -vel;
    if(y > GetHeight() - 3)   vely = -vel;

    x += velx;
    y += vely;
    
    DrawCanvas(x, y, &canvas);
}