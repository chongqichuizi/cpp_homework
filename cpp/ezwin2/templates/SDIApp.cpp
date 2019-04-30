//-- MYAPP.h
#ifndef MYAPP_H
#define MYAPP_H

#include <ezmainwindow.h>

class MYAPP_MainWindow : public EZMainWindow
{
public:
  MYAPP_MainWindow(const char *name);
  virtual ~MYAPP_MainWindow();
protected:
  virtual void onPreCreate(CREATESTRUCT *cs);
  virtual void onCreate(EZEvent *ev);
};  

#endif //MYAPP_H 

//--------------------------------------------
// MYAPP.cpp

//#include "MYAPP.h"
#include <ezapp.h>
#include <ezmenubar.h>
#include <ezmenu.h>
#include <eztoolbar.h>
#include <ezstatusbar.h>
#include <ezlayout.h>

#include <eztextedit.h>

MYAPP_MainWindow::MYAPP_MainWindow(const char *name)
 : EZMainWindow(name)
{

}
MYAPP_MainWindow::~MYAPP_MainWindow()
{
}
void MYAPP_MainWindow::onPreCreate(CREATESTRUCT *cs)
{
  // TODO: set any things we want to change in the mainwindow 
  // ie: styles, x,y,w,h etc
}
void MYAPP_MainWindow::onCreate(EZEvent *ev)
{
  // adding the menubar etc
  EZMenuBar *menubar = (EZMenuBar *)getMenuBar();

  // loadmenubar
  //menubar->loadMenuBar(this, resourceid);

  // or create by hand
  EZMenu *menu = new EZMenu(this,"mymenu");
  menu->addItem("&Exit",100);
  menubar->addMenu("&File", menu);

  // must redraw after a menuchange
  menubar->redraw();

  // the toolbar
  EZToolBar *toolbar = (EZToolBar *)getToolBar();
  
  // the statusbar
  EZStatusBar *statusbar = (EZStatusBar *)getStatusBar(); 

  // get the layout manager so we can add our client area to it
  EZMainWindowLayout *layout = (EZMainWindowLayout *)getLayout(); 

  // add the sdi client - in our case, a text editor
  EZTextEdit *text = new EZTextEdit(this,"sometext");

  // add the client to the layout
  layout->setMainWindow(text);

}

// the main for windows
//
int PASCAL WinMain(HINSTANCE hCurInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nCmdShow)
{
   // create the app
   EZApplication app(hCurInstance,"MYAPP");
   
   // open up the mainwindow
   EZWindow * win = new MYAPP_MainWindow("My App WIndow");

   // set the main window
   app.setMainWindow(win);

   // make it visible  // wont be done here .. but tell it we want to be seen :)
   win->show();

   // run everything
   return app.run();
} 