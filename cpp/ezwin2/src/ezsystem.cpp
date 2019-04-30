#include <ezsystem.h>



EZPen EZSystem::getSystemPen(int index)

{

  return EZPen(GetSysColor(index));

}

EZBrush EZSystem::getSystemBrush(int index)

{

  return EZBrush(GetSysColorBrush(index));

}
