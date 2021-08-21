#include "GameTemplate.hpp"

GameTemplate::GameTemplate(){
    lastUpdate = std::chrono::steady_clock::now();
}

void GameTemplate::Update(){
    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1E6;
    lastUpdate = now;

    if(postResetCall){
        Reset();
        postResetCall = false;

        // no need to update right after reset
        return;
    }

    GameLogic::Update(deltaTime);
    GameCueLogic::UpdateCue(deltaTime);
}

void GameTemplate::Reset(){
    InitializeGame();
}

void GameTemplate::InitializeGame(){
    ClearGameData();
    
    InitDefaultMapFormation();
    InitDefaultBallFormation();
    InitDefaultCue();
}

void GameTemplate::InitDefaultMapFormation(){
}

void GameTemplate::InitDefaultCue(){
}

void GameTemplate::InitDefaultBallFormation(){
}

