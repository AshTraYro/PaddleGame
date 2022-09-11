#include "Beveler.h"

Beveler::Beveler(Color baseColor)
{
	SetBaseColor(baseColor);
}

void Beveler::SetBaseColor(Color color_in)
{
	color_in = baseColor;
	topColor = Color(
		int(float(baseColor.GetR()) * topFactor), 
		int(float(baseColor.GetG()) * topFactor), 
		int(float(baseColor.GetB()) * topFactor));

	bottomColor = Color(
		int(float(baseColor.GetR()) * bottomFactor),
		int(float(baseColor.GetG()) * bottomFactor),
		int(float(baseColor.GetB()) * bottomFactor));

	leftColor = Color(
		int(float(baseColor.GetR()) * leftFactor),
		int(float(baseColor.GetG()) * leftFactor),
		int(float(baseColor.GetB()) * leftFactor));

	rightColor = Color(
		int(float(baseColor.GetR()) * rightFactor),
		int(float(baseColor.GetG()) * rightFactor),
		int(float(baseColor.GetB()) * rightFactor));

}

void Beveler::DrawOuterBevel(const RectF& rect, int size, Graphics& gfx)
{

	int left = int(rect.left);
	int right = int(rect.right);
	int top = int(rect.top);
	int bottom = int(rect.bottom);


	//left side of the Bevler
	gfx.DrawIsoRightTriBL(left, top, size, leftColor);
	gfx.DrawRect(left, top + size, right, bottom - size, leftColor);
	gfx.DrawIsoRightTriUL(left, top, size, leftColor);
	//top side of the Bevler
	gfx.DrawIsoRightTriUR(left, top, size, topColor);
	gfx.DrawRect(left + size, top, right - size, top + size, topColor);
	gfx.DrawIsoRightTriUL(right - size, top, size, topColor);
	//right side of the Bevler
	gfx.DrawIsoRightTriBR(right - size, top, size, rightColor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, rightColor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, rightColor);
	//bottom side of the Bevler
	gfx.DrawIsoRightTriBR(left, bottom - size, size, bottomColor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, bottomColor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, bottomColor);
}

void Beveler::DrawInnerBevel(const RectF& rect, int size, Graphics& gfx)
{
	int left = int(rect.left);
	int right = int(rect.right);
	int top = int(rect.top);
	int bottom = int(rect.bottom);


	//left side of the Bevler color rightColor
	gfx.DrawIsoRightTriBL(left, top, size, rightColor);
	gfx.DrawRect(left, top + size, right, bottom - size, rightColor);
	gfx.DrawIsoRightTriUL(left, top, size, rightColor);
	//top side of the Bevler color bottomColor
	gfx.DrawIsoRightTriUR(left, top, size, bottomColor);
	gfx.DrawRect(left + size, top, right - size, top + size, bottomColor);
	gfx.DrawIsoRightTriUL(right - size, top, size, bottomColor);
	//right side of the Bevler color leftColor
	gfx.DrawIsoRightTriBR(right - size, top, size, leftColor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, leftColor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, leftColor);
	//bottom side of the Bevler color topColor
	gfx.DrawIsoRightTriBR(left, bottom - size, size, topColor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, topColor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, topColor);
}

void Beveler::DrawBevelerBrick(RectF& rect, int bevelsize, Graphics& gfx)
{
	DrawOuterBevel(rect, bevelsize, gfx);
	gfx.DrawRect(rect.GetExpanded(-float(bevelsize)), baseColor);
}

void Beveler::DrawBevelerFrame(RectF& rect, int bevelsize, Graphics& gfx)
{
	DrawOuterBevel(rect, bevelsize, gfx);
	DrawInnerBevel(rect.GetExpanded(-float(bevelsize)), bevelsize, gfx);
}
