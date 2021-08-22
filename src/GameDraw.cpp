#include "GameDraw.hpp"

void GameDraw::Draw(){
    DrawFunctions::PaintBlankScreen(backgroundColor);

	Terminal::SetDrawColor(holeColor);
    for(Hole& hole : holes){
        DrawHole(hole, '.');
    }

	Terminal::SetDrawColor(ghostColor);
    DrawCueGhosts(cue, '#');

	Terminal::SetDrawColor(lineColor);
    for(Line& line : lines){
        DrawLine(line, ' ');
    }

	Terminal::SetDrawColor(cueColor);
    if(cue.active){
        DrawCue(cue, ' ', ' ');
    }

    Terminal::SetDrawColor(ballColor);
    for(Ball& ball : balls){
        if(ball.active)
            DrawBall(ball, ' ');
    }
}

void GameDraw::DrawBall(double x, double y, double r, char c){
    x = x           * fromMapToScreenScalarX;
    y = y           * fromMapToScreenScalarY;
    double rx = r   * fromMapToScreenScalarX;
    double ry = r   * fromMapToScreenScalarY;

    DrawFunctions::DrawSolidEllipse(x, y, rx, ry, c);
}

void GameDraw::DrawLine(double x1, double y1, double x2, double y2, char c){
    x1 = x1 * fromMapToScreenScalarX;
    y1 = y1 * fromMapToScreenScalarY;
    x2 = x2 * fromMapToScreenScalarX;
    y2 = y2 * fromMapToScreenScalarY;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
}

void GameDraw::DrawBall(const Ball& ball, char c){
    double x = ball.pos.x    * fromMapToScreenScalarX;
    double y = ball.pos.y    * fromMapToScreenScalarY;
    double rx = ball.r       * fromMapToScreenScalarX;
    double ry = ball.r       * fromMapToScreenScalarY;

    DrawFunctions::DrawSolidEllipse(x, y, rx, ry, c);
}

void GameDraw::DrawLine(const Line& line, char c){
    double x1 = line.a.x * fromMapToScreenScalarX;
    double y1 = line.a.y * fromMapToScreenScalarY;
    double x2 = line.b.x * fromMapToScreenScalarX;
    double y2 = line.b.y * fromMapToScreenScalarY;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
}

void GameDraw::DrawHole(const Hole& hole, char c){
    double x1 = hole.pos.x * fromMapToScreenScalarX;
    double y1 = hole.pos.y * fromMapToScreenScalarY;
    double rx = hole.holeRadius * fromMapToScreenScalarX;
    double ry = hole.holeRadius * fromMapToScreenScalarY;

    DrawFunctions::DrawSolidEllipse(x1, y1, rx, ry, c);
}

void GameDraw::DrawCue(const Cue& cue, char c, char x){
    if(!IsCueValid(cue))
        return;

    Ball* ball = &balls[cue.ballIndex];

    vec2 unit = MakeVector(cue.angle, 1.0);
    double distanceFromBall = cue.distanceFromBallMin + (cue.distanceFromBallMax - cue.distanceFromBallMin) * cue.pullScale + ball->r;
    double distanceFromBall2 = distanceFromBall + cue.lengthOnScreen;

    double x1 = (ball->pos + unit * distanceFromBall).x * fromMapToScreenScalarX;
    double y1 = (ball->pos + unit * distanceFromBall).y * fromMapToScreenScalarY;
    double x2 = (ball->pos + unit * distanceFromBall2).x * fromMapToScreenScalarX;
    double y2 = (ball->pos + unit * distanceFromBall2).y * fromMapToScreenScalarY;

    DrawFunctions::DrawLine(x1, y1, x2, y2, c);
}

void GameDraw::DrawCueGhosts(const Cue& cue, char c){
    if(!IsCueValid(cue))
        return;

    Ball startball = balls[cue.ballIndex];
    Ball endball = balls[cue.ballIndex];
    endball.dpos = MakeVector(cue.angle + M_PI, MAX_GHOST_DISTANCE);

    BallBallCollision collision = GetClosestBallBallCollision(endball);
    BallLineCollision collisionline = GetClosestBallLineCollision(endball);

    bool bb_not_bl;

    if(!collision.nocollision && !collisionline.nocollision){
        if(collision.scalarOfDeltatime < collisionline.scalarOfDeltatime){
            endball.pos = collision.pos1;
            bb_not_bl = true;
        }
        else{
            endball.pos = collisionline.pos;
            bb_not_bl = false;
        }
    }
    else if(!collision.nocollision){
        endball.pos = collision.pos1;
        bb_not_bl = true;
    }
    else if(!collisionline.nocollision){
        endball.pos = collisionline.pos;
        bb_not_bl = false;
    }

    DrawBall(endball, c);

    // trace 1
    DrawLine(startball.pos.x, startball.pos.y, endball.pos.x, endball.pos.y, c);

    // trace 2
    if(bb_not_bl){
        vec2 tracer = UnitVector(collision.dpos2) * TRACER_LENGTH;

        Line l;
        l.a = endball.pos;
        l.b = endball.pos + tracer;
        DrawLine(l, c);
    }
    else{
        vec2 tracer = UnitVector(collisionline.dpos) * TRACER_LENGTH;

        Line l;
        l.a = endball.pos;
        l.b = endball.pos + tracer;
        DrawLine(l, c);
    }
}
