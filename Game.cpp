#include "Game.h"

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
        if(ball.white){
            ball.vel *= (1.0 + 2.0 * dt);
            ball.vel.rotate(dt);
        }
        else{
            ball.vel *= (1.0 - deacceleration * dt);
        }
    }

    HandleWallCollisions();
    HandleBallCollisions();
}

void Game::UpdateScreen() 
{
    if(!screen)
        return;

    screen->Clear();

    for(Ball& ball : balls){
        if(ball.white){
            screen->DrawSphere(ball.pos.x, ball.pos.y, ball.radius);
        }
        else if(ball.striped){
            screen->DrawHollowSphere(ball.pos.x, ball.pos.y, ball.radius, nameAreaRadius / 5.0);
            for(int x = ball.pos.x - ball.radius; x <= ball.pos.x + ball.radius; x++)
                screen->PlotPixel(x, ball.pos.y, ' ');
            screen->PlotPixel(ball.pos.x, ball.pos.y, ball.name);
        }
        else{
            screen->DrawHollowSphere(ball.pos.x, ball.pos.y, ball.radius, nameAreaRadius);
            screen->PlotPixel(ball.pos.x, ball.pos.y, ball.name);
        }
    }
}

void Game::InitDefaultGame() 
{
    const Vec2d white_start(6, height / 2);
    const Vec2d hub_start(40, height / 2);
    const double hub_scalar = 2.7;
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
        balls.push_back(Ball(positions[i].x, positions[i].y, defaultBallRadius, '0' + (i % 10), i % 2));
    }

    balls.push_back(Ball(white_start.x, white_start.y, defaultBallRadius, ' ', false));
    balls.back().vel = cueVelocity * Vec2d(1.0, 0.0).unit();
    balls.back().white = true;
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

                double velTotal = b1.vel.norm() + b2.vel.norm();
                // double velDifferenceScale1 = b1.vel.norm() / velTotal;
                // double velDifferenceScale2 = 1.0 - velDifferenceScale1;

                double velavg = 0.5 * velTotal;

                // needs trasferrance of energy, currently will never lose/gain velocity to other balls in collision
                // or maybe not
                b1.vel = 0.5 * velavg *  collisionDirection + 0.5 * velavg * b1.vel.reflected(mirrorUnitVector).unit();
                b2.vel = 0.5 * velavg * -collisionDirection + 0.5 * velavg * b2.vel.reflected(mirrorUnitVector).unit();

                // only works accurately when moving head on with same velocity or some other symmetric circumstances
                b1.pos += 0.5 * intersectionSize * -collisionDirection.reflected(mirrorUnitVector);
                b2.pos += 0.5 * intersectionSize *  collisionDirection.reflected(mirrorUnitVector);
            }
        }
    }
}

Ball::Ball(double x, double y, double radius, char name, bool striped) :
    pos(Vec2d(x, y)), vel(Vec2d(0, 0)), radius(radius), lastDeltaPosition(Vec2d(0, 0)), white(false), name(name), striped(striped)
{
}

bool Ball::CollidesWith(const Ball& other) const
{
    return (other.pos - pos).norm() <= other.radius + radius;
}

Game::Game(Window* screen) :
    screen(screen), width(screen->GetWidth()), height(screen->GetHeight())
{
    InitDefaultGame();
}

Ball::Ball() 
{
}
