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
    for(int i=0; i<6; i++){
        balls.push_back(Ball(2 + i * 8, 2 + i * 6, i * 1.0));
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
                // double distanceTravelled1 = b1.lastDeltaPosition.norm();
                // double distanceTravelled2 = b2.lastDeltaPosition.norm();

                Vec2d mirrorUnitVector = collisionDirection.unit();

                b1.vel.reflect(mirrorUnitVector);
                b2.vel.reflect(mirrorUnitVector);

                // double goBackScale1 = intersectionSize / distanceTravelled1;
                // double goBackScale2 = intersectionSize / distanceTravelled2;

                // b1.pos -= goBackScale1 * b1.lastDeltaPosition + (1.0 - goBackScale1) * b1.lastDeltaPosition.reflected(mirrorUnitVector);
                // b2.pos -= goBackScale2 * b2.lastDeltaPosition + (1.0 - goBackScale2) * b2.lastDeltaPosition.reflected(mirrorUnitVector);
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
