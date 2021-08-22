#ifndef __GAMEDRAW_H__
#define __GAMEDRAW_H__

#include "DrawFunctions.hpp"
#include "GameData.hpp"

class GameDraw : public virtual GameData{
public:
    void Draw();

protected:
    const double map_width      = 2.0;
    const double map_height     = 1.0;

    double fromMapToScreenScalarX;
    double fromMapToScreenScalarY;

protected:
    void DrawBall(double x, double y, double r, char c);
    void DrawLine(double x1, double y1, double x2, double y2, char c);

    void DrawBall(const Ball& ball, char c);
    void DrawBallRainbow(const Ball& ball, char c);
    void DrawLine(const Line& line, char c);
    void DrawHole(const Hole& hole, char c);
    void DrawCue(const Cue& cue, char c, char x);
    void DrawCueStrengthBar(const Cue& cue, char c, char x);
    // void DrawCueGhosts(const Cue& cue, char c);
};

#endif // __GAMEDRAW_H__