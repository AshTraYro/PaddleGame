#pragma once

#include "Graphics.h"
#include "RectF.h"


class Beveler
{
public:
	Beveler(Color baseColor);
	Beveler() = default;
	void SetBaseColor(Color color_in);
	void DrawInnerBevel(const RectF& rect, int size, Graphics& gfx);
	void DrawOuterBevel(const RectF& rect, int size, Graphics& gfx);
	void DrawBevelerBrick(RectF& rect, int bevelsize, Graphics& gfx);
	void DrawBevelerFrame(RectF& rect, int bevelsize, Graphics& gfx);
private:
	static constexpr float leftFactor = 1.10f;
	static constexpr float topFactor = 0.93f;
	static constexpr float bottomFactor = 0.80f;
	static constexpr float rightFactor = 0.65f;
	Color baseColor;
	Color topColor;
	Color bottomColor;
	Color leftColor;
	Color rightColor;

};
