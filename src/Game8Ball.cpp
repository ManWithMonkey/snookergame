#include "Game8Ball.hpp"

Game8Ball::Game8Ball(){
    Reset();
}

void Game8Ball::InitDefaultMapFormation(){
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
}

void Game8Ball::InitDefaultBallFormation(){
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
    ball.isCueball = true;
    balls.push_back(ball);
}

void Game8Ball::InitDefaultCue(){
    cuestick.angle = cueStartAngle;
    cuestick.ballIndex = GetCueballIndex();
    cuestick.distanceFromBallMin = cueDistanceFromBallMinMultipleOfBallr * ballr;
    cuestick.distanceFromBallMax = cueDistanceFromBallMaxMultipleOfBallr * ballr;
    cuestick.lengthOnScreen = cueLengthOnScreen;
    cuestick.pullScale = cueStartPullScale;
    cuestick.releaseMinStregth = cueReleaseMinStregth;
    cuestick.releaseMaxStregth = cueReleaseMaxStregth;
    cuestick.rotationStatus = NO_ROTATION;
    cuestick.active = true;

    cuehand.active = false;
    cuehand.pos = vec2{map_width, map_height} * 0.5;
}

bool Game8Ball::IsValidBallDropArea(vec2 pos){
    return (
        pos.x > table_left      + ballr &&
        pos.x < table_right     - ballr &&
        pos.y > table_top       + ballr &&
        pos.y < table_bottom    - ballr
    );
}
