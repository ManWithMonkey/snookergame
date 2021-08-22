#include "GameLogic.hpp"

GameLogic::GameLogic(){
}

void GameLogic::Update(double dt){
    double w = Terminal::GetWidth();
    double h = Terminal::GetHeight();

    UpdateBallHoleInteraction(dt);
    ApplyDeacceleration(dt);
    CalculateMotions(dt);
    HandleCollisionsAndApplyMotion();
}

void GameLogic::ApplyDeacceleration(double dt){
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];
        ball.vel = ball.vel * (1.0 - deacceleration * dt);

        // instant stop if too slow
        if(Norm(ball.vel) < instantStopBelowVelocity)
            ball.vel = {0, 0};
    }
}

void GameLogic::CalculateMotions(double dt){
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];
        if(!ball.active)
            continue;

        // position change
        ball.dpos.x = ball.vel.x * dt;
        ball.dpos.y = ball.vel.y * dt;
    }
}

void GameLogic::UpdateBallHoleInteraction(double dt){
    // todo: holes dont really work properly, sometimes even accelerates ball to bounce at high velocity from hole

    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        for(Hole& hole : holes){
            bool inside = hole.IsInside(ball);
            bool close = hole.IsClose(ball);

            if(inside){
                HandleBallInsideHole(ball);
                break;
            }
            if(close){
                double distance = Norm(ball.pos - hole.pos);
                double strength = holeSuckMinVel + distance * hole.pullStrength;
                
                vec2 unit = UnitVector(hole.pos - ball.pos);

                ball.vel = ball.vel * (1.0 - holeDeacceleration * dt);
                ball.vel = ball.vel + unit * strength * dt;
            }
        }
    }
}

void GameLogic::HandleBallInsideHole(Ball& ball){
    ball.active = false;
    if(ball.isCueball){
        cuehand.active = true;
        cuehand.ballIndex = GetCueballIndex();
    }
}
