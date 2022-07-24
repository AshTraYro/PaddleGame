#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
    :
    left(left_in),
    right(right_in),
    top(top_in),
    bottom(bottom_in)

{
}

RectF::RectF(Vec2& topLeft, Vec2& rightBottom)
    :
    RectF(topLeft.x,rightBottom.x,topLeft.y,rightBottom.y)
{
}

RectF::RectF(Vec2& topLeft, float width, float height)
    :
    RectF(topLeft, topLeft+Vec2(width,height))
{
}

RectF RectF::FromCenter(Vec2& center, float halfWidth, float halfHeight)
{
    Vec2 half(halfWidth, halfHeight);
    return RectF(center-half,center+half);
}

bool const RectF::IsOverlappingWith(const RectF& other)
{
    return left<other.right &&
           right>other.left &&
           top<other.bottom &&
           bottom>other.top;
}
