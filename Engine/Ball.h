#pragma once

#include "Graphics.h"
class Ball 
{
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
	bool isGameOver = false;
public:
	Ball(Vec2& pos_in, Vec2& vel_in);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool DoWallCollission(const RectF& wall);
	void ReboundX();
	void ReboundY();
	RectF GetRect();
	Vec2 GetVelocity();
	Vec2 GetBallCenter();
	void UpdateVelocity(Vec2 vel_new);
	void UpdateVelocityX(float vel_x);
	void UpdateVelocityY(float vel_y);
	bool GetGameStatus();
};

