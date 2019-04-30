#include <ezpen.h>

EZPen::EZPen(const EZPen &p)
{
   handle = p.handle;
   rgb = p.rgb;

  add((HANDLE)handle);
}
EZPen & EZPen::operator=(const EZPen &p)
{
   if(handle) rem((HANDLE)handle);

   handle = p.handle;
   rgb = p.rgb;

   add((HANDLE)handle);

   return *this;
}
EZPen::EZPen(HPEN br)
{
  handle = br;

  LOGPEN lp;
  if(GetObject((HANDLE)handle,sizeof(lp),&lp))
  {
    rgb = lp.lopnColor;
  }

  add((HANDLE)handle);
}
EZPen::EZPen(COLORREF cr,  int style, int width)
{
  handle = CreatePen(style,width, cr);
  rgb = cr;

  add((HANDLE)handle);
}
EZPen::~EZPen()
{
  rem((HANDLE)handle);
}
EZPen EZPen::white()
{
  EZPen p = EZPen((HPEN)GetStockObject(WHITE_PEN));
  p.rgb = RGB(0xff,0xff,0xff);
  return p;
}
EZPen EZPen::black()
{
  EZPen p = EZPen((HPEN)GetStockObject(BLACK_PEN));
  p.rgb = RGB(0,0,0);
  return p;
}

EZPen EZPen::getSystemPen(int index)
{
  COLORREF r = GetSysColor(index);
  return EZPen(r);
}