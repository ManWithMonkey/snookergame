#include "Game.h"

Game::Game(int w, int h) 
{
    width = w;
    height = h;
    screen = Console(w, h);

    InitDefaultGame();
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

    balls.clear();
    for(int i=0; i<5; i++){
        balls.push_back(Ball(2 + i * 4, 2 + i * 4, i * 1.0));
        balls.back().vel = 100.0 * Vec2d(_randScalar(), _randScalar());
    }
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
    // DrawTestLuminosity();
}

void Game::HandleWallCollisions() 
{
    for(Ball& ball : balls){
        if(ball.pos.x - ballRadius < 0)         { ball.vel.x *= -1.0; ball.pos.x = 2.0 * ballRadius - ball.pos.x; }
        if(ball.pos.y - ballRadius < 0)         { ball.vel.y *= -1.0; ball.pos.y = 2.0 * ballRadius - ball.pos.y; }
        if(ball.pos.x + ballRadius >= width)    { ball.vel.x *= -1.0; ball.pos.x = width - ((ball.pos.x + 2.0 * ballRadius) - width); }
        if(ball.pos.y + ballRadius >= height)   { ball.vel.y *= -1.0; ball.pos.y = height - ((ball.pos.y + 2.0 * ballRadius) - height); }
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
                Vec2d collisionDir = (b1.pos - b2.pos).unit();

                Vec2d mirrorUnit = collisionDir.unit();

                b1.vel.reflect(mirrorUnit);
                b2.vel.reflect(mirrorUnit);

                b1.pos -= 0.5 * b1.lastDeltaPosition + 0.5 * b1.lastDeltaPosition.reflected(mirrorUnit);
                b2.pos -= 0.5 * b2.lastDeltaPosition + 0.5 * b2.lastDeltaPosition.reflected(mirrorUnit);
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
