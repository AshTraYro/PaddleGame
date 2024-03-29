/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Ball.h"
#include "FrameTimer.h"
#include "Paddle.h"
#include "Sound.h"
#include "Brick.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	void ResetBall();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr float wallThickness = 20;
	static constexpr float wallPadding = 10;
	
	RectF wallLeft;
	RectF wallRight;
	RectF wallTop;
	RectF wallBottom;
	RectF background;
	bool isNotGameOver = true;
	static constexpr int nBrickColumns = 10;
	static constexpr int nBrickRows = 4;
	static constexpr int nBricks = nBrickColumns * nBrickRows;
	static constexpr float brickWidth = 60.0f;
	static constexpr float brickHeight = 30.0f;
	Color bricksColor[nBrickRows] = { {230,0,0},{0,230,0},{230,230,0},{230,0,230} };
	Ball ball;
	FrameTimer ft;
	RectF gameBoundry;
	Paddle pad;
	Sound soundPad;
	Sound soundBrick;
	Brick bricks[int(nBricks)];
	/********************************/
};