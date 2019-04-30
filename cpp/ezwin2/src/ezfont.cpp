#include <ezfont.h>

EZFont::EZFont()
{
  _handle = (HFONT)GetStockObject(DEVICE_DEFAULT_FONT);
  add((HANDLE)_handle);
}
EZFont::EZFont(LOGFONT &logFont)
{
  _handle = CreateFontIndirect(&logFont);

  add((HANDLE)_handle);
}
EZFont::EZFont(const EZFont &f)
{
  _handle = f._handle;

  add((HANDLE)_handle);
}
EZFont & EZFont::operator=(const EZFont &f)
{
  if(_handle) rem((HANDLE)_handle);

  _handle = f._handle;

  add((HANDLE)_handle);

  return *this;
}

EZFont::EZFont(const char * name, int w, int h, int pitch, int quality, int style)
{
  LOGFONT logFont;
  memset(&logFont, 0, sizeof(LOGFONT));

  logFont.lfHeight = h; //-h;  
  logFont.lfWidth  = w; // -w;
  logFont.lfPitchAndFamily = pitch;

  if(style & EZFONTSTYLE_BOLD) logFont.lfWeight = FW_BOLD;
  if(style & EZFONTSTYLE_ITALIC) logFont.lfItalic = TRUE;
  if(style & EZFONTSTYLE_UNDERLINE) logFont.lfUnderline = TRUE;

//  logFont.lfQuality = DRAFT_QUALITY;

  // NOTE: should check str size here !!!
  if(name) strcpy(logFont.lfFaceName, name); 

  _handle = CreateFontIndirect(&logFont);

  add((HANDLE)_handle);
}
EZFont::~EZFont()
{
  rem((HANDLE)_handle);
} 

EZFont::EZFont(HFONT br)
{
  _handle = br;

  add((HANDLE)_handle);
}

int EZFont::getWidth()
{
  return getSize().getWidth();
}
int EZFont::getHeight()
{
  return getSize().getHeight();
}
EZSize EZFont::getSize()
{
  LOGFONT logFont;

  if(GetObject((HANDLE)_handle,sizeof(LOGFONT),&logFont)<0)
  {
	  // if failed

	  logFont.lfHeight = 0;
	  logFont.lfWidth = 0;
  }
  
  return EZSize(logFont.lfWidth, logFont.lfHeight);
}

bool EZFont::getInfo(LOGFONT *info)
{
  if(!info) return false;

  return GetObject((HANDLE)_handle,sizeof(LOGFONT), info) !=0;
}
