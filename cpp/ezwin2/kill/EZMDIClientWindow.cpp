
#include <ezmdiclientwindow.h>
#include <ezmdiwindow.h>
#include <ezevent.h>
#include <ezlayout.h>

EZMDIClientWindow::EZMDIClientWindow()
{
	setLayout( new EZSingleClientLayout(this) );
}

bool EZMDIClientWindow::create(EZWindow *parent)
{

	bool ok = EZWindow::create(parent,"mdiclientwindow",0,EZRect(),0);

	EZMDIWindow *w = new EZMDIWindow();
	w->create(this);

	return ok;
}
EZMDIClientWindow::~EZMDIClientWindow()
{
} 

void EZMDIClientWindow::onPreCreate(CREATESTRUCT *cs)
{
    static CLIENTCREATESTRUCT ccs = {0};

	ccs.hWindowMenu = 0;
	ccs.idFirstChild = ((int)cs->hMenu)+1;
	
  	cs->style |= (WS_VISIBLE); //|WS_CLIPCHILDREN|WS_VSCROLL|WS_HSCROLL|WS_BORDER);
	cs->lpCreateParams = &ccs;
}

LRESULT EZMDIClientWindow::processDefaultMessage(UINT uMessage,EZEvent *msg)
{
  EZWindow *w = getFirstChild();

  if(w) return(DefFrameProc(getHandle(), w->getHandle(),
	      uMessage,msg->getWParam(), msg->getLParam()));
  else
	  return EZWindow::processDefaultMessage(uMessage, msg);
}

//DEL void EZMDIClientWindow::onChildControlAction(EZEvent *ev)
//DEL {
//DEL   processAsDefault(WM_COMMAND,ev);
//DEL }

//DEL void EZMDIClientWindow::onSize(EZEvent *ev)
//DEL {
//DEL   this->processDefault();
//DEL }

void EZMDIClientWindow::onCreate(EZEvent *ev)
{
	rethinkLayout();
}
