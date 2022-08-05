#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Ball.h"

class Paddle
{
private:
	Vec2 pos;
	float halfWidth;
	float halfHeight;
	float speed=500.0f;
	Color c = Colors::Green;
	float wingWidth = 20.0f;
	Color wingColor = Colors::Red;
public:
	Paddle(Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	RectF GetRect();
	void Draw(Graphics& gfx);
	void Update(Keyboard& kbd, float dt);
	bool DoBallCollission(Ball& ball);
	void DoWallCollission(RectF& walls);
};