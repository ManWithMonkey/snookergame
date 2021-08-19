#include "Game.hpp"

Game::Game(){
    Reset();
    ResizeEvent();

    lastUpdate = std::chrono::steady_clock::now();
}

void Game::Draw(){
    // ghosts
    if(cue.active){
        DrawCueGhosts(cue, '.');
    }

    for(Hole& hole : holes){
        DrawHole(hole, '.');
    }

    for(Ball& ball : balls){
        if(ball.active)
            DrawBall(ball, '#');
    }

    for(Line& line : lines){
        DrawLine(line, 176);
    }

    // cue
    if(cue.active){
        DrawCue(cue, 176, 'X');
    }
}

void Game::ResizeEvent(){
    x_factor = (double)GetWidth()    / map_width; 
    y_factor = (double)GetHeight()   / map_height;
}

void Game::Reset(){
    auto frand = []() -> double {
        return (double)rand() / ((double)(RAND_MAX) + 1.0);
    };

    lines.clear();

    std::vector<vec2> pointBand;
    std::vector<double> lastBounceBand;

    vec2 tr = {r, t};
    vec2 br = {r, b};
    vec2 bl = {l, b};
    vec2 tl = {l, t};
    vec2 tr_x = {r,             t + holer};
    vec2 tr_y = {r - holer,     t};
    vec2 br_x = {r,             b - holer};
    vec2 br_y = {r - holer,     b};
    vec2 bl_x = {l,             b - holer};
    vec2 bl_y = {l + holer,     b};
    vec2 tl_x = {l,             t + holer};
    vec2 tl_y = {l + holer,     t};

    vec2 corners[4][3]{
        {tr, tr_x, tr_y},
        {tl, tl_y, tl_x},
        {bl, bl_x, bl_y},
        {br, br_y, br_x}
    };

    double angleOffsets[4] = {
        1. * M_PI * 0.5,
        0. * M_PI * 0.5,
        3. * M_PI * 0.5,
        2. * M_PI * 0.5
    };


    for(int i=0; i<4; i++){
        pointBand.push_back(corners[i][1]);
        lastBounceBand.push_back(wallBounce);

        double da = (1.) * M_PI / (double)holePointCount;
        for(int j=0; j<holePointCount; j++){
            double ang = 2. * M_PI - (double)j * da + angleOffsets[i] - M_PI * 0.25;
            double length = realholer;

            vec2 center = (corners[i][2] + corners[i][1] + corners[i][0] * 2.) * 0.25;
            vec2 point = center + MakeVector(ang, length);
            pointBand.push_back(point);
            lastBounceBand.push_back(holeWallBounce);
        }
        
        pointBand.push_back(corners[i][2]);
        lastBounceBand.push_back(wallBounce);
    }
    
    lines.push_back({pointBand.back(), pointBand.front(), lastBounceBand.front()});
    for(int i=1; i<pointBand.size(); i++){
        double bounce = lastBounceBand[i];

        lines.push_back({
            pointBand[i],
            pointBand[i-1],
            bounce
        });
    }

    Hole hole;
    hole.holeRadius = realholer * 1.0;
    hole.insideRadius = holeInsideRadius;
    hole.pullStrength = 100.0 * map_width;
    
    for(int i=0; i<4; i++){
        vec2 center = (corners[i][2] + corners[i][1] + corners[i][0] * 2.0) * 0.25;
        hole.pos = center;
        holes.push_back(hole);
    }

    balls.clear();
    InitDefaultBallFormation();

    InitDefaultCue();
}

void Game::Update(){
    double w = GetWidth();
    double h = GetHeight();

    // deaccelerate
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];
        ball.vel = ball.vel * (1.0 - deacceleration * deltaTime);
    }

    // holes
    UpdateBallHoleInteraction();

    // calculate dpos
    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        if(!ball.active)
            continue;

        double velx = std::max(0.1, std::abs(ball.vel.x));
        double vely = std::max(0.1, std::abs(ball.vel.y));

        // totally out of bounds
        if(ball.pos.x < 0.)            ball.vel.x =  velx;
        if(ball.pos.y < 0.)            ball.vel.y =  vely;
        if(ball.pos.x >= map_width)     ball.vel.x = -velx;
        if(ball.pos.y >= map_height)    ball.vel.y = -vely;

        // position change
        ball.dpos.x = ball.vel.x * deltaTime;
        ball.dpos.y = ball.vel.y * deltaTime;
    }

    // collisions
    UpdatePositions();
    HandleClipping();

    // cue
    UpdateCueStuff();

    // deltatime for next iteration
    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1E6;
    lastUpdate = now;
}

void Game::UpdateBallHoleInteraction(){
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

                ball.vel = ball.vel * (1.0 - holeDeacceleration * deltaTime);
                ball.vel = ball.vel + unit * strength * deltaTime;
            }
        }
    }
}

void Game::InitDefaultBallFormation(){
    double w = r - l;
    double h = b - t;

    double startx = l + w * 0.7;
    double starty = t + h * 0.5;

    double dx = ballr * 2.2;
    double dy = ballr * 2.8;

    Ball ball;
    ball.r = ballr;
    ball.vel = {0.0, 0.0};

    for(int l=0; l<4; l++){
        double x = startx + dx * (double)l;

        for(int i=l+1; i>0; i--){
            double y = starty + dy * ((double)i - (double)l / 2.0 - 1.0);

            ball.pos = {x, y};
            balls.push_back(ball);
        }
    }

    double cueballx = l + w * 0.2;
    double cuebally = t + h * 0.5;

    ball.pos = {cueballx, cuebally};
    ball.vel = {0.0, 0.0};
    balls.push_back(ball);
}

void Game::InitDefaultCue(){
    cue.active = true;
    cue.ballIndex = balls.size() - 1;
    cue.angle = M_PI;
    cue.distanceFromBallMin = ballr * 0.5;
    cue.distanceFromBallMax = ballr * 6.0;
    cue.pullScale = 0.0;
    cue.lengthOnScreen = table_w * 0.25;
    cue.releaseMaxStregth = 6.0;
    cue.releaseMinStregth = 0.25;
    cue.rotationStatus = NO_ROTATION;

    vec2 toCenter = vec2{table_left, table_top} + vec2{table_w, table_h} * 0.5 - balls.back().pos;
    if(Norm(toCenter) >= balls.back().r * 4.){
        cue.angle = M_PI + atan2(toCenter.y, toCenter.x);
    }
}

void Game::DrawBall(double x, double y, double r, char c){
    x = x           * x_factor;
    y = y           * y_factor;
    double rx = r   * x_factor;
    double ry = r   * y_factor;

    DrawFunctions::DrawSolidEllipse(x, y, rx, ry, c);
}

void Game::DrawLine(double x1, double y1, double x2, double y2, char c){
    x1 = x1 * x_factor;
    y1 = y1 * y_factor;
    x2 = x2 * x_factor;
    y2 = y2 * y_factor;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
}

void Game::DrawBall(const Ball& ball, char c){
    double x = ball.pos.x    * x_factor;
    double y = ball.pos.y    * y_factor;
    double rx = ball.r       * x_factor;
    double ry = ball.r       * y_factor;

    DrawFunctions::DrawSolidEllipse(x, y, rx, ry, c);
}

void Game::DrawLine(const Line& line, char c){
    double x1 = line.a.x * x_factor;
    double y1 = line.a.y * y_factor;
    double x2 = line.b.x * x_factor;
    double y2 = line.b.y * y_factor;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
}

void Game::DrawHole(const Hole& hole, char c){
    double x1 = hole.pos.x * x_factor;
    double y1 = hole.pos.y * y_factor;
    double rx = hole.holeRadius * x_factor;
    double ry = hole.holeRadius * y_factor;

    DrawFunctions::DrawSolidEllipse(x1, y1, rx, ry, c);
}

void Game::DrawCue(const Cue& cue, char c, char x){
    if(cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;

    Ball* ball = &balls[cue.ballIndex];

    vec2 unit = MakeVector(cue.angle, 1.0);
    double distanceFromBall = cue.distanceFromBallMin + (cue.distanceFromBallMax - cue.distanceFromBallMin) * cue.pullScale + ball->r;
    double distanceFromBall2 = distanceFromBall + cue.lengthOnScreen;

    double x1 = (ball->pos + unit * distanceFromBall).x * x_factor;
    double y1 = (ball->pos + unit * distanceFromBall).y * y_factor;
    double x2 = (ball->pos + unit * distanceFromBall2).x * x_factor;
    double y2 = (ball->pos + unit * distanceFromBall2).y * y_factor;
    // double x3 = cue.targetPosition.x * x_factor;
    // double y3 = cue.targetPosition.y * y_factor;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
    // DrawFunctions::DrawPoint(x3, y3, x);
}

void Game::UpdateCueStuff(){

    if(cue.active && (cue.rotationStatus != NO_ROTATION) && !(cue.ballIndex < 0 || cue.ballIndex >= balls.size())){
        Ball* ball = &balls[cue.ballIndex];
        
        double newAngle = cue.angle + rotateCueVel * deltaTime * (cue.rotationStatus == ROTATE_LEFT ? -1.0 : 1.0);
        cue.angle = newAngle;
    }

    if(!cue.active){
        bool isEverythingSlowEnough = true;

        for(Ball& ball : balls){
            if(!ball.active)
                continue;
            double vel = Norm(ball.vel);

            if(vel > cueActivationVel){
                isEverythingSlowEnough = false;
                break;
            }
        }
        
        if(isEverythingSlowEnough){
            InitDefaultCue();
        }
    }
}

void Game::ReleaseCue(){
    if(!cue.active || cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;

    double strength = cue.releaseMinStregth + (cue.releaseMaxStregth - cue.distanceFromBallMin) * cue.pullScale;

    Ball* ball = &balls[cue.ballIndex];
    vec2 unit = MakeVector(cue.angle, -1.0);

    ball->vel = unit * strength;

    cue.active = false;
}


void Game::DrawCueGhosts(const Cue& cue, char c){
    if(!cue.active)
        return;
    if(cue.ballIndex < 0 || cue.ballIndex >= balls.size())
        return;

    Ball* ball = &balls[cue.ballIndex];
    vec2 unit = MakeVector(cue.angle, -100.0);

    vec2 temp = ball->dpos;
    ball->dpos = unit;

    auto bl = GetClosestBallLineCollision(*ball);
    auto bb = GetClosestBallBallCollision(*ball);

    ball->dpos = temp;

    bool apply_ballball_instead_of_ballline;

    bool b = !bb.nocollision;
    bool l = !bl.nocollision;

    if(!b && !l){
        // no more collisions, no need to iterate
        return;
    }
    else if(b && l){
        apply_ballball_instead_of_ballline = bb.scalarOfDeltatime < bl.scalarOfDeltatime;
    }
    else if(b){
        apply_ballball_instead_of_ballline = true;
    }
    else if(l){
        apply_ballball_instead_of_ballline = false;
    }

    double scalar;

    if(apply_ballball_instead_of_ballline)
        scalar = bb.scalarOfDeltatime;
    else
        scalar = bl.scalarOfDeltatime;

    vec2 ghost = ball->pos + unit * scalar;

    DrawLine(ball->pos.x, ball->pos.y, ghost.x, ghost.y, c);
    DrawBall(ghost.x, ghost.y, ball->r, c);
}
