#include <ezmainwindow.h>
#include <ezstatusbar.h>
#include <ezlayout.h>
#include <eztoolbar.h>
#include <ezmenubar.h>

EZMainWindow::EZMainWindow()
{
  _toolbar = 0;
  _statusbar = 0;
  _menubar = 0;

  setLayout(new EZMainWindowLayout(this));
}

EZMainWindow::~EZMainWindow()
{
}

bool EZMainWindow::create(const char *windowname,unsigned long flags,const EZRect &rect)
{
	return EZWindow::create(0,windowname,flags,rect);
}
void EZMainWindow::onPreCreate(CREATESTRUCT *cs)
{
	static const char * classname = "EZMainWindow";

	cs->lpszClass = EZWindow::createEZWindowClass(classname);
}

EZMenuBar *EZMainWindow::getMenuBar()
{
  if(_menubar) return _menubar;

  _menubar = new EZMenuBar();
  _menubar->create(this);

  return _menubar;
}

EZWindow *EZMainWindow::getStatusBar()
{
  if(_statusbar) return _statusbar;

  _statusbar = new EZStatusBar();
  ((EZStatusBar *)_statusbar)->create(this,"",-1);

  // add to layout

  if(getLayout()) ((EZMainWindowLayout *)getLayout())->setStatusBar(_statusbar);

  return _statusbar;
}
EZWindow *EZMainWindow::getToolBar()
{
  if(_toolbar) return _toolbar;


  _toolbar = new EZToolBar();

  ((EZToolBar *)_toolbar)->create(this,"toolbar",0);

  // add to layout
  if(getLayout()) ((EZMainWindowLayout *)getLayout())->setToolBar(_toolbar);

  return _toolbar;
}

bool EZMainWindow::setIcon(EZIcon &icon)
{
  return SetClassLong(_window,GCL_HICON,(LPARAM)icon.getHandle()) != 0;
}

void EZMainWindow::onDestroy(EZEvent *ev)
{
	getApp()->quit();
}

void EZMainWindow::onSize(EZEvent *ev)
{
	EZWindow::onSize(ev);
}

void EZMainWindow::onCreate(EZEvent *ev)
{
  rethinkLayout();
}
