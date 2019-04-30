#include <eztooltip.h>
#include <ezapp.h>

EZToolTip::EZToolTip()
{
}
bool EZToolTip::create(EZWindow *parent)
{
   return EZWindow::create(parent,"",0,EZRect(0,0,0,0));
}
EZToolTip::~EZToolTip()
{
}
void EZToolTip::onPreCreate(CREATESTRUCT *cs)
{
  static const char * classname = TOOLTIPS_CLASS;

  cs->lpszClass = classname;

  cs->dwExStyle |= WS_EX_TOPMOST;
  cs->style     |= (WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP);
}

bool EZToolTip::addTool(EZWindow *window,LPSTR text)
{
  if(!window) return false;

  TOOLINFO ti;
  ti.cbSize = sizeof(TOOLINFO);
  ti.uFlags = TTF_SUBCLASS|TTF_IDISHWND;

  if(getParent()) ti.hwnd = getParent()->getHandle();
  else ti.hwnd = window->getHandle();

  ti.hinst = EZApp->getInstance();
  ti.uId = (UINT)window->getHandle();
  ti.lpszText = text;

  return sendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti) != 0;
}

bool EZToolTip::addTool(EZWindow *window, const EZRect &rect, int id,LPSTR text)
{
  if(!window) return false;

  TOOLINFO ti;
  ti.cbSize = sizeof(TOOLINFO);
  ti.uFlags = TTF_SUBCLASS;
  ti.hwnd = window->getHandle();
  ti.hinst = EZApp->getInstance();
  ti.uId = id;
  ti.lpszText = text;

  ti.rect = rect.toRECT();

  return sendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti) != 0;
}

bool EZToolTip::remTool(EZWindow *wnd)
{
  if(!wnd) return false;

  TOOLINFO ti;
  ti.cbSize = sizeof(TOOLINFO);
  ti.uFlags = TTF_SUBCLASS|TTF_IDISHWND;

  if(getParent()) ti.hwnd = getParent()->getHandle();
  else ti.hwnd = wnd->getHandle();

  ti.hinst = EZApp->getInstance();
  ti.uId = (UINT)wnd->getHandle();

  return sendMessage(TTM_DELTOOL, 0, (LPARAM)&ti) != 0;
}

bool EZToolTip::remTool(EZWindow *w,int ID)
{
  if(!w) return false;

  TOOLINFO ti;
  ti.cbSize = sizeof(TOOLINFO);
  ti.uFlags = TTF_SUBCLASS;

  if(getParent()) ti.hwnd = getParent()->getHandle();
  else ti.hwnd = w->getHandle();

  ti.hinst = EZApp->getInstance();
  ti.uId = (UINT)ID;

  return sendMessage(TTM_DELTOOL, 0, (LPARAM)&ti) != 0;
}

void EZToolTip::onCreate(EZEvent *ev)
{
	SetWindowPos(getHandle(),HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
}
