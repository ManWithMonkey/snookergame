#include "demos.hpp"

using namespace DrawFunctions;

static double x = 0;
static double y = 0;

void BouncingBallTest(){
    const double vel = 0.03;

    static double velx = vel;
    static double vely = vel;
    static double r = 5.;

    if(x < r) velx = vel;
    if(y < r) vely = vel;
    if(x > (double)(GetWidth()   - 1) - r) velx = -vel;
    if(y > (double)(GetHeight()  - 1) - r) vely = -vel;

    x += velx;
    y += vely;

    DrawSolidBall(x, y, r, '#');
}

static double x2 = 0;
static double y2 = 0;

void CanvasTest(){
    const double vel = 0.05;

    static double velx = vel;
    static double vely = vel;

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
