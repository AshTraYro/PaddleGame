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
	RectF(Vec2& topLeft, Vec2& rightBottom);
	RectF(Vec2& topLeft, float width, float height);
	static RectF FromCenter(Vec2& center, float halfWidth, float halfHeight);
	bool const IsOverlappingWith(const RectF& other);


};
