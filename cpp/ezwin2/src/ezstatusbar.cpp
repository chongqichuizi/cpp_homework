#include <EZStatusBar.h>

#include <commctrl.h>


EZStatusBar::EZStatusBar()
{
}
EZStatusBar::~EZStatusBar()
{

}
bool EZStatusBar::create(EZWindow *parent,const char *text, int id)
{
  unsigned long flags = WS_BORDER | WS_VISIBLE;

  if(parent) flags |= WS_CHILD;

  return EZWindow::create(parent,text,flags,EZRect(),id);
}

void EZStatusBar::onPreCreate(CREATESTRUCT *cs)
{
	static const char *classname = STATUSCLASSNAME;

	cs->lpszClass = classname;
}
