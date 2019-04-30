#include <ezsimplescrollwindow.h>
#include <ezevent.h>
#include <ezgfx.h>
#include <ezscrollbar.h>

EZSimpleScrollWindow::EZSimpleScrollWindow()
{
  vscroll = hscroll = 0;
}

bool EZSimpleScrollWindow::create(EZWindow *parent)
{
	return EZWindow::create(parent,"",WS_VISIBLE|WS_HSCROLL |WS_VSCROLL);
}
EZSimpleScrollWindow::~EZSimpleScrollWindow()
{
}

void EZSimpleScrollWindow::onPreCreate(CREATESTRUCT *cs)
{
    // make sure hscroll & vscroll set
	cs->style |= (WS_HSCROLL |WS_VSCROLL);
	cs->dwExStyle |= WS_EX_CLIENTEDGE;
}

void EZSimpleScrollWindow::onCreate(EZEvent *ev)
{
  // create the scroll bars
	vscroll = EZScrollBar::getScrollBar(this, EZScrollBar::VERTICAL); 
 
	hscroll = EZScrollBar::getScrollBar(this, EZScrollBar::HORIZONTAL);
}

void EZSimpleScrollWindow::onScroll(EZEvent *ev, int type)
{
  int nScrollCode = (int) LOWORD(ev->getWParam());  // scroll bar value 
  short nPos = (short int) HIWORD(ev->getWParam()); // scroll box position 
  HWND hwndScrollBar = (HWND) ev->getLParam();      // handle to scroll bar 
 
  if(hwndScrollBar==0)
  {
	  // controls
	  if(type == EZScrollBar::VERTICAL)
	  {
			int ypos = vscroll->getScrollPos();

			switch(nScrollCode)
			{
			case SB_THUMBTRACK:
				ypos = vscroll->getTrackPos();
				break;
			case SB_THUMBPOSITION:
				ypos=vscroll->getTrackPos();
				vscroll->setScrollPos(ypos);
				break;
			case SB_LINEUP:
				if(ypos > 0)
				{
					ypos--;
					vscroll->setScrollPos(ypos,true);
				}
				break;
			case SB_LINEDOWN:
				if(ypos < vscroll->getMax())
				{
					ypos++;
					vscroll->setScrollPos(ypos,true);
				}
				break;
			case SB_PAGEDOWN:
				if(ypos < vscroll->getMax())
				{
					ypos += vscroll->getScrollPage();
					if(ypos > vscroll->getMax()) ypos = vscroll->getMax();

					vscroll->setScrollPos(ypos,true);
				}
				break;
			case SB_PAGEUP:
				if(ypos > 0)
				{
					ypos -= vscroll->getScrollPage();
					if(ypos<0) ypos = 0;

					vscroll->setScrollPos(ypos,true);
				}
				break;
			default:
				//vscroll->setScrollPos(pos);
				break;
			}

			EZWindow * w = getFirstChild();
			if(w)
			{
				w->setPos(w->getLeft(), -ypos);
				//int ap = w->getTop();
				repaint(getClientRect(),true);
			}
	  }
	  else if(type == EZScrollBar::HORIZONTAL)
	  {
			int xpos = hscroll->getScrollPos();

			switch(nScrollCode)
			{
			case SB_THUMBTRACK:
				xpos = hscroll->getTrackPos();
				break;
			case SB_THUMBPOSITION:
				xpos = hscroll->getTrackPos();
				hscroll->setScrollPos(xpos);
				break;
			case SB_LINEUP:
				if(xpos > 0)
				{
					xpos--;
					hscroll->setScrollPos(xpos,true);
				}
				break;
			case SB_LINEDOWN:
				if(xpos < hscroll->getMax())
				{
					xpos++;
					hscroll->setScrollPos(xpos,true);
				}
				break;
			case SB_PAGEDOWN:
				if(xpos < hscroll->getMax())
				{
					xpos += hscroll->getScrollPage();
					if(xpos > hscroll->getMax()) xpos = hscroll->getMax();

					hscroll->setScrollPos(xpos,true);
				}
				break;
			case SB_PAGEUP:
				if(xpos > 0)
				{
					xpos -= hscroll->getScrollPage();
					if(xpos<0) xpos = 0;

					hscroll->setScrollPos(xpos,true);
				}
				break;
			default:
				//vscroll->setScrollPos(pos);
				break;
			}

			EZWindow * w = getFirstChild();
			if(w)
			{
				w->setPos(-xpos, w->getTop());
				repaint(getClientRect(),true); 
			}
	  }
  }
}

void EZSimpleScrollWindow::onSize(EZEvent *ev)
{
  EZWindow::onSize(ev);

  calcScrollBarPos();
}

void EZSimpleScrollWindow::rethinkLayout()
{
	EZWindow::rethinkLayout();

	calcScrollBarPos();
}

void EZSimpleScrollWindow::calcScrollBarPos()
{
  //get rect used by child window
  EZWindow *w = getFirstChild();

  EZRect used_rect(0,0,1,1);
  int child_x=0, child_y=0;

  if(w) 
  {
	  used_rect = w->getRect();
	  child_x = w->getLeft();
	  child_y = w->getTop();

	  if(child_y>0) child_y = 0;
  }
  // have to move window?
  if(w)
  {
	if(used_rect.getHeight() < getClientRect().getHeight())
	{
		// center
		child_y = getClientRect().getHeight()/2 - used_rect.getHeight()/2;
	}
	else // use pos from scrollbar
		child_y = child_y;

	if(used_rect.getWidth() < getClientRect().getWidth())
	{
		// center
		child_x = getClientRect().getWidth()/2 - used_rect.getWidth()/2;
	}
	else // use pos from scroll bar
		child_x = child_x;

    w->setPos(child_x,child_y);
  }
  if(vscroll)
  {
	 SCROLLINFO info;

     ZeroMemory(&info, sizeof(SCROLLINFO));
     info.cbSize = sizeof(SCROLLINFO);

     info.fMask = SIF_DISABLENOSCROLL|SIF_RANGE|SIF_POS|SIF_PAGE; 

	 if(vscroll->getScrollInfo(&info))
	 {
		int  totalheight = used_rect.getHeight();

		int viewheight = getClientRect().getHeight();

		info.nMax = totalheight; 
		info.nMin = 0;
		info.nPos = -child_y;
		info.nPage = viewheight;
		
		info.fMask = SIF_DISABLENOSCROLL|SIF_RANGE|SIF_POS|SIF_PAGE;

		vscroll->setScrollInfo(&info, true);

	 }
  }
  if(hscroll)
  {
	 SCROLLINFO info;

     ZeroMemory(&info, sizeof(SCROLLINFO));
     info.cbSize = sizeof(SCROLLINFO);

     info.fMask = SIF_DISABLENOSCROLL|SIF_RANGE|SIF_POS|SIF_PAGE; 

	 if(hscroll->getScrollInfo(&info))
	 {
		int  totalwidth = used_rect.getWidth();

		int viewwidth = getClientRect().getWidth();

		info.nMax = totalwidth;
		info.nMin = 0;
		info.nPos = child_x;
		info.nPage = viewwidth;
		
		info.fMask = SIF_DISABLENOSCROLL|SIF_RANGE|SIF_POS|SIF_PAGE;

		hscroll->setScrollInfo(&info, true);
	 }
  }


  repaint(getClientRect(),true);
}
