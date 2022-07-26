#pragma once

#include "Graphics.h"
class Ball 
{
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
public:
	Ball(Vec2& pos_in, Vec2& vel_in);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool DoWallCollission(const RectF& wall);
	void ReboundX();
	void ReboundY();
	RectF GetRect();
};

