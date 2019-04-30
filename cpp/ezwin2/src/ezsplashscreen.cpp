#include <ezsplashscreen.h>
#include <eztimer.h>

EZSplashScreen::EZSplashScreen()
{
	
}
bool EZSplashScreen::create(int timeout)
//: EZWindow(0,"EZSplashScreen","splash")
{
//  registerClass();

  //_extrastyle = WS_EX_TOPMOST|WS_EX_CLIENTEDGE; //WS_EX_WINDOWEDGE; //WS_EX_CLIENTEDGE;

  // find the center of the desktop
  int w = 400;
  int h = 240;

  HWND win = GetDesktopWindow();
  RECT rect;
  GetClientRect(win,&rect);

  bool ok = EZWindow::create(0, "splash",/*WS_BORDER|*/ WS_VISIBLE|WS_POPUP,
    EZRect(rect.right/2 - w/2,rect.bottom/2 - h/2, w,h) );

  EZTimer * t = new EZTimer(this);
  t->start(timeout * 1000);

  return ok;
}
EZSplashScreen::~EZSplashScreen()
{
   // TODO - need to be able to remove from app list - and delete
}
void EZSplashScreen::onPreCreate(CREATESTRUCT *cs)
{
	cs->dwExStyle |= WS_EX_TOPMOST|WS_EX_CLIENTEDGE;

	EZWindow::onPreCreate(cs);
}
void EZSplashScreen::onTimer(EZEvent *ev)
{
  close();
}



void EZSplashScreen::onCreate(EZEvent *ev)
{
}
