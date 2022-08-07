/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ball(Vec2(400.0f,300.0f), Vec2(-300.0f, -300.0f)),
	gameBoundry(0.0f+wallThickness+wallPadding,float(gfx.ScreenWidth)-wallThickness-wallPadding,0.0f+wallThickness+wallPadding,float(gfx.ScreenHeight)),
	pad(Vec2(400.0f,550),70.0f,15.0f),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav")


{
	Color bricksColor[nBrickRows] = { Colors::Blue,Colors::Green,Colors::Yellow,Colors::Magenta };
	Vec2 topLeft = Vec2(40.0f, 40.0f);
	int i = 0;
	for (int y = 0; y < nBrickRows; y++)
	{
		Color c = bricksColor[y];
		for (int x = 0; x < nBrickColumns; x++)
		{
			bricks[i] = Brick(RectF(Vec2(topLeft + Vec2(x * brickWidth, y * brickHeight)), brickWidth, brickHeight),c);
			i++;
		}	
	}

	wallLeft = RectF(wallPadding, wallThickness+wallPadding, wallPadding, float(gfx.ScreenHeight-wallPadding));
	wallRight = RectF(float(gfx.ScreenWidth) - wallThickness-wallPadding, float(gfx.ScreenWidth)-wallPadding, wallPadding, float(gfx.ScreenHeight)-wallPadding);
	wallTop = RectF(wallThickness+wallPadding, float(gfx.ScreenWidth) - wallThickness-wallPadding, wallPadding, wallThickness+wallPadding);

}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{


		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	
	ball.Update(dt);
	pad.Update(wnd.kbd, dt);
	pad.DoWallCollission(gameBoundry);
	if (pad.DoBallCollission(ball))
	{
		soundPad.Play();
	}

	if (ball.DoWallCollission(gameBoundry))
	{
		pad.ResetCoolDown();
		soundPad.Play();
	}
	bool collisionHappend = false;
	float DistFromBallCenterToBrickCenterSq;
	int curIndexOfBrickToCollide;
	
	for (int i=0;i<nBricks;i++)
	{
		if (bricks[i].CheckBallCollision(ball))
		{
			if (collisionHappend)
			{
				float newDistFromBallCenterToBrickCenterSq = (bricks[i].GetBrickCenter() - ball.GetBallCenter()).GetLengthSq();
				if (newDistFromBallCenterToBrickCenterSq < DistFromBallCenterToBrickCenterSq)
				{
					DistFromBallCenterToBrickCenterSq = newDistFromBallCenterToBrickCenterSq;
					curIndexOfBrickToCollide = i;
				}
			}
			else
			{
				DistFromBallCenterToBrickCenterSq = (bricks[i].GetBrickCenter() - ball.GetBallCenter()).GetLengthSq();
				curIndexOfBrickToCollide = i;
				collisionHappend = true;
			}
		}
	}

	if (collisionHappend)
	{
		pad.ResetCoolDown();
		bricks[curIndexOfBrickToCollide].ExecuteBallCollision(ball);
		soundBrick.Play();
	}
}

void Game::ComposeFrame()
{
	ball.Draw(gfx);
	pad.Draw(gfx);
	for (Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	gfx.DrawRect(wallLeft, Colors::LightGray);
	gfx.DrawRect(wallRight, Colors::LightGray);
	gfx.DrawRect(wallTop, Colors::LightGray);
}
