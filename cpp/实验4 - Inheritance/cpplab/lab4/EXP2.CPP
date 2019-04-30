//
// Laboratory 4 - Inheritance (exp2.cpp)
//
#include <assert.h>
#include "shadowrect.h"

SimpleWindow DemoWindow("Lab 4 - Experiment 2", 15.0, 9.0, Position(3.0, 3.0));

int ApiMain() 
{
   DemoWindow.Open();
   assert(DemoWindow.GetStatus() == WindowOpen);

   // Instantiate a red shadowed rectangle
   ShadowedRectangleShape R(DemoWindow, Position(4.25, 4.25), Red, 5.0, 5.0);
  
   R.Draw();
   
   R.Erase();
  

   return 0;
}
