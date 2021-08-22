#ifndef __GAMEDRAW_H__
#define __GAMEDRAW_H__

#include "DrawFunctions.hpp"

#include "GameData.hpp"
#include "GameCueLogic.hpp"
#include "GameCollisions.hpp"

// todo: shouldnt have gamecollisions header?

class GameDraw : public virtual GameData, public virtual GameCueLogic, public virtual GameCollisions{ 
public:
    void Draw();

protected:
    const double MAX_GHOST_DISTANCE = map_width * 10.0;
    const double TRACER_LENGTH = map_width * 0.2;

    const Color backgroundColor = {200, 200, 400};
    const Color holeColor       = {150, 150, 300};
    const Color ballColor       = {900, 900, 1000};
    const Color ghostColor      = {170, 170, 350};
    const Color tracerColor     = {50, 50, 50};
    const Color lineColor       = {100, 100, 100};
    const Color cueColor        = {800, 800, 200};

protected:
    void DrawBall(double x, double y, double r, char c);
    void DrawLine(double x1, double y1, double x2, double y2, char c);

    void DrawBall(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);
    void DrawHole(const Hole& hole, char c);
    void DrawCue(const Cue& cue, char c, char x);
    // void DrawCueStrengthBar(const Cue& cue, char c, char x);
    void DrawCueGhosts(const Cue& cue, char c);
};

#endif // __GAMEDRAW_H__