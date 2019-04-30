
#include <ezclientwindow.h>
#include <ezevent.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EZClientWindow::EZClientWindow()
{
}
bool EZClientWindow::create(EZWindow *parent)
{
   EZRect rect;
   if(parent!=0) rect = parent->getClientRect();
	return EZWindow::create(parent,"",WS_VISIBLE,rect,-1);
}

EZClientWindow::~EZClientWindow()
{

}
void EZClientWindow::onPreCreate(CREATESTRUCT *cs)
{
	EZWindow::onPreCreate(cs);

	cs->style |= WS_VISIBLE;
}

void EZClientWindow::onNotify(EZEvent *ev)
{
	if(getParent())
	{
		getParent()->onNotify(ev);
	}
}
void EZClientWindow::onMenuSelect(EZEvent *ev)
{
	if(getParent())
	{
		getParent()->onMenuSelect(ev);
	}
}
void EZClientWindow::onControlAction(EZEvent *ev)
{
	if(getParent())
	{
		getParent()->onControlAction(ev);
	}
}

void EZClientWindow::onMouseUp(EZEvent *ev, int button)
{
	if(getParent())
	{
		// translate to parents coords first
		int x = LOWORD(ev->getLParam());
		int y = HIWORD(ev->getLParam());

		EZPoint pt = translatePoint(this, EZPoint(x,y));

		EZEvent ev1( ev->getWParam(), ((LPARAM)pt.getY() << 16) | pt.getX() );
		
		getParent()->onMouseUp(&ev1, button);
	}
}
void EZClientWindow::onMouseDown(EZEvent *ev, int button)
{
	if(getParent())
	{
		// translate to parents coords first
		int x = LOWORD(ev->getLParam());
		int y = HIWORD(ev->getLParam());

		EZPoint pt = translatePoint(this, EZPoint(x,y));

		EZEvent ev1( ev->getWParam(), ((LPARAM)pt.getY() << 16) | pt.getX() );

		getParent()->onMouseDown(&ev1, button);
	}
}
