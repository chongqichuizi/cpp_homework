

#include <ezmdiwindow.h>
#include <ezevent.h>

EZMDIWindow::EZMDIWindow()
{
}
bool EZMDIWindow::create(EZWindow *parent)
{
	return EZWindow::create(parent,"mdiclient",0,EZRect(),0);
}
EZMDIWindow::~EZMDIWindow()
{
} 

void EZMDIWindow::onPreCreate(CREATESTRUCT *cs)
{
	static const char * classname = "MDICLIENT";

    cs->lpszClass = classname;

    static CLIENTCREATESTRUCT ccs = {0};

	ccs.hWindowMenu = 0;
	ccs.idFirstChild = ((int)cs->hMenu)+1;
	
  	cs->style |= (WS_VISIBLE|WS_CLIPCHILDREN|WS_VSCROLL|WS_HSCROLL); //|WS_BORDER);
	cs->lpCreateParams = &ccs;
}

void EZMDIWindow::MDICascade(int flags)
{
  //flags =  // MDITILE_SKIPDISABLED

   sendMessage(WM_MDICASCADE, flags,0);
}

void EZMDIWindow::MDITile(int flags)
{
  // flags = MDITILE_HORIZONTAL MDITILE_SKIPDISABLED MDITILE_VERTICAL       
  sendMessage(WM_MDITILE, flags, 0); 
}

void EZMDIWindow::MDIRestore(EZWindow *w)
{
  if(w == 0) return;
  sendMessage(WM_MDIRESTORE, (WPARAM)w->getHandle(), 0);
}

void EZMDIWindow::MDIMaximise(EZWindow *w)
{
  if(w == 0) return;
  sendMessage(WM_MDIMAXIMIZE, (WPARAM)w->getHandle(), 0);
}

void EZMDIWindow::MDINext()
{
  sendMessage(WM_MDINEXT, 0, 0);  
}

void EZMDIWindow::MDIPrev()
{
  sendMessage(WM_MDINEXT, 0, 1);  
}

EZWindow * EZMDIWindow::MDIGetActive()
{
  // get active, then do a lookup for it
  HWND w = (HWND)sendMessage(WM_MDIGETACTIVE,0,0);
  return getApp()->findWindow(w);
}

// MDISetWindowMenu(), and other menu to replace

void EZMDIWindow::MDIActivate(EZWindow *w)
{
  if(!w) return;
  sendMessage(WM_MDIACTIVATE, (WPARAM)w->getHandle(), 0);  
}

void EZMDIWindow::MDIClose(EZWindow *w)
{
  if(!w) return;
  sendMessage(WM_MDIDESTROY, (WPARAM)w->getHandle(), 0); 
}
