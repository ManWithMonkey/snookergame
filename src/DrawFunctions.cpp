#include "DrawFunctions.hpp"

void DrawSolidBall(float x, float y, float r, char c){
    float iy = y - r;
    float ix;

    // for(float i = 0; i < y + r; i += 1.f){
    // }

    while(iy <= y + r){
        float hw = std::sqrt(std::abs(r * r - (iy - y) * (iy - y)));

        ix = x - hw;

        while(ix <= x + hw){
            PlotPixel(ix, iy, c);

            ix += 1.f;
        }

        iy += 1.f;
    }
}

void BouncingBallTest(){
    const float vel = 0.01f;

    static float x = 0;
    static float y = 0;
    static float velx = vel;
    static float vely = vel;

    if(x < 0) velx = vel;
    if(y < 0) vely = vel;
    if(x > GetWidth() - 1)    velx = -vel;
    if(y > GetHeight() - 1)   vely = -vel;

    x += velx;
    y += vely;

    DrawSolidBall(x, y, 5.f, '#');
}

Canvas::Canvas(int w, int h, int cx, int cy, std::string str) :
    w(w), h(h), cx(cx), cy(cy)
{
    data = new char[w * h];

    int y = 0;

    std::istringstream ss(str);
    std::string line;
    while(std::getline(ss, line, '\n')){
        for(int x=0; x<w; x++){
            data[y * w + x] = line[x];
        }
        y ++;
    }
}

void DrawCanvas(int x, int y, const Canvas* canvas){
    for(int iy = 0; iy < canvas->h; iy ++){
        for(int ix = 0; ix < canvas->w; ix ++){
            int x2 = ix + x - canvas->cx;
            int y2 = iy + y - canvas->cy;

            char c = canvas->data[iy * canvas->w + ix];

            if(c != canvas->alpha){
                PlotPixel(x2, y2, c);
            }
        }
    }
}

void CanvasTest(){
    const float vel = 0.05f;

    static float x = 0;
    static float y = 0;
    static float velx = vel;
    static float vely = vel;

    Canvas canvas = Canvas(
        7, 5, 0, 0,

        "1232123\n" \
        "3     5\n" \
        "6  X  8\n" \
        "3     5\n" \
        "1232123\n"
    );

    if(x < 0) velx = vel;
    if(y < 0) vely = vel;
    if(x > GetWidth() - 1)    velx = -vel;
    if(y > GetHeight() - 1)   vely = -vel;

    x += velx;
    y += vely;
    
    DrawCanvas(x, y, &canvas);
}
