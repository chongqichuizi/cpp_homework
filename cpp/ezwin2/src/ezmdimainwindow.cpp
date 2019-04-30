// EZMDIMainWindow.cpp: implementation of the EZMDIMainWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "EZMDIMainWindow.h"
#include <EZMDIWindow.h>
#include <ezevent.h>
#include <ezlayout.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EZMDIMainWindow::EZMDIMainWindow()
: EZMainWindow()
{
 _mdi = 0;
}

EZMDIMainWindow::~EZMDIMainWindow()
{

}

LRESULT EZMDIMainWindow::processDefaultMessage(UINT uMessage,EZEvent *e)
{
  return DefFrameProc(getHandle(), _mdi ? _mdi->getHandle() : 0, 
	  uMessage, e->getWParam(),e->getLParam());
}
void EZMDIMainWindow::onMenuSelect(EZEvent *ev)
{
  processDefault();
}
void EZMDIMainWindow::onControlAction(EZEvent *ev)
{
  processDefault();
}
void EZMDIMainWindow::onCreate(EZEvent *ev)
{
  EZMainWindowLayout *layout = (EZMainWindowLayout *)getLayout(); 

  _mdi = new EZMDIWindow();

  _mdi->create(this);
  
  if(layout) layout->setMainWindow(_mdi);
}

EZMDIWindow * EZMDIMainWindow::getMDIWindow()
{
  return _mdi;
}

void EZMDIMainWindow::onSize(EZEvent *ev)
{
  EZMainWindow::onSize(ev);

  //processDefault();

}

void EZMDIMainWindow::MDICascade(int flags)
{
  //flags =  // MDITILE_SKIPDISABLED

   getMDIWindow()->MDICascade(flags);
}

void EZMDIMainWindow::MDITile(int flags)
{
  // flags = MDITILE_HORIZONTAL MDITILE_SKIPDISABLED MDITILE_VERTICAL       
  getMDIWindow()->MDITile(flags);
}

void EZMDIMainWindow::MDIRestore(EZWindow *w)
{
  getMDIWindow()->MDIRestore(w);
}

void EZMDIMainWindow::MDIMaximise(EZWindow *w)
{
  getMDIWindow()->MDIMaximise(w);
}

void EZMDIMainWindow::MDINext()
{
  getMDIWindow()->MDINext();
}

void EZMDIMainWindow::MDIPrev()
{
  getMDIWindow()->MDIPrev();
}

EZWindow * EZMDIMainWindow::MDIGetActive()
{
  // get active, then do a lookup for it
  return getMDIWindow()->MDIGetActive();
}

// MDISetWindowMenu(), and other menu to replace

void EZMDIMainWindow::MDIActivate(EZWindow *w)
{
  getMDIWindow()->MDIActivate(w);  
}

void EZMDIMainWindow::MDIClose(EZWindow *w)
{
  getMDIWindow()->MDIClose(w); 
}
