#include <ezcursor.h>

#include <ezapp.h>

EZCursor::EZCursor()
{
  _handle = LoadCursor(NULL, IDC_ARROW);
}

EZCursor::EZCursor(DWORD res)
{
  _handle = LoadCursor(EZApp->getInstance(), MAKEINTRESOURCE(res));
}

EZCursor::EZCursor(LPCTSTR lpCursorName)
{
  _handle = LoadCursor(EZApp->getInstance(), lpCursorName);
}

EZCursor::EZCursor(const EZCursor &curs)
{
  _handle = CopyCursor(curs.getHandle());
}

EZCursor::EZCursor(HCURSOR h)
{
  _handle = CopyCursor(h);
}

EZCursor &EZCursor::operator=(const EZCursor &curs)
{
  if(_handle) DestroyCursor(_handle);

  _handle = CopyCursor(curs.getHandle());

  return *this;
}

EZCursor::~EZCursor()
{
	if(_handle) DestroyCursor(_handle);
}

HCURSOR EZCursor::getHandle() const
{
  return _handle;
}

EZCursor EZCursor::getSystemCursor(LPCTSTR lpCursorName)
{
  HCURSOR s = LoadCursor(NULL,lpCursorName);

  EZCursor curs(s);

  DestroyCursor(s);

  return curs;
}

