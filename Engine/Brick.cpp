#include "Brick.h"

Brick::Brick(RectF& rect_in, Color color_in)
	:
	rect(rect_in),
	color(color_in)
{
}

void Brick::Draw(Graphics& gfx)
{
	if (destroyed == false)
	{
		gfx.DrawRect(rect.GetExpanded(-brickPadding), color);
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!destroyed && rect.IsOverlappingWith(ball.GetRect()))

	{
		if (ball.GetBallCenter().x > rect.left && ball.GetBallCenter().x < rect.right)
		{
			ball.ReboundY();
			destroyed = true;
			return true;
		}
		else
		{
			ball.ReboundX();
			destroyed = true;
			return true;
		}
	}

	else
	{
		return false;
	}
}
