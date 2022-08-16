#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(Vec2& pos_in, Vec2& vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

bool Ball::DoWallCollission(const RectF& wall)
{
	const RectF rect = GetRect();
	bool collided = false;
	if (rect.left < wall.left)
	{
		pos.x += wall.left - rect.left;
		ReboundX();
		collided = true;
	}
	else if (rect.right > wall.right)
	{
		pos.x -= rect.right - wall.right;
		ReboundX();
		collided = true;
	}

	if (rect.top < wall.top)
	{
		pos.y += wall.top-rect.top;
		ReboundY();
		collided = true;
	}
	else if (rect.bottom > wall.bottom)
	{
		pos.y -= rect.bottom - wall.bottom;
		collided = true;
		isGameOver = true;
	}

	return collided;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

RectF Ball::GetRect()
{
	return RectF::FromCenter(pos,radius,radius);
}

Vec2 Ball::GetVelocity()
{
	return vel;
}

Vec2 Ball::GetBallCenter()
{
	return pos;
}

void Ball::UpdateVelocity(Vec2 vel_new)
{
	vel = vel_new;
}

void Ball::UpdateVelocityX(float vel_x)
{
	vel.x = vel_x;
}

void Ball::UpdateVelocityY(float vel_y)
{
	vel.y = vel_y;
}

bool Ball::GetGameStatus()
{
	return isGameOver;
}
