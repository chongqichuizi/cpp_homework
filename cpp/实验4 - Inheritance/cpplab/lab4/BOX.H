#include"SHAPE.H"
#ifndef BOX_H
#define BOX_H

// Your declaration of BoxShape should be placed in this file
class BoxShape : public Shape {
public:
	BoxShape(SimpleWindow &Window,
		const Position &Center, const color &c = Red,
		float Length = 1.0f, float Width = 2.0f, float offset=0);
	BoxShape(SimpleWindow &w,
		float XCoord, float YCoord,
		const color &c = Red, float Length = 1.0f,
		float Width = 2.0f, float offset=0);
	float GetWidth() const;
	float GetHeight() const;

	void GetSize(float &Width, float &Height) const;
	void SetSize(float Width, float Height);

	void Draw();
	void Erase();

private:
	float Width;
	float Height;
	float Offset=0;
};

#endif

