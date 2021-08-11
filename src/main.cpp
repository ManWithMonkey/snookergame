#include <unistd.h>
#include "Game.hpp"
#include "MathFunctions.hpp"

#include <random>
#include <sstream>

template<typename T>
std::string ToString(const T& rhs){
    std::string result;

    std::stringstream ss;
    ss << rhs;
    result += ss.str();

    return result;
}

static Game game;

void Randomize(){
    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };

    game.Randomize();
}

void SetOther(){
}

void MoveL(){
}

void D(){
}

void W(){
}

void S(){
}

int main(){
    Init();

    Randomize();
    AddCallback('r', Randomize);
    // AddCallback('a', MoveL);
    // AddCallback('d', MoveR);
    // AddCallback('w', MoveU);
    // AddCallback('s', MoveD);
    // AddCallback(' ', SetOther);

    while(!ShouldQuit()){
        UpdateNCurses();
        BlankScreen();

        // const float r = 10.f;
        // vec2 n = NormalUnit(p4 - p3);
        // vec2 collision = LineCollisionPoint(p1, p2, p3, p4);
        // vec2 mirror = MirrorVectorFromNormal(p1 - collision, n);
        // vec2 mirroredDst = collision + mirror;

        // DrawFunctions::DrawLine(p3.x, p3.y, p4.x, p4.y, 176);
        // DrawFunctions::DrawLine(p2.x, p2.y, collision.x, collision.y, 176);
        // DrawFunctions::DrawLine(collision.x, collision.y, mirroredDst.x, mirroredDst.y, 176);
        // DrawFunctions::DrawPoint(p1.x, p1.y, 'X');
        // DrawFunctions::DrawPoint(p2.x, p2.y, 'X');
        // DrawFunctions::DrawPoint(p3.x, p3.y, 'X');
        // DrawFunctions::DrawPoint(p4.x, p4.y, 'X');

        // std::string s = ToString(collision.x) + ", " + ToString(collision.y);
        // DrawFunctions::TypeString(1, 1, s);

        game.Update();
        game.Draw();

        Refresh();
        usleep(1000);
    }

    Quit();

    return 0;
}
