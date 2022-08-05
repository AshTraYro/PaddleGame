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
		float ballVelocityValue = (ball.GetVelocity()).GetLength();
		Vec2 FromPaddleToBall = ball.GetBallCenter() - pos; //Value of vector from center of the paddle to the center of the ball
		float FromPaddleToBallValue = FromPaddleToBall.GetLength();
		float newBallVelX = abs(ballVelocityValue * FromPaddleToBall.x / FromPaddleToBallValue);
		float newBallVelY = abs(ballVelocityValue * FromPaddleToBall.y / FromPaddleToBallValue);
		
		if (ball.GetBallCenter().x - pos.x >= 0 && ball.GetVelocity().x<=0)
		{
			
			if (ball.GetBallCenter().x == pos.x)
			{
				ball.UpdateVelocityX(0);
				ball.UpdateVelocityY(-ballVelocityValue);
			}
			else
			{
				ball.UpdateVelocityX(newBallVelX);
				ball.UpdateVelocityY(-newBallVelY);
			}
			
			return true;
		}
		else if (ball.GetBallCenter().x - pos.x < 0 && ball.GetVelocity().x >= 0)
		{
			
			ball.UpdateVelocityX(-newBallVelX);
			ball.UpdateVelocityY(-newBallVelY);
			
			return true;
		}
		else if (ball.GetBallCenter().x - pos.x > 0 && ball.GetVelocity().x >= 0)
		{

				ball.UpdateVelocityX(newBallVelX);
				ball.UpdateVelocityY(-newBallVelY);

			return true;
		}
		else if (ball.GetBallCenter().x - pos.x < 0 && ball.GetVelocity().x <= 0)
		{

			ball.UpdateVelocityX(-newBallVelX);
			ball.UpdateVelocityY(-newBallVelY);

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
