#include <iostream>
#include <vector>

using namespace std;

#include "shape.h"
#include "triangle.h"
#include "circle.h"
#include "rect.h"
#include "square.h"
#include "ellipse.h"

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

	RectangleShape* pyancong = new RectangleShape(W, Position(7, 3.5), Blue, .4, 2);
	House->push_back(pyancong);
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

	RectangleShape* pFence1 = new RectangleShape(W, Position(1.5, 8.5), Black, 1.8, .2);
	House->push_back(pFence1);
	RectangleShape* pFence2 = new RectangleShape(W, Position(8.5, 8.5), Black, 1.8, .2);
	House->push_back(pFence2);
	RectangleShape* pFence3 = new RectangleShape(W, Position(1.5, 9), Black, 1.8, .2);
	House->push_back(pFence3);
	RectangleShape* pFence4 = new RectangleShape(W, Position(8.5, 9), Black, 1.8, .2);
	House->push_back(pFence4);
	RectangleShape* pFence5 = new RectangleShape(W, Position(.8, 8.75), Black, .2, 1);
	House->push_back(pFence5);
	
	RectangleShape* pFence6 = new RectangleShape(W, Position(9.2, 8.75), Black, .2, 1);
	House->push_back(pFence6);
	RectangleShape* pFence7 = new RectangleShape(W, Position(1.4, 8.75), Black, .2, 1);
	House->push_back(pFence7);
	RectangleShape* pFence8 = new RectangleShape(W, Position(2, 8.75), Black, .2, 1);
	House->push_back(pFence8);
	RectangleShape* pFence9 = new RectangleShape(W, Position(8.6, 8.75), Black, .2, 1);
	House->push_back(pFence9);
	RectangleShape* pFence10 = new RectangleShape(W, Position(8, 8.75), Black, .2, 1);
	House->push_back(pFence10);
	EllipseShape* pyan1 = new EllipseShape(W, Position(7, 2.4), Magenta, .3, 0.1);
	House->push_back(pyan1);
	EllipseShape* pyan2 = new EllipseShape(W, Position(7.2, 2.2), Magenta, .5, 0.15);
	House->push_back(pyan2);
	EllipseShape* pyan3 = new EllipseShape(W, Position(7.5, 1.9), Magenta, .75, 0.25);
	House->push_back(pyan3);
	EllipseShape* pyan4 = new EllipseShape(W, Position(7.9, 1.5), Magenta, 1, 0.4);
	House->push_back(pyan4);
	EllipseShape* pyan5 = new EllipseShape(W, Position(8.5, .9), Magenta, 1.3, .6);
	House->push_back(pyan5);
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

