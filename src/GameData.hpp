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

    void ClearGameData();
};

#endif // __GAMEDATA_H__