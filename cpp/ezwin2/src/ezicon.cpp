#include <ezicon.h>

EZIcon::EZIcon(DWORD iconresource)
{
  _icon = 0;
  LPCTSTR ic = (LPCTSTR)iconresource;

  if(ic == IDI_APPLICATION ||
     ic == IDI_ASTERISK    ||
     ic == IDI_EXCLAMATION ||
     ic == IDI_HAND        ||
     ic == IDI_QUESTION    ||
     ic == IDI_WINLOGO
  )
  {
       _icon = LoadIcon(0,(LPCTSTR)iconresource);
  }
  else
      _icon = LoadIcon(EZApp->getInstance(),ic);
}
EZIcon::EZIcon(const char *filename)
{

  _icon = (HICON)LoadImage(0,filename,IMAGE_ICON,0, 0,  LR_DEFAULTSIZE|LR_LOADFROMFILE);

}
EZIcon::~EZIcon()
{
  // if(_icon) hmmm win32 thinks u dont have to free it - .... I wonder .... 
}

EZIcon & EZIcon::operator=(const EZIcon &icon)
{
  this->_icon = icon._icon;
  return *this;
}
EZIcon::EZIcon(const EZIcon &icon)
{
  this->_icon = icon._icon;
}
