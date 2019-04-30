#include <ezscrollbar.h>

EZScrollBar::EZScrollBar()
{
  _control_only = false;
  _type = VERTICAL;	
}

bool EZScrollBar::create(EZWindow *parent, EZScrollBar::EZScrollType type, int scrollflags, int id)
{
  _control_only = false;
  _type = type;

  unsigned long flags = WS_VISIBLE|scrollflags|(unsigned long)type;

  return EZWindow::create(parent,"", flags,EZRect(),id); 
}
EZScrollBar::~EZScrollBar()
{
}

EZScrollBar * EZScrollBar::getScrollBar(EZWindow *window, EZScrollBar::EZScrollType type)
{

  if(!window) return 0;

  EZScrollBar *b = new EZScrollBar();
  
  b->_window = window->getHandle();
  b->_control_only = true;
  b->_type = type;

  // tell the parent that we have a scrollbar
  LONG flags;

  flags = GetWindowLong(window->getHandle(), GWL_STYLE);

  if(type == HORIZONTAL) flags|= WS_HSCROLL;
  else flags |= WS_VSCROLL;

  SetWindowLong(window->getHandle(), GWL_STYLE, flags);

  return b;
}

bool EZScrollBar::getScrollInfo(LPSCROLLINFO lpsi)
{
  if(!lpsi) return false;


  return GetScrollInfo(getHandle(), _control_only ? _type : SB_CTL, lpsi) == TRUE;
}

bool EZScrollBar::show()
{
  return ShowScrollBar(getHandle(), _control_only ? _type : SB_CTL, TRUE) == TRUE;
}

bool EZScrollBar::hide()
{
  return ShowScrollBar(getHandle(), _control_only ? _type : SB_CTL, FALSE) == TRUE;
}

bool EZScrollBar::setScrollInfo(LPSCROLLINFO lpsi, bool refresh)
{
  if(!lpsi) return false;

  return SetScrollInfo(getHandle(), _control_only ? _type : SB_CTL, lpsi, refresh) == TRUE;
}

int EZScrollBar::getMax()
{
	 SCROLLINFO info;

     ZeroMemory(&info, sizeof(SCROLLINFO));
     info.cbSize = sizeof(SCROLLINFO);

     info.fMask = SIF_RANGE; 

	 getScrollInfo(&info);

	 return info.nMax;
}

int EZScrollBar::getScrollPos()
{
	 SCROLLINFO info;

     ZeroMemory(&info, sizeof(SCROLLINFO));
     info.cbSize = sizeof(SCROLLINFO);

     info.fMask = SIF_POS;
	 getScrollInfo(&info);

	 return info.nPos;
}

int EZScrollBar::getTrackPos()
{
	 SCROLLINFO info;

     ZeroMemory(&info, sizeof(SCROLLINFO));
     info.cbSize = sizeof(SCROLLINFO);

     info.fMask = SIF_TRACKPOS; 

	 getScrollInfo(&info);

	 return info.nTrackPos;
}

bool EZScrollBar::setScrollPos(int pos, bool refresh)
{
	 SCROLLINFO info;

     ZeroMemory(&info, sizeof(SCROLLINFO));

     info.cbSize = sizeof(SCROLLINFO);
     info.nPos = pos;
     info.fMask = SIF_POS;

	 return setScrollInfo(&info, refresh);
}

int EZScrollBar::getScrollPage()
{
	 SCROLLINFO info;

     ZeroMemory(&info, sizeof(SCROLLINFO));
     info.cbSize = sizeof(SCROLLINFO);

     info.fMask = SIF_PAGE; 

	 getScrollInfo(&info);

	 return info.nPage;
}

void EZScrollBar::onPreCreate(CREATESTRUCT *cs)
{
  static const char * classname = "SCROLLBAR";

  cs->lpszClass = classname;
}
