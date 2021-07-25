#include "Game.h"

Game::~Game()
{
}

void Game::KeyPressed(int key) 
{
	if(key == 'a'){
		cue.angle += 0.2;
	}
	if(key == 'd'){
		cue.angle -= 0.2;
	}
	if(key == 'w'){
		DragCue(-1.75);
	}
	if(key == 's'){
		DragCue(1.75);
	}
	if(key == ' '){
		if(!cue.beingDragged){
			ResetAndActivateCue();
		}
		else{
			ReleaseCue();
		}
	}
}

void Game::DragCue(double amount) 
{
	cue.strength += amount;
	if(cue.strength < 5.0)
		cue.strength = 5.0;

	cue.beingDragged = true;
}

void Game::ResetAndActivateCue() 
{
	cue.strength = 5.0;
	cue.angle = 3.14159;

	cue.beingDragged = true;
}

void Game::ReleaseCue() 
{
	cue.beingDragged = false;
	balls.back().vel = cueMultiplier * cue.strength * Vec2d(1.0, 0.0).rotated(3.14159 + cue.angle);
}

void Game::Update(double dt)
{
	// std::cout << "Updating...\n";
	
	for (Ball &ball : balls) {
		Vec2d deltaPosition = ball.vel * dt;

		ball.pos += deltaPosition;
		ball.lastDeltaPosition = deltaPosition;

        if(ball.cueball){
            // remove this part
            ball.vel *= (1.0 + 1.5 * dt);
            ball.vel *= (1.0 + 1.0 * dt);
            ball.vel.rotate(dt);
        }
        else{
			ball.vel *= (1.0 - deacceleration * dt);
        }
	}

	if ((HandleWallCollisions() || HandleBallCollisions()) ) {
		// screen->MakeBellSound();
	}

	// Update cueball ball pos and cue pos
	for (Ball &ball : balls) {
		if (ball.cueball) {
			cueBallPosition = ball.pos;
			cue.x = ball.pos.x;
			cue.y = ball.pos.y;
			cueBallVel = ball.vel.norm();
			break;
		}
	}

	// cue logic
	if(!cue.beingDragged){
		if(cueBallVel < 1.0){
			ResetAndActivateCue();
		}
	}
}

void Game::Draw()
{
	// Draw table
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if (x < table_x || y < table_y || x >= table_x + table_w || y >= table_y + table_h){
				SetPixel(game_x + x, game_y + y, '#');
			}
			else{
				SetPixel(game_x + x, game_y + y, ((y + x) % 2 ? '.' : ' '));
			}
		}
	}

	// Draw balls
	for (Ball &ball : balls) {
		DrawBall(ball);
	}

	// Draw cue
	if(cue.beingDragged){
		double cueStrengthDrawScale = 1.0;

		double cueStartDistance = ballRadius + cueStrengthDrawScale * cue.strength;
		double cueEndDistance = cue.lengthOnScreen + cueStartDistance;

		double x1 = cue.x + cueStartDistance * cos(cue.angle);
		double y1 = cue.y + cueStartDistance * sin(cue.angle);
		double x2 = cue.x + cueEndDistance * cos(cue.angle);
		double y2 = cue.y + cueEndDistance * sin(cue.angle);
		DrawLine(x1, y1, x2, y2, '#', COLOR_WHITE);
	}
}

static int yes = 0;

void Game::DrawBall(Ball& ball) 
{
	double bx = ball.pos.x;
	double by = ball.pos.y;
	double r = ball.radius;
	
	if(ball.cueball){
		// DrawSphere(bx, by, r, WHT); // cue ball always white
		DrawCircleOutline(bx, by, r, COLOR_WHITE);
		return;
	}

	// DrawSphere(bx, by, r);
	DrawCircleOutline(bx, by, r, (yes++) % 8);
	SetPixel(bx, by, ball.id);

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
	double sx = ((double)table_w / 120.0);
	double sy = ((double)table_h / 80.0);

	double r = ballRadius = 3.0 * sx;
	double dx = 2.4 * sx;
	double dy = 1.0 * sy;
	double hub_scalar = 3.7;
	Vec2d white_start(
		(double)table_x + sx * 6.0,
		(double)table_y + sy * (table_w / 2)
	);
	Vec2d hub_start(
		(double)table_x + table_w - dx * 6.0 * hub_scalar,
		(double)table_y + table_h / 2
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
	balls.back().cueball = true;

	//remove this
    balls.back().vel = 100.0 * Vec2d(1.0, 0.0).unit();
}

bool Game::HandleWallCollisions()
{
	bool result = false;

	for(Ball& ball : balls) {
		// add more general linecollision system when adding holes
		//
		// if(CollidesWithLine(borderlines[0])) 
		//   ...

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

Game::Game(int x, int y, int w, int h) :
	game_x(x), game_y(y), width(w), height(h)
{
	table_x = table_side_x;
	table_y = table_side_y;
	table_w = (double)width - 2.0 * table_side_x;
	table_h = (double)height - 2.0 * table_side_y;

	InitDefaultGame();
	ResetAndActivateCue();
}
