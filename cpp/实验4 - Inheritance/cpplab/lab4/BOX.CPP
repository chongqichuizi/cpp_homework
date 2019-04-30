#include "box.h"
#include<iostream>
// Your implementation of BoxShape should be placed in this file
BoxShape::BoxShape(SimpleWindow &Window,
	const Position &Center, const color &c, float w,
	float h,float o) : Shape(Window, Center, c),
	Width(w), Height(h) ,Offset(o){
	cout << "Constructor BoxShape called" << endl;
}

BoxShape::BoxShape(SimpleWindow &Window,
	float XPosition, float YPosition,
	const color &c, float w, float h,float o) : Shape(Window,
		Position(XPosition, YPosition), c),
	Width(w), Height(h) , Offset(o){
	cout << "Constructor BoxShape called" << endl;
}
float BoxShape::GetWidth() const {
	return Width;
}

float BoxShape::GetHeight() const {
	return Height;
}

void BoxShape::GetSize(float &W, float &H) const {
	W = Width;
	H = Height;
	return;
}

void BoxShape::Draw()
{
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();

	const Position UpperLeft = Center + Position(-.5f * Width, -.5f * Height);
	const Position LowerRight = Center + Position(.5f * Width, .5f * Height);

	GetWindow().RenderRectangle(UpperLeft, LowerRight, GetColor(), false);

	return;
}

void BoxShape::SetSize(float W, float H)
{
	Width = W;
	Height = H;
	return;
}

void BoxShape::Erase()
{
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();

	const Position UpperLeft = Center + Position(-.5f * Width+Offset, -.5f * Height+Offset);
	const Position LowerRight = Center + Position(.5f * Width-Offset, .5f * Height-Offset);

	GetWindow().RenderRectangle(UpperLeft, LowerRight, White, false);
	

	return;
}
