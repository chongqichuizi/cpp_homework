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
// $Revision: 1.3 $
// $Name: E2 $
//
//**************************************************************************

// Display a dream house
#include <iostream>
#include <vector>

using namespace std;

#include "shape.h"
#include "triangle.h"
#include "circle.h"
#include "rect.h"
#include "square.h"

// prototypes
vector<Shape*>* BuildHouse(SimpleWindow &W);
void DrawFigure(vector<Shape*> *F);

SimpleWindow Window("House", 10, 10);

// ApiMain(); manage building and display of house
int ApiMain()
{
	Window.Open();

	vector<Shape*> *DreamHouse = BuildHouse(Window);
	DrawFigure(DreamHouse);

	cout << "Type a line to terminate the program:";
	char reply;
	cin >> reply;

	return 0;
}

// BuildHouse(): use basic shapes to make a house
vector<Shape*>* BuildHouse(SimpleWindow &W)
{
	//
	// House composed of a list of parts
	//
	vector<Shape*> *House = new vector<Shape*>;

	// 1
	// house has a square frame
	SquareShape* pFrame = new SquareShape(W, Position(5, 7), Blue, 5);
	House->push_back(pFrame);

	// 2
	// house has a triangular roof	
	TriangleShape* pRoof = new TriangleShape(W, Position(5, 3.5), Red, 6);
	House->push_back(pRoof);

	// 3
	// house has a skylight
	CircleShape* pSkylight = new CircleShape(W, Position(5, 7.75), Yellow, 1.5);
	House->push_back(pSkylight);

	// 4
	// house has a door
	RectangleShape* pDoor = new RectangleShape(W, Position(5, 8.5), Yellow, 1.5, 2);
	House->push_back(pDoor);

	// 5
	// house has a left window
	SquareShape* pLeftWindow = new SquareShape(W, Position(4, 6), Yellow, 1.5);
	House->push_back(pLeftWindow);

	// 6
	// house has a right window
	SquareShape* pRightWindow = new SquareShape(W, Position(6, 6), Yellow, 1.5);
	House->push_back(pRightWindow);

	return House;
}

// DrawFigure(): draw shapes in list F
void DrawFigure(vector<Shape*> *F)
{
	for (vector<Shape*>::iterator P = F->begin(); P != F->end(); ++P)
	{
		(*P)->Draw();

		delete *P;
	}

	delete F;
}

