#include "Paddle.h"

Paddle::Paddle(Vec2& pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight (halfHeight_in)

{
}

RectF Paddle::GetRect()
{
	return RectF::FromCenter(pos,halfWidth,halfHeight);
}

void Paddle::Draw(Graphics& gfx)
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, c);
}

void Paddle::Update(Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x-=speed*dt;
	}

	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

bool Paddle::DoBallCollission(Ball& ball)
{
	if (ball.GetVelocity().y>0 && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		if (ball.GetBallCenter().x - pos.x > 0 && ball.GetVelocity().x<0)
		{
			ball.ReboundX();
			ball.ReboundY();
			if (ball.GetBallCenter().y == pos.y)
			{
				ball.UpdateVelocityX(0);
			}
			else
			{
				Vec2 vect = ball.GetBallCenter() + (ball.GetBallCenter() - pos);
				ball.UpdateVelocityX(abs(vect.x * ball.GetVelocity().y / vect.y));
			}
			
			return true;
		}
		else if (ball.GetBallCenter().x - pos.x < 0 && ball.GetVelocity().x > 0)
		{
			ball.ReboundX();
			ball.ReboundY();
			if (ball.GetBallCenter().y == pos.y)
			{
				ball.UpdateVelocityX(0);
			}
			else
			{
				Vec2 vect = ball.GetBallCenter() + (ball.GetBallCenter() - pos);
				ball.UpdateVelocityX(-abs(vect.x * ball.GetVelocity().y / vect.y));
			}
			return true;
		}
		else
		{
			ball.ReboundY();
			if (ball.GetBallCenter().y == pos.y)
			{
				ball.UpdateVelocityX(0);
			}
			else
			{
				if (ball.GetVelocity().x > 0)
				{
					Vec2 vect = ball.GetBallCenter() + (ball.GetBallCenter() - pos);
					ball.UpdateVelocityX(abs(vect.x * ball.GetVelocity().y / vect.y));
				}
				else
				{
					Vec2 vect = ball.GetBallCenter() + (ball.GetBallCenter() - pos);
					ball.UpdateVelocityX(-abs(vect.x * ball.GetVelocity().y / vect.y));
				}
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}

void Paddle::DoWallCollission(RectF& walls)
{
	RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}

}
