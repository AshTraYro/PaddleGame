#pragma once

#include "RectF.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"

class Brick {
private:
	RectF rect;
	Color color;
	bool destroyed = false;
	int brickHitCount = 0;
	static constexpr float brickPadding = 1.0f;
public:
	Brick() = default;
	Brick(RectF& rect_in, Color color_in);
	void Draw(Graphics& gfx);
	bool CheckBallCollision(Ball& ball);
	void ExecuteBallCollision(Ball& ball);
	Vec2 GetBrickCenter();
	int GetBrickHitCounts();
	bool GetBrickStatus();
	void UpdateBrickStatus(bool new_status);
};