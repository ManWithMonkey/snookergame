#include "demos.hpp"

using namespace DrawFunctions;

static float x = 0;
static float y = 0;

void BouncingBallTest(){
    const float vel = 0.03f;

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

static float x2 = 0;
static float y2 = 0;

void CanvasTest(){
    const float vel = 0.05f;

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

    if(x2 < 2) velx = vel;
    if(y2 < 3) vely = vel;
    if(x2 > GetWidth() - 3)    velx = -vel;
    if(y2 > GetHeight() - 3)   vely = -vel;

    x2 += velx;
    y2 += vely;
    
    DrawCanvas(x2, y2, &canvas);
}

void DrawLineTest(){
    DrawLine(x, y, x2, y2, 'x');
}
