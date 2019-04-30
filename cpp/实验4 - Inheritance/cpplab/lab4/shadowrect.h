#include "rect.h"

class ShadowedRectangleShape : public RectangleShape 
{
public:
	// prototype constructor         
	ShadowedRectangleShape(SimpleWindow &Window,
		const Position &Center, const color &c = Red,
		float Length = 1.0f, float Width = 2.0f);
	ShadowedRectangleShape(SimpleWindow &w,
		float XCoord, float YCoord,
		const color &c = Red, float Length = 1.0f,
		float Width = 2.0f);
	// prototype Draw()
	void Draw();
	// prototype Erase()
	void Erase();

private:
	Position Offset=0.1;
};
