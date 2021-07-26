#include "Game.h"

Game::~Game()
{
}

void Game::KeyPressed(int key) 
{
	double x_move_amount = 0.05;
	double y_move_amount = 0.05;

	if(key == 97 - 'a' + 'a'){
		cue.target.x -= x_move_amount;
	}
	if(key == 97 - 'a' + 'd'){
		cue.target.x += x_move_amount;
	}
	if(key == 97 - 'a' + 'w'){
		cue.target.y -= y_move_amount;
	}
	if(key == 97 - 'a' + 's'){
		cue.target.y += y_move_amount;
	}
	if(key == 97 - 'a' + ' '){
		if(cue.inAction){
			ReleaseCue();
		}
	}
}

void Game::ResetAndActivateCue() 
{
	cue.target = Vec2d(table_x + table_w / 2.0, table_y + table_h / 2.0);
	cue.inAction = true;
}

void Game::ReleaseCue() 
{
	cue.Apply(balls[cueBallIndex]);
	cue.inAction = false;
}

void Game::Update(double dt)
{
	for (Ball &ball : balls) {
		Vec2d deltaPosition = ball.vel * dt;

		ball.pos += deltaPosition;
		ball.lastPositionChange = deltaPosition;

		ball.vel *= (1.0 - deacceleration * dt);
	}

	if ((HandleWallCollisions() || HandleBallCollisions()) && useSounds ) {
		MakeBellSound();
	}

	// activate cue stick if ball has slowed down enough, should be all balls velocities instead
	if(!cue.inAction){
		if(balls[cueBallIndex].vel.norm() < 1.0){
			ResetAndActivateCue();
		}
	}
}

void Game::Draw(int w, int h)
{
	x_scalar = (double)w / game_width;
	y_scalar = (double)h / game_height;

	// Draw table
	for (int y = 0; y < h; y++){
		for (int x = 0; x < w; x++){
			if (x < x_scalar * table_x || y < y_scalar * table_y || x >= x_scalar * (table_x + table_w) || y >= y_scalar * (table_y + table_h)){
				SetPixel(x, y, (y + x) % 2 ? '+' : '-', TABLE_COLOR_PAIR);
			}
			else{
				SetPixel(x, y, ((y + x) % 5 ? ' ' : '.'), PLAYAREA_COLOR_PAIR); 
			}
		}
	}

	// Draw balls
	for (Ball &ball : balls) {
		DrawBall(ball);
	}

	// Draw cue
	if(cue.inAction){
		Ball& cueBall = balls[cueBallIndex];

		double distance = (cue.target - cueBall.pos).norm();
		double angle = 3.14159 + (cue.target - cueBall.pos).angle();
		double stickDistFromBall = (0.2 * distance);

		double cueStartDistance = balls[cueBallIndex].radius + stickDistFromBall;
		double cueEndDistance = cue.lengthOnScreen + cueStartDistance;

		double x1 = x_scalar * (cueBall.pos.x + cueStartDistance * cos(angle));
		double y1 = y_scalar * (cueBall.pos.y + cueStartDistance * sin(angle));
		double x2 = x_scalar * (cueBall.pos.x + cueEndDistance * cos(angle));
		double y2 = y_scalar * (cueBall.pos.y + cueEndDistance * sin(angle));
		
		DrawLine(x1, y1, x2, y2, '#', CUE_COLOR_PAIR);

		SetPixel(x_scalar * cue.target.x, y_scalar * cue.target.y, 'X', CUE_TARGET_COLOR_PAIR);
	}
}

void Game::DrawBall(Ball& ball) 
{
	double bx = x_scalar * ball.pos.x;
	double by = y_scalar * ball.pos.y;
	double r = std::min(x_scalar, y_scalar) * ball.radius;
	
	DrawSphere(bx, by, r, ' ', ball.color);
	DrawCircleOutline(bx, by, r, ball.color2);

	if(!ball.cueball)
		SetPixel(bx, by, ball.id, FG_BG(BALL_ID_COLOR, GET_BG(ball.color)));
}

void Game::InitDefaultGame()
{
	balls.clear();

	double sx = ((double)table_w / 120.0);
	double sy = ((double)table_h / 80.0);

	double r = 5.0 * std::min(sx, sy);
	double dx = 2.4 * sx;
	double dy = 1.0 * sy;
	double triangle_scalar = 3.7;
	
	Vec2d cueball_start(
		(double)table_x + sx * 6.0,
		(double)table_y + sy * (table_w / 2)
	);
	Vec2d triangle_start(
		(double)table_x + table_w - dx * 6.0 * triangle_scalar,
		(double)table_y + table_h / 2
	);

	const Vec2d positions[] = {
		triangle_start + triangle_scalar * Vec2d(0.0 * dx, 0.0 * dy),
		triangle_start + triangle_scalar * Vec2d(1.0 * dx, -1.0 * dy),
		triangle_start + triangle_scalar * Vec2d(1.0 * dx, 1.0 * dy),
		triangle_start + triangle_scalar * Vec2d(2.0 * dx, -2.0 * dy),
		triangle_start + triangle_scalar * Vec2d(2.0 * dx, 0.0 * dy),
		triangle_start + triangle_scalar * Vec2d(2.0 * dx, 2.0 * dy),
		triangle_start + triangle_scalar * Vec2d(3.0 * dx, -3.0 * dy),
		triangle_start + triangle_scalar * Vec2d(3.0 * dx, -1.0 * dy),
		triangle_start + triangle_scalar * Vec2d(3.0 * dx, 1.0 * dy),
		triangle_start + triangle_scalar * Vec2d(3.0 * dx, 3.0 * dy),
		triangle_start + triangle_scalar * Vec2d(4.0 * dx, -4.0 * dy),
		triangle_start + triangle_scalar * Vec2d(4.0 * dx, -2.0 * dy),
		triangle_start + triangle_scalar * Vec2d(4.0 * dx,  0.0 * dy),
		triangle_start + triangle_scalar * Vec2d(4.0 * dx,  2.0 * dy),
		triangle_start + triangle_scalar * Vec2d(4.0 * dx,  4.0 * dy),
	};

	for(int i=0; i<1+2+3+4+5; i++){
		int color 	= FG_BG(COLOR_BLACK, 1 + i % 6);
		int color2 	= FG_BG(COLOR_BLACK, 1 + i % 6);

		if(i == 8){
			color 	= FG_BG(COLOR_WHITE, COLOR_BLACK);
			color2 	= FG_BG(COLOR_WHITE, COLOR_BLACK);
		}

		balls.push_back(Ball(positions[i].x, positions[i].y, r, '0' + (i % 10), i % 2, color, color2));
	}

	// init cueball
	balls.push_back(Ball(cueball_start.x, cueball_start.y, r, ' ', false, FG_BG(COLOR_BLACK, COLOR_WHITE), FG_BG(COLOR_BLACK, COLOR_WHITE)));
	balls.back().cueball = true;
	cueBallIndex = balls.size() - 1;
}

bool Game::CollidesWithWalls(const Ball& ball) const
{
	bool result = false;

	if(ball.pos.x - ball.radius < table_x)       		{ result = true; }
	if(ball.pos.y - ball.radius < table_y)       		{ result = true; }
	if(ball.pos.x + ball.radius >= table_x + table_w)  	{ result = true; }
	if(ball.pos.y + ball.radius >= table_y + table_h) 	{ result = true; }

	return result;
}

bool Game::CollidesWithOtherBalls(const Ball& ball) const
{
	for (size_t j = 0; j < balls.size(); j++) {
		const Ball &b2 = balls[j];
		if(&b2 == &ball)
			continue;

		if(ball.CollidesWith(b2)) {
			return true;
		}
	}

	return false;
}

bool Game::HandleWallCollisions()
{
	bool result = false;

	for(Ball& ball : balls) {
		// add more general linecollision system when adding holes
		//
		// if(CollidesWithLine(borderlines[0])) 
		//   ...

		if(ball.pos.x - ball.radius < table_x)       		{ if(ball.cueball) result = true; ball.vel.x *= -1.0; ball.pos.x = table_x + 2.0 * ball.radius - (ball.pos.x - table_x); }
		if(ball.pos.y - ball.radius < table_y)       		{ if(ball.cueball) result = true; ball.vel.y *= -1.0; ball.pos.y = table_y + 2.0 * ball.radius - (ball.pos.y - table_y); }
		if(ball.pos.x + ball.radius >= table_x + table_w)  	{ if(ball.cueball) result = true; ball.vel.x *= -1.0; ball.pos.x = table_x + table_w - ((ball.pos.x + 2.0 * ball.radius) - (table_x + table_w)); }
		if(ball.pos.y + ball.radius >= table_y + table_h) 	{ if(ball.cueball) result = true; ball.vel.y *= -1.0; ball.pos.y = table_y + table_h - ((ball.pos.y + 2.0 * ball.radius) - (table_y + table_h)); }
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

Game::Game()
{
	InitDefaultGame();
	ResetAndActivateCue();
}

void Game::MoveCue(double dx, double dy) {
	cue.target += Vec2d(dx, dy);
}
