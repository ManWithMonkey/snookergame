#include "Game.hpp"

Game::Game(){
    Reset();
    ResizeEvent();

	lastUpdate = std::chrono::steady_clock::now();
}

void Game::Update(){
    float w = GetWidth();
    float h = GetHeight();

    for(Ball& ball : balls){
        float x = ball.pos.x;
        float y = ball.pos.y;

        float velx = std::abs(ball.vel.x);
        float vely = std::abs(ball.vel.y);

        // totally out of bounds
        if(x < 0.f)     ball.vel.x = velx;
        if(y < 0.f)     ball.vel.y = vely;
        if(x > w - 1.f) ball.vel.x = -velx;
        if(y > h - 1.f) ball.vel.y = -vely;

        // const float deacceleration = 0.9f;
        // ball.vel.x *= (1.f - deltaTime * deacceleration);
        // ball.vel.y *= (1.f - deltaTime * deacceleration);

        // position change
        ball.dpos.x = ball.vel.x * deltaTime;
        ball.dpos.y = ball.vel.y * deltaTime;

        // correct collisions, needs refactor
        bool collisionsLastIteration = true;
        for(int i=0; (i<MAX_COLLISIONS_ITERS) && collisionsLastIteration; i++){
            collisionsLastIteration = false;

            float minDistance = 10000000.f;
            int lineIndex = 0;
            vec2 normalMin, centerMin, closestMin, mirrorMin;

            for(Line& line : lines){
                if(MovingCircleCollidesWithStaticLine(ball.pos, ball.dpos, ball.r, line.a, line.b)){
                    vec2 collisionCircleCenter = MovingCircleCollisionPointWithLine(ball.pos, ball.dpos, ball.r, line.a, line.b);
                    vec2 closest = LineClosestPointFromPoint(line.a, line.b, ball.pos);

                    float distance = Norm(collisionCircleCenter - closest);

                    if(distance > minDistance)
                        continue;

                    minDistance = distance;
                    centerMin = collisionCircleCenter;
                    closestMin = closest;
                    normalMin = UnitVector(closest - ball.pos); // line.nu
                    mirrorMin = MirrorVectorFromNormal(ball.pos + ball.dpos - collisionCircleCenter, normalMin);
                    // vec2 mirroredDst = collisionCircleCenter + mirror;

                    collisionsLastIteration = true;
                }
            }

            if(collisionsLastIteration){
                float l = Norm(ball.dpos);
                float mirrorl = Norm(mirrorMin);

                ball.pos = ball.pos + UnitVector(ball.dpos) * (l - mirrorl) * MIRROR_LOSS;

                ball.dpos = UnitVector(mirrorMin) * mirrorl            * DPOS_LOSS;
                ball.vel = MirrorVectorFromNormal(ball.vel, normalMin) * VEL_LOSS;
            }
        }

        // add position change
        ball.pos.x += ball.dpos.x;
        ball.pos.y += ball.dpos.y;
    }

    for(Line& line : lines)
        line.UpdateNormal();

    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
    lastUpdate = now;
}

void Game::Draw() {
	Terminal::SetDrawColor(BLACK_ON_GREEN);
	for (Ball &ball : balls) {
		DrawBall(ball, 'O');
	}

	Terminal::SetDrawColor(BLACK_ON_RED);
    for(Line& line : lines){
        DrawLine(line, '#');
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
    const float holer = 0.08f;
    const float ballr = 0.04f;

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

    Ball ball;
    ball.pos = {map_width / 2.f, map_height / 2.f};
    ball.vel = {-5.f, 5.f};
    ball.r = ballr;
    balls.push_back(ball);
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
