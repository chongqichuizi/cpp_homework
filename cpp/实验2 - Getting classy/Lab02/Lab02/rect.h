//**************************************************************************
//
// Copyright (c) 1997.
//      Richard D. Irwin, Inc.
//
// This software may not be distributed further without permission from
// Richard D. Irwin, Inc.
//
// This software is distributed WITHOUT ANY WARRANTY. No claims are made
// as to its functionality or purpose.
//
// Authors: James P. Cohoon and Jack W. Davidson
// Date: 7/15/96
// $Revision: 1.4 $
// $Name: $
//
//**************************************************************************
// Class RectangleShape interface


#ifndef RECTSHAPE_H
#define RECTSHAPE_H
#include "shape.h"

class RectangleShape : public Shape 
{
public:
	RectangleShape(SimpleWindow &w,
		float XCoord, float YCoord,
		const color &c = Red, float Length = 1.0f,
		float Width = 2.0f);

	float GetWidth() const;
	float GetHeight() const;
	void  GetSize(float &Width, float &Height) const;

	void SetSize(float Width, float Height);

	void Draw();
	void Erase();
	void Double();

private:
	float Width;
	float Height;
};

#endif
