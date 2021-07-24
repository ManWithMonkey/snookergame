#include "Game.h"

Game::Game(int w, int h) :
    width(w), height(h), screen(width, height), balls(0)
{
    InitDefaultGame();
}

Game::Game() :
    width(defaultWidth), height(defaultHeight), screen(defaultWidth, defaultHeight), balls(0)
{
    InitDefaultGame();
}

Game::~Game() 
{
}

void Game::Update(double dt) 
{
    for(Ball& ball : balls){
        Vec2d deltaPosition = ball.vel * dt;

        ball.pos                += deltaPosition;
        ball.lastDeltaPosition  =  deltaPosition;

        // deacceleration
        ball.vel *= (1.f - deacceleration * dt);
    }

    HandleWallCollisions();
    HandleBallCollisions();
}

void Game::Draw() 
{
    screen.Clear();
    DrawGame();
    screen.Draw();
}

void Game::DrawTestLuminosity() 
{
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            screen.PlotPixel(x, y, (double)(width - x) / (double)width);
        }
    }
}

void Game::InitDefaultGame() 
{
    auto _randScalar = []() -> double {
        return 2.0 * (double)(rand()) / (double)RAND_MAX - 1.0;
    };

    const Vec2d white_start(4, 25);
    const Vec2d hub_start(55, 25);
    const double hub_scalar = 3.f;
    const double dx = 2;
    const double dy = 1;

    const Vec2d positions[] = {
        hub_start + hub_scalar * Vec2d(0.0 * dx,  0.0 * dy),
        hub_start + hub_scalar * Vec2d(1.0 * dx, -1.0 * dy),
        hub_start + hub_scalar * Vec2d(1.0 * dx,  1.0 * dy),
        hub_start + hub_scalar * Vec2d(2.0 * dx, -2.0 * dy),
        hub_start + hub_scalar * Vec2d(2.0 * dx,  0.0 * dy),
        hub_start + hub_scalar * Vec2d(2.0 * dx,  2.0 * dy),
        hub_start + hub_scalar * Vec2d(3.0 * dx, -3.0 * dy),
        hub_start + hub_scalar * Vec2d(3.0 * dx, -1.0 * dy),
        hub_start + hub_scalar * Vec2d(3.0 * dx,  1.0 * dy),
        hub_start + hub_scalar * Vec2d(3.0 * dx,  3.0 * dy),
        hub_start + hub_scalar * Vec2d(4.0 * dx, -4.0 * dy),
        hub_start + hub_scalar * Vec2d(4.0 * dx, -2.0 * dy),
        hub_start + hub_scalar * Vec2d(4.0 * dx,  0.0 * dy),
        hub_start + hub_scalar * Vec2d(4.0 * dx,  2.0 * dy),
        hub_start + hub_scalar * Vec2d(4.0 * dx,  4.0 * dy)
    };

    balls.clear();
    for(int i=0; i<1+2+3+4+5; i++){
        balls.push_back(Ball(positions[i].x, positions[i].y, defaultBallRadius));
    }

    balls.push_back(Ball(white_start.x, white_start.y, defaultBallRadius));
    balls.back().vel = cueVelocity * Vec2d(1, 0);
}

void Game::DrawSphere(double x, double y, double r) 
{
    double cx = (int)(x);
    double cy = (int)(y);

    for(double ix = -r; ix <= r; ix += 1.0){
        for(double iy = -r; iy <= r; iy += 1.0){

            double distance = std::hypot(cx + ix - x, cy + iy - y);
            double luminosity = 1.0 - distance / r;
            
            // screen.PlotPixel(ix, iy, luminosity);
            screen.PlotPixelIfBrighter(cx + ix, cy + iy, luminosity);
        }
    }
}

void Game::DrawGame() 
{
    for(Ball& ball : balls){
        DrawSphere(ball.pos.x, ball.pos.y, ball.radius);
    }
}

void Game::HandleWallCollisions() 
{
    for(Ball& ball : balls){
        if(ball.pos.x - ball.radius < 0)         { ball.vel.x *= -1.0; ball.pos.x = 2.0 * ball.radius - ball.pos.x; }
        if(ball.pos.y - ball.radius < 0)         { ball.vel.y *= -1.0; ball.pos.y = 2.0 * ball.radius - ball.pos.y; }
        if(ball.pos.x + ball.radius >= width)    { ball.vel.x *= -1.0; ball.pos.x = width - ((ball.pos.x + 2.0 * ball.radius) - width); }
        if(ball.pos.y + ball.radius >= height)   { ball.vel.y *= -1.0; ball.pos.y = height - ((ball.pos.y + 2.0 * ball.radius) - height); }
    }
}

void Game::HandleBallCollisions() 
{
    for(int i=0; i<balls.size(); i++){
        for(int j=i+1; j<balls.size(); j++){
            Ball& b1 = balls[i];
            Ball& b2 = balls[j];

            if(b1.CollidesWith(b2)){
                double distance = (b1.pos - b2.pos).norm();
                Vec2d collisionDirection = (b1.pos - b2.pos).unit();

                double intersectionSize = (b1.radius + b2.radius) - distance;

                Vec2d mirrorUnitVector = collisionDirection.unit();

                // needs trasferrance of energy, currently will never lose/gain velocity to other balls in collision
                b1.vel.reflect(mirrorUnitVector);
                b2.vel.reflect(mirrorUnitVector);

                // only works accurately when moving head on with same velocity or some other symmetric circumstances
                b1.pos += 0.5 * intersectionSize * b1.lastDeltaPosition.reflected(mirrorUnitVector);
                b2.pos += 0.5 * intersectionSize * b2.lastDeltaPosition.reflected(mirrorUnitVector);
            }
        }
    }
}

Ball::Ball(double x, double y, double radius) :
    pos(Vec2d(x, y)), vel(Vec2d(0, 0)), radius(radius), lastDeltaPosition(Vec2d(0, 0))
{
}

bool Ball::CollidesWith(const Ball& other) const
{
    return (other.pos - pos).norm() <= other.radius + radius;
}

Ball::Ball() 
{
    
}
