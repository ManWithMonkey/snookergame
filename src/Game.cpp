#include "Game.hpp"

Game::Game(){
    Reset();
    ResizeEvent();

    lastUpdate = std::chrono::steady_clock::now();
}

void Game::Draw(){
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
}

void Game::ResizeEvent(){
    x_factor = (float)GetWidth()    / map_width; 
    y_factor = (float)GetHeight()   / map_height;
}

void Game::Reset(){
    auto frand = []() -> float {
        return (float)rand() / ((float)(RAND_MAX) + 1.f);
    };

    balls.clear();
    lines.clear();

    const float l = 0.15f * map_width;
    const float t = 0.15f * map_height;
    const float r = map_width - l;
    const float b = map_height - t;
    const float holer = 0.12f;
    const float ballr = 0.06f;

    std::vector<vec2> pointBand;

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

    float angleOffsets[4] = {
        1.f * 3.14159f * 0.5f,
        0.f * 3.14159f * 0.5f,
        3.f * 3.14159f * 0.5f,
        2.f * 3.14159f * 0.5f
    };

    for(int i=0; i<4; i++){
        pointBand.push_back(corners[i][1]);

        int pc = 8;
        float da = 1.5f * 3.14159f / (float)pc;
        for(int j=0; j<pc; j++){
            float ang = 2.f * 3.14159f - (float)j * da + angleOffsets[i];
            float length = holer;

            vec2 point = corners[i][0] + MakeVector(ang, length);
            pointBand.push_back(point);
        }
        
        pointBand.push_back(corners[i][2]);
    }
    
    lines.push_back({pointBand.back(), pointBand.front()});
    for(int i=1; i<pointBand.size(); i++){
        lines.push_back({
            pointBand[i],
            pointBand[i-1]
        });
    }

    for(int j=0; j<2; j++){
        for(int i=0; i<3; i++){
            Ball ball;
            ball.pos = {map_width / 2.f - 6.f * ballr + (float)i * 2.5f * ballr, map_height / 2.f - 3.f * ballr + 2.f * ballr * (float)j};
            ball.vel = {-2.f + 4.f * frand(), -2.f + 4.f * frand()};
            ball.r = ballr;

            balls.push_back(ball);
        }
    }

    Hole hole;
    hole.holeRadius = holer * 0.8f;
    hole.insideRadius = ballr * 1.1f;
    hole.pullStrength = 1000.f * map_width;
    
    hole.pos = tl;
    holes.push_back(hole);
    hole.pos = tr;
    holes.push_back(hole);
    hole.pos = bl;
    holes.push_back(hole);
    hole.pos = br;
    holes.push_back(hole);
}

void Game::Update(){
    float w = GetWidth();
    float h = GetHeight();

    UpdateHoleStuff();

    for(int i = 0; i < balls.size(); i++){
        Ball& ball = balls[i];

        if(!ball.active)
            continue;

        float velx = std::max(0.1f, std::abs(ball.vel.x));
        float vely = std::max(0.1f, std::abs(ball.vel.y));

        // totally out of bounds
        if(ball.pos.x < 0.f)            ball.vel.x =  velx;
        if(ball.pos.y < 0.f)            ball.vel.y =  vely;
        if(ball.pos.x >= map_width)     ball.vel.x = -velx;
        if(ball.pos.y >= map_height)    ball.vel.y = -vely;

        ball.vel = ball.vel * (1.f - 0.1f * deltaTime);

        // position change
        ball.dpos.x = ball.vel.x * deltaTime;
        ball.dpos.y = ball.vel.y * deltaTime;
    }

    UpdatePositionsAndHandleCollisions();
    HandleClippingIfNecessary();

    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
    lastUpdate = now;
}

void Game::UpdateHoleStuff(){
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
                float distance = Norm(ball.pos - hole.pos);
                float strength = std::pow(hole.holeRadius - distance, 2.f) * hole.pullStrength;
                
                vec2 unit = UnitVector(hole.pos - ball.pos);

                float slowdownScalar = Norm(ball.vel) * ball.r / hole.holeRadius * 0.1f;
                ball.vel = ball.vel * (1.f - slowdownScalar * deltaTime) + unit * strength * deltaTime;
            }
        }
    }
}

void Game::DrawBall(const Ball& ball, char c){
    float x = ball.pos.x    * x_factor;
    float y = ball.pos.y    * y_factor;
    float rx = ball.r       * x_factor;
    float ry = ball.r       * y_factor;

    DrawFunctions::DrawSolidEllipse(x, y, rx, ry, c);
}

void Game::DrawLine(const Line& line, char c){
    float x1 = line.a.x * x_factor;
    float y1 = line.a.y * y_factor;
    float x2 = line.b.x * x_factor;
    float y2 = line.b.y * y_factor;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
}

void Game::DrawHole(const Hole& hole, char c){
    float x1 = hole.pos.x * x_factor;
    float y1 = hole.pos.y * y_factor;
    float rx = hole.holeRadius * x_factor;
    float ry = hole.holeRadius * y_factor;

    DrawFunctions::DrawSolidEllipse(x1, y1, rx, ry, c);
}
