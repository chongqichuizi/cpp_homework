#include <ezbrush.h>


EZBrush::EZBrush(const EZBrush &p)
{
   handle = p.handle;
   rgb = p.rgb;

   add((HANDLE)handle);
}
EZBrush & EZBrush::operator=(const EZBrush &p)
{
   if(handle) rem((HANDLE)handle);

   handle = p.handle;
   rgb = p.rgb;

   add((HANDLE)handle);

   return *this;
}
EZBrush::EZBrush(HBRUSH br)
{
  handle = br;

  LOGBRUSH lb;
  if(GetObject((HANDLE)handle,sizeof(lb),&lb))
  {
    rgb = lb.lbColor;
  }

  add((HANDLE)handle);
}
EZBrush::EZBrush(COLORREF cr)
{
  handle = CreateSolidBrush(cr);
  rgb = cr;

  add((HANDLE)handle);
}
EZBrush::~EZBrush()
{
  rem((HANDLE)handle);
}
EZBrush EZBrush::white()
{
  return EZBrush((HBRUSH)GetStockObject(WHITE_BRUSH));
}
EZBrush EZBrush::black()
{
  return EZBrush((HBRUSH)GetStockObject(BLACK_BRUSH));
}
EZBrush EZBrush::gray()
{
  return EZBrush((HBRUSH)GetStockObject(GRAY_BRUSH));
}
EZBrush EZBrush::dkgray()
{
  return EZBrush((HBRUSH)GetStockObject(DKGRAY_BRUSH));
}
EZBrush EZBrush::ltgray()
{
  return EZBrush((HBRUSH)GetStockObject(LTGRAY_BRUSH));
}

EZBrush EZBrush::getSystemBrush(int index)
{
  return EZBrush(GetSysColorBrush(index));
}
