#include <ezbitmap.h>
#include <ezapp.h>
#include <stdlib.h>

EZBitmap::EZBitmap(const EZBitmap &b)
{
  _handle = b._handle;

  add((HANDLE)_handle);  
}
EZBitmap & EZBitmap::operator=(const EZBitmap &b)
{
  if(_handle) rem((HANDLE)_handle);

  _handle = b._handle;

  add((HANDLE)_handle);  

  return *this;
}

EZBitmap::EZBitmap(HBITMAP bm)
{
   _handle = bm;

  GetObject(_handle,sizeof(BITMAP),&bmapinfo);

  add((HANDLE)_handle);
}
EZBitmap::~EZBitmap()
{
  rem((HANDLE)_handle);
}
EZBitmap::EZBitmap(DWORD bmresource)
{
  _handle = LoadBitmap(EZApp->getInstance(),(LPCTSTR)bmresource);

  GetObject(_handle,sizeof(BITMAP),&bmapinfo);

  add((HANDLE)_handle);
}
EZBitmap::EZBitmap(const char *name)
{
  _handle = 0;

  _handle = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);

  add((HANDLE)_handle);
}
int EZBitmap::getWidth()
{
  GetObject(_handle,sizeof(BITMAP),&bmapinfo);
  return bmapinfo.bmWidth;
}
int EZBitmap::getHeight()
{
  GetObject(_handle,sizeof(BITMAP),&bmapinfo);
  return bmapinfo.bmHeight;
}

