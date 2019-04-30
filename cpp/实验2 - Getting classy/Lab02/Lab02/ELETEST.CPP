#include <iostream>
#include "element.h"
using namespace std;

int main() {

   int MyX = 1;
   int MyY = 2;
   int MyZ = 3;

   const Element Center(0, 0, 0);
   Element MyPoint(MyX, MyY, MyZ);

   cout << "Center is (" << Center.GetX() << "," << Center.GetY()
    << "," << Center.GetZ() << ")" << endl;

   cout << "MyPoint is (" << MyPoint.GetX() << "," << MyPoint.GetY()
    << "," << MyPoint.GetZ() << ")" << endl;

   Element OtherPoint = MyPoint;

   OtherPoint.SetX(9);
   cout << "OtherPoint is (" << OtherPoint.GetX() << ","
    << OtherPoint.GetY() << ","
    << OtherPoint.GetZ() << ")" << endl;

   return 0;

}

