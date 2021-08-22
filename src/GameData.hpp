#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include "GameUtils.hpp"

class GameData{
public:
    // todo: seperate collision lines and draw lines
    std::vector<Line> lines;
    std::vector<Ball> balls;
    std::vector<Hole> holes;

    // std::vector<Cue> cues;
    Cue cue;

    const double map_width      = 2.0;
    const double map_height     = 1.0;
    
    double fromMapToScreenScalarX;
    double fromMapToScreenScalarY;

    void ClearGameData();
};

#endif // __GAMEDATA_H__