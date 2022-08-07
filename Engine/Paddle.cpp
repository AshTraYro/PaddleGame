#include "Paddle.h"
#include "SpriteCodex.h"

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
	SpriteCodex::DrawPaddle(pos, halfWidth, halfHeight, gfx);
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

	if (!isCoolDown)
	{


		if (ball.GetVelocity().y > 0 && GetRect().IsOverlappingWith(ball.GetRect()))
		{
			float ballVelocityValue = (ball.GetVelocity()).GetLength();
			Vec2 FromPaddleToBall = ball.GetBallCenter() - (pos + Vec2(0.0f, 50.0f)); //vector from center of the paddle to the center of the ball
			float FromPaddleToBallValue = FromPaddleToBall.GetLength();
			float newBallVelX = abs(ballVelocityValue * FromPaddleToBall.x / FromPaddleToBallValue);
			float newBallVelY = abs(ballVelocityValue * FromPaddleToBall.y / FromPaddleToBallValue);

			if (ball.GetBallCenter().x - pos.x >= 0 && ball.GetVelocity().x <= 0)
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
			}
			if (ball.GetBallCenter().x - pos.x < 0 && ball.GetVelocity().x >= 0)
			{
				ball.UpdateVelocityX(-newBallVelX);
				ball.UpdateVelocityY(-newBallVelY);
			}
			if (ball.GetBallCenter().x - pos.x > 0 && ball.GetVelocity().x >= 0)
			{
				ball.UpdateVelocityX(newBallVelX);
				ball.UpdateVelocityY(-newBallVelY);			
			}
			if (ball.GetBallCenter().x - pos.x < 0 && ball.GetVelocity().x <= 0)
			{
				ball.UpdateVelocityX(-newBallVelX);
				ball.UpdateVelocityY(-newBallVelY);			
			}
			isCoolDown = true;
			return true;
		}
	}

	return false;
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

void Paddle::ResetCoolDown()
{
	isCoolDown = false;
}
