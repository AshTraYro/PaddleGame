#include "Brick.h"
#include <assert.h>
#include <cmath>

Brick::Brick(RectF& rect_in, Color color_in)
	:
	rect(rect_in),
	bev(color_in)
{
}

void Brick::Draw(Graphics& gfx)
{
	if (destroyed == false)
	{
		bev.DrawBevelerBrick(rect.GetExpanded(-brickPadding), bevelBrickSize, gfx);
		//gfx.DrawRect(rect.GetExpanded(-brickPadding), c);
	}
}

bool Brick::CheckBallCollision(Ball& ball)
{
	return !destroyed && rect.IsOverlappingWith(ball.GetRect());
}

void Brick::ExecuteBallCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));
		if (std::signbit(ball.GetVelocity().x) == std::signbit((ball.GetBallCenter() - GetBrickCenter()).x))
		{
			ball.ReboundY();
		}
		else if (ball.GetBallCenter().x >= rect.left && ball.GetBallCenter().x <= rect.right)
		{
			ball.ReboundY();		
		}
		else
		{
			ball.ReboundX();
		}
		if (brickHitCount == 0)
		{
			destroyed = true;
		}
		brickHitCount++;
}

Vec2 Brick::GetBrickCenter()
{
	return rect.GetRectCenter();
}

int Brick::GetBrickHitCounts()
{
	return brickHitCount;
}

bool Brick::GetBrickStatus()
{
	return destroyed;
}

void Brick::UpdateBrickStatus(bool new_status)
{
	destroyed = new_status;
}

