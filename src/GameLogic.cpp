#include "GameLogic.hpp"

GameLogic::GameLogic(){
}

void GameLogic::Update(double dt){
    double w = GetWidth();
    double h = GetHeight();

    // todo, ApplyDeacceleration()

    // deaccelerate
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];
        ball.vel = ball.vel * (1.0 - deacceleration * dt);
    }

    // holes
    UpdateBallHoleInteraction(dt);

    // todo: CalculateMotions for dpos
    // calculate dpos
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        if(!ball.active)
            continue;

        // REMOVE START - should be optional or in a function
        double velx = std::max(0.1, std::abs(ball.vel.x));
        double vely = std::max(0.1, std::abs(ball.vel.y));

        // totally out of bounds
        if(ball.pos.x < 0.)             ball.vel.x =  velx;
        if(ball.pos.y < 0.)             ball.vel.y =  vely;
        if(ball.pos.x >= map_width)     ball.vel.x = -velx;
        if(ball.pos.y >= map_height)    ball.vel.y = -vely;
        // REMOVE END

        // position change
        ball.dpos.x = ball.vel.x * dt;
        ball.dpos.y = ball.vel.y * dt;
    }

    // collisions
    HandleCollisionsAndApplyMotion();
}

void GameLogic::UpdateBallHoleInteraction(double dt){
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        for(Hole& hole : holes){
            bool inside = hole.IsInside(ball);
            bool close = hole.IsClose(ball);

            if(inside){
                ball.active = false;
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
