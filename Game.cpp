#include "Game.h"

Game::~Game()
{
}

void Game::Update(double dt)
{
	for (Ball &ball : balls) {
		Vec2d deltaPosition = ball.vel * dt;

		ball.pos += deltaPosition;
		ball.lastDeltaPosition = deltaPosition;

		if (ball.cueball) {
			// remove this part
			ball.vel *= (1.0 + 1.0 * dt);
			ball.vel.rotate(dt);
		} else {
			// leave this part
			ball.vel *= (1.0 - deacceleration * dt);
		}
	}

	if ((HandleWallCollisions() || HandleBallCollisions()) && soundEnabled) {
		screen->MakeBellSound();
	}

	// Update cueball ball pos
	for (Ball &ball : balls) {
		if (ball.cueball) {
			cueBallPosition = ball.pos;
			break;
		}
	}
}

void Game::UpdateScreen()
{
	if (!screen)
		return;

	// Clear
	screen->Clear();

	// Draw table
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if (x < table_x || y < table_y || x >= table_x + table_w || y >= table_y + table_h){
				screen->PlotPixel(x, y, '%', RED);
			}
			else{
				screen->PlotPixel(x, y, ((y + x) % 2 ? '.' : ' '), GRN);
			}
		}
	}

	// Draw balls
	for (Ball &ball : balls) {
		DrawBall(ball);
	}
}

void Game::DrawBall(Ball& ball) 
{
	COLOR base_color = ball.GetColor();

	// same for all balls
	COLOR edge_color = WHT;
	COLOR id_color = WHT; //the number

	double bx = ball.pos.x;
	double by = ball.pos.y;
	double r = ball.radius;
	
	if(ball.cueball){
		screen->DrawSphere(bx, by, r, WHT); // cue ball always white
		screen->DrawCircleOutline(bx, by, r, edge_color);
		return;
	}

	screen->DrawSphere(bx, by, r, base_color);
	screen->DrawCircleOutline(bx, by, r, edge_color);
	screen->PlotPixel(bx, by, ball.id, id_color);

	// switch (ball.type){
	// 	case STRIPED:
	// 		break;
	// 	case OTHER:
	// 		break;
	// 	default:
	// 		break;
	// }
}

void Game::InitDefaultGame()
{
	double s = ((double)table_w / 120.0);

	double r = 3.0 * s;
	double dx = 2.4 * s;
	double dy = 1.0 * s;
	double hub_scalar = 3.7;
	Vec2d white_start(
		(double)table_x + s * 6.0,
		(double)table_y + s * (height / 2)
	);
	Vec2d hub_start(
		(double)table_x + s * width - dx * 3.5 * hub_scalar,
		(double)table_y + s * height / 2
	);

	const Vec2d positions[] = {
		hub_start + hub_scalar * Vec2d(0.0 * dx, 0.0 * dy),
		hub_start + hub_scalar * Vec2d(1.0 * dx, -1.0 * dy),
		hub_start + hub_scalar * Vec2d(1.0 * dx, 1.0 * dy),
		hub_start + hub_scalar * Vec2d(2.0 * dx, -2.0 * dy),
		hub_start + hub_scalar * Vec2d(2.0 * dx, 0.0 * dy),
		hub_start + hub_scalar * Vec2d(2.0 * dx, 2.0 * dy),
		hub_start + hub_scalar * Vec2d(3.0 * dx, -3.0 * dy),
		hub_start + hub_scalar * Vec2d(3.0 * dx, -1.0 * dy),
		hub_start + hub_scalar * Vec2d(3.0 * dx, 1.0 * dy),
		hub_start + hub_scalar * Vec2d(3.0 * dx, 3.0 * dy),
		hub_start + hub_scalar * Vec2d(4.0 * dx, -4.0 * dy),
		hub_start + hub_scalar * Vec2d(4.0 * dx, -2.0 * dy),
		hub_start + hub_scalar * Vec2d(4.0 * dx,  0.0 * dy),
		hub_start + hub_scalar * Vec2d(4.0 * dx,  2.0 * dy),
		hub_start + hub_scalar * Vec2d(4.0 * dx,  4.0 * dy),
	};

	balls.clear();
	for(int i=0; i<1+2+3+4+5; i++){
		balls.push_back(Ball(positions[i].x, positions[i].y, r, '0' + (i % 10), i % 2));
	}

	balls.push_back(Ball(white_start.x, white_start.y, r, ' ', false));
	balls.back().vel = cueVelocity * Vec2d(1.0, 0.0).unit();
	balls.back().cueball = true;
}

bool Game::HandleWallCollisions()
{
	bool result = false;

	for(Ball& ball : balls) {
		if(ball.pos.x - ball.radius < table_x)       { if(ball.cueball) result = true; ball.vel.x *= -1.0; ball.pos.x = table_x + 2.0 * ball.radius - (ball.pos.x - table_x); }
		if(ball.pos.y - ball.radius < table_y)       { if(ball.cueball) result = true; ball.vel.y *= -1.0; ball.pos.y = table_y + 2.0 * ball.radius - (ball.pos.y - table_y); }
		if(ball.pos.x + ball.radius >= table_x + table_w)  { if(ball.cueball) result = true; ball.vel.x *= -1.0; ball.pos.x = table_x + table_w - ((ball.pos.x + 2.0 * ball.radius) - (table_x + table_w)); }
		if(ball.pos.y + ball.radius >= table_y + table_h) { if(ball.cueball) result = true; ball.vel.y *= -1.0; ball.pos.y = table_y + table_h - ((ball.pos.y + 2.0 * ball.radius) - (table_y + table_h)); }
	}
	return result;
}

bool Game::HandleBallCollisions()
{
	bool result = false;

	for (size_t i = 0; i < balls.size(); i++) {
		for (size_t j = i + 1; j < balls.size(); j++) {
			Ball &b1 = balls[i];
			Ball &b2 = balls[j];

			if (b1.CollidesWith(b2)) {
				if (b1.cueball || b2.cueball)
					result = true;

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
				b1.vel = 0.5 * velavg * +collisionDirection + 0.5 * velavg * b1.vel.reflected(mirrorUnitVector).unit();
				b2.vel = 0.5 * velavg * -collisionDirection + 0.5 * velavg * b2.vel.reflected(mirrorUnitVector).unit();

				// only works accurately when moving head on with same velocity or some other symmetric circumstances
				b1.pos += 0.5 * intersectionSize * -collisionDirection.reflected(mirrorUnitVector);
				b2.pos += 0.5 * intersectionSize * +collisionDirection.reflected(mirrorUnitVector);
			}
		}
	}

	return result;
}

Game::Game(int w, int h, ConsolePanel *screen, ConsolePanel *zoomWindow) :
	screen(screen), zoomWindow(zoomWindow), width(w), height(h)
{
	table_x = table_side;
	table_y = table_side;
	table_w = (double)width - 2.0 * table_side;
	table_h = (double)height - 2.0 * table_side;

	InitDefaultGame();
}