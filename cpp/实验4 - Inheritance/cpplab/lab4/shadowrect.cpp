#include<iostream>
#include "shadowrect.h"

// define ShadowedRectangleShape's constructor here
ShadowedRectangleShape::ShadowedRectangleShape(SimpleWindow &Window,
	const Position &Center, const color &c, float w,
	float h) :RectangleShape(Window, Center, c,w,h){
	cout << "Constructor ShadowedRectangleShape called" << endl;
}
ShadowedRectangleShape::ShadowedRectangleShape(SimpleWindow &Window,
	float XPosition, float YPosition,
	const color &c, float w, float h):RectangleShape(Window,XPosition,YPosition,c,w,h){
	cout << "Constructor ShadowedRectangleShape called" << endl;
}
/// define ShadowedRectangleShape's draw function here
void ShadowedRectangleShape::Draw()
{
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();

	const Position UpperLeft = Center + Position(-.4f * Width, -.4f * Height);
	const Position LowerRight = Center + Position(.6f * Width, .6f * Height);

	GetWindow().RenderRectangle(UpperLeft, LowerRight, GetColor(), false);
	
	return;
}
void ShadowedRectangleShape::Erase() 
{
   const Position Center = GetPosition();
   const float    Width  = GetWidth();
   const float    Height = GetHeight();

   const Position UpperLeft  = Center + Position(-.5f * Width, -.5f * Height);
   const Position LowerRight = Center + Position( .5f * Width,  .5f * Height);

   // Erase main rectangle first
   GetWindow().RenderRectangle(UpperLeft, LowerRight, White, false);
   if (HasBorder()) 
   {
      GetWindow().RenderRectangle(UpperLeft, LowerRight, White, true);
   }
   
  /* GetWindow().RenderRectangle(UpperLeft +Offset, LowerRight + Offset, White, false);
   if (HasBorder()) 
   {
      GetWindow().RenderRectangle(UpperLeft - Offset, LowerRight - Offset, White, true);
   }*/

   return;
}
 