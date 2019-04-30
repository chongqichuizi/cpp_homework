// blue.cpp: for Laboratory 09 - "Getting classy"
// $Revision: 1.2 $

#include <iostream>
#include <string>
#include <stdlib.h>
#include "rect.h"

using namespace std;
// function prototypes
void DisplayRectangleAttributes(const RectangleShape &r);
string Convert(const color &c);

// global window object for displaying graphical objects
SimpleWindow W("MainWindow", 12.0, 12.0);

//  ApiMain(): Manage our graphical operations
int ApiMain() 
{
   W.Open();
  
   RectangleShape R(W, 4.0, 4.0, Blue, 2.0, 3.0);
   R.Double();
   
   RectangleShape S(W, 7.0, 3.0, Black, 4.0, 1.0);
   DisplayRectangleAttributes(R);
   //DisplayRectangleAttributes(S);
   R.Draw();
   //S.Draw();
   return 0;
}

//  DisplayRectangleAttributes(): give a rectangle's vital characeristics
void DisplayRectangleAttributes(const RectangleShape &r) {

   // get position

   float rPositionX;
   float rPositionY;

   r.GetPosition(rPositionX, rPositionY );

   // get color
   color c;
   c = r.GetColor();   // enum color version of color

   string rColor = Convert(c);  // get string version of color

   // get size
   float rWidth;
   float rHeight;

   r.GetSize(rWidth, rHeight);

   // display attributes
   cout << "Your " <<  rColor << " rectangle is centered at ("
        << rPositionX << "," << rPositionY << ")  with width " << rWidth
        << " and height " << rHeight << endl;
}

// Convert(): return enum-type color as a string
string Convert(const color &c)
{
   string s;

   switch (c) 
   {
   case Black:
	  s = "black";   break;
   case White:
	  s = "white";   break;
   case Red:
	  s = "red";     break;
   case Green:
      s = "green";   break;
   case Blue:
      s = "blue";    break;
   case Yellow:
      s = "yellow";  break;
   case Cyan:
      s = "cyan";    break;
   case Magenta:
      s = "magenta"; break;
   default:
      cerr << "Unexpected color request: ";
      exit(1);
   }

   return s;
}

