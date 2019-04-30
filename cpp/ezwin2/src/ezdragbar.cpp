#include <ezdragbar.h>

#include <commctrl.h>

#include <ezevent.h>
#include <ezgfx.h>
#include <ezbrush.h>
#include <ezcursor.h>

#define DRAG_WIDTH 5

EZDragBar::EZDragBar() 
: EZWindow(), EZLayout(this)
{
  _vert = true;

  _dragpos = 0;

  if(_vert) _drag = EZRect(300,0,300 + DRAG_WIDTH,100);
  else _drag = EZRect(0,40,100,40+DRAG_WIDTH);
  _dragpos = 40;

  _moving = false;

  _left = _right = 0;

  setLayout(NULL);

}
EZDragBar::~EZDragBar()
{

}
bool EZDragBar::create(EZWindow *parent,const char *name,bool vert)
{
  _vert = vert;
  if(_vert) _drag = EZRect(300,0,300 + DRAG_WIDTH,100);
  else _drag = EZRect(0,40,100,40+DRAG_WIDTH);

  EZRect rect;
  if(parent != 0) rect = parent->getClientRect();
  bool ok = EZWindow::create(parent,name,WS_VISIBLE,rect,-1);

  return ok;
}

void EZDragBar::onCreate(EZEvent *ev)
{
  setLayout(this);

  SetClassLong(_window,GCL_HCURSOR,0);

  if(_vert)
	  setCursor(EZCursor::getSystemCursor(IDC_SIZEWE));
  else
	  setCursor(EZCursor::getSystemCursor(IDC_SIZENS));

  onSize(0);
  EZWindow::rethinkLayout();
}

bool EZDragBar::setDragPos(int pos)
{
   EZGfx painter(this,false);

   if(pos<0) pos=0;

   if(_moving==true) painter.patBlt(_drag,DSTINVERT);

   if(_vert==true)
   {
     if(pos>getClientRect().getRight()-DRAG_WIDTH) pos = getClientRect().getRight()-DRAG_WIDTH;

     _drag.moveTo(pos,0);

   }
   else
   {
     if(pos>getClientRect().getBottom()-DRAG_WIDTH) pos = getClientRect().getBottom()-DRAG_WIDTH;

     _drag.moveTo(0,pos);
   }

   _dragpos = getDragRatioPos();

   if(_moving==true) painter.patBlt(_drag,DSTINVERT);
   else
   {
     // now force a redraw of us
     repaint(EZRect(),true); 
     doLayout();
   }
   return true;
}
int EZDragBar::getDragPos()
{
  if(_vert) return _drag.getLeft(); 
  else
	  return _drag.getTop();
}
int EZDragBar::getDragRatioPos()
{
  int pos;
  int sz;

  if(_vert)
  {
    sz = getClientRect().getWidth(); 
    pos = _drag.getLeft();
  }
  else
  {
    sz = getClientRect().getHeight(); 
    pos = _drag.getTop();
  }
  if(sz==0 || pos==0) pos = 0;
  else pos = (int)((pos*100.0)/sz);

  return pos;
}
bool EZDragBar::setDragRatioPos(int pos)
{
  int sz;

  if(pos<0) pos=0;
  if(pos>100) pos = 100;

  if(_vert)
  {
    sz = getClientRect().getWidth(); 
  }
  else
  {
    sz = getClientRect().getHeight(); 
  }
  sz =(int)( (sz * pos) /100.0 );

  return setDragPos(sz);
}
void EZDragBar::onSetFocus(EZEvent *ev)
{
  HWND wnd_handle = (HWND)ev->getWParam();
  
  EZWindow *parent = getParent();

  // set parent as focused if we have the focus and wasnt parent that just lost it
  //if(parent && parent->getHandle()!=wnd_handle) parent->focus();

  if(parent) parent->focus();
}
void EZDragBar::onPaint(EZEvent *ev)
{
  EZGfx painter(this);

  EZBrush brush = EZBrush::getSystemBrush(COLOR_BTNFACE);

  painter.fillRect(_drag,brush);
  painter.draw3DRect(_drag);
}
void EZDragBar::onSize(EZEvent *ev)
{
  int pos = getDragPos();

  if(_vert) _drag = EZRect(_drag.getLeft(),0,_drag.getRight(),getClientRect().getHeight());
  else _drag = EZRect(0,_drag.getTop(),getClientRect().getRight(),_drag.getBottom());

  setDragPos(pos);
}

void EZDragBar::onMouseDown(EZEvent *ev,int button)
{
   short x,y;

   if(button!=0) return;

   x=LOWORD(ev->getLParam());
   y=HIWORD(ev->getLParam());

   if(_drag.contains(x,y)!=true) return;

   captureMouse(true);
   _moving = true;

   EZGfx painter(this,false);
   painter.patBlt(_drag,DSTINVERT);

}
void EZDragBar::onMouseUp(EZEvent *ev,int button)
{
   if(button!=0) return;

   if(_moving == false) return;

   captureMouse(false);
   _moving = false;

   short x,y;

	x=LOWORD(ev->getLParam());
	y=HIWORD(ev->getLParam());

   EZGfx painter(this,false);
   painter.patBlt(_drag,DSTINVERT);

   clear();
   doLayout();
}
void EZDragBar::onMouseMove(EZEvent *ev)
{
  if(_moving == false) return;

  short x,y;


  x=LOWORD(ev->getLParam());
  y=HIWORD(ev->getLParam());

  if(_vert) setDragPos(x);
  else setDragPos(y);
}


//DEL void EZDragBar::onSetCursor(EZEvent *ev)
//DEL {
//DEL   if(_vert) SetCursor(LoadCursor(NULL,IDC_SIZEWE));
//DEL   else      SetCursor(LoadCursor(NULL,IDC_SIZENS));
//DEL }

void EZDragBar::doLayout()
{
  // do the layout for the direct children of this parent
  if(EZLayout::_parent==0) return;

  EZRect pr = getClientRect();

  if(_vert)
  {
    if(_left) {
      EZSize s = _left->getSize();
      EZRect r(0,0,_drag.getLeft(),pr.getHeight());
      _left->setRect(r);
    }
    if(_right) {
      EZSize s = _right->getSize();
      EZRect r(_drag.getRight()+1,0,pr.getRight(),pr.getHeight());
      _right->setRect(r);
    }

  }
  else // horz
  {
    if(_left) {
      EZSize s = _left->getSize();
      EZRect r(0,0,pr.getWidth(),_drag.getTop());
      _left->setRect(r);
    }
    if(_right) {
      EZSize s = _right->getSize();
      EZRect r(0,_drag.getBottom()+1,pr.getWidth(),pr.getHeight());
      _right->setRect(r);
    }

  }
  repaint(getClientRect(),true);
  return;
}
void EZDragBar::setLeftPane(EZWindow *w)
{
  _left = w;
}
void EZDragBar::setRightPane(EZWindow *w)
{
  _right = w;
}
void EZDragBar::setTopPane(EZWindow *w)
{
  setLeftPane(w);
}
void EZDragBar::setBottomPane(EZWindow *w)
{
  setRightPane(w);
}

EZWindow * EZDragBar::getLeftPane()
{
  return _left;
}

EZWindow * EZDragBar::getRightPane()
{
  return _right;
}
EZWindow * EZDragBar::getTopPane()
{
  return getLeftPane();
}

EZWindow * EZDragBar::getBottomPane()
{
  return getRightPane();
}

