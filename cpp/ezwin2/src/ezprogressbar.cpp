#include <ezprogressbar.h>

#include <commctrl.h>

EZProgressBar::EZProgressBar()
{
}

bool EZProgressBar::create(EZWindow *parent,char *name,const EZRect &rect, int id)
{
  unsigned long flags = WS_VISIBLE;

  if(parent) flags |= WS_CHILD;

  return EZWindow::create(parent, name,flags,rect,id);
}
EZProgressBar::~EZProgressBar()
{

}

void EZProgressBar::setRange(long rn)
{
  sendMessage(PBM_SETRANGE,rn,rn);
}
void EZProgressBar::setPos(long p)
{
  _pos = p;
  sendMessage(PBM_SETPOS,p,p);
}


/*
#define PBM_SETRANGE            (WM_USER+1)
#define PBM_SETPOS              (WM_USER+2)
#define PBM_DELTAPOS            (WM_USER+3)
#define PBM_SETSTEP             (WM_USER+4)
#define PBM_STEPIT              (WM_USER+5)
*/

void EZProgressBar::onPreCreate(CREATESTRUCT *cs)
{
  static const char * classname = PROGRESS_CLASS;

  cs->lpszClass = classname;

}

void EZProgressBar::onCreate(EZEvent *ev)
{
  sendMessage(PBM_SETSTEP,1,1);
  sendMessage(PBM_DELTAPOS,1,1);
  sendMessage(PBM_STEPIT,1,1);
  setRange(10);
  setPos(5);
}
