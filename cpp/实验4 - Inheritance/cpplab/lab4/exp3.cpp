//
// Laboratory 4 - Inheritance (exp3.cpp)
//
#include <assert.h>
#include "ezwin.h"
#include "box.h"

SimpleWindow DemoWindow("Lab 4 - Experiment 3", 15.0, 9.0, Position(3.0, 3.0));

int ApiMain() 
{


	DemoWindow.Open();
    assert(DemoWindow.GetStatus() == WindowOpen);
    BoxShape R(DemoWindow, Position(7, 5), Blue, 10.0, 6.0, 0.2);
    R.Draw();
    R.Erase();
    BoxShape S(DemoWindow, Position(7, 5), Red, 4.0, 3.0, 0.2);
    S.Draw();
    S.Erase();
    return 0;

}


