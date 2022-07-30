#pragma once

#include "Vec2.h"

class RectF
{
public:
	float left;
	float right;
	float top;
	float bottom;
public:
	RectF() = default;
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vec2& topLeft, const Vec2& rightBottom);
	RectF(const Vec2& topLeft, float width, float height);
	static RectF FromCenter(const Vec2& center, float halfWidth, float halfHeight);
	bool const IsOverlappingWith(const RectF& other);
	RectF GetExpanded(float offset);


};
