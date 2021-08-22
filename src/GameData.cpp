#include "GameData.hpp"

void GameData::ClearGameData(){
    balls.clear();
    lines.clear();
    holes.clear();
    // cues.clear();
}

int GameData::GetCueballIndex(){
    for(int i=0; i<balls.size(); i++){
        if(balls[i].isCueball)
            return i;
    }

    return -1;
}
