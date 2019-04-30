/**********************************************************
 * test.cpp
 *
 * (c) 2000, John Donoghue
 *
 * A simple demonstration program using EZWin.
 *
 * Creates a main window and displays the text "Hello World" in it.
 */

// include a few needed headers
#include <ezapp.h>
#include <ezwindow.h>
#include <ezgfx.h>
#include <eztimer.h>
#include <ezbitmap.h>
#include <eztaskbaricon.h>
#include <ezevent.h>
#include <ezmenu.h>
#include <ezconfig.h>
#include <ezimagewin.h>
#include <ezbutton.h>

#include <ezmainwindow.h>

class TESTWindow
  : public EZWindow
{
public:
  TESTWindow();
  virtual ~TESTWindow();
  EZTimer *timer;
  EZBitmap *heart;
  EZPopupMenu *menu;
  EZTaskbarIcon *taskicon;
protected:
  virtual void onPaint(EZEvent *ev);
  virtual void onTimer(EZEvent *ev);
  virtual void onUser(EZEvent *ev);
  virtual void onDestroy(EZEvent *ev)
  {
     //delete icon;
     delete timer;
     delete taskicon;
     delete menu;
     EZApp->quit();
  }
  virtual void onMouseUp(EZEvent *ev,int button)
  {
    if(button==2) menu->show();
  }
};

TESTWindow::TESTWindow()
 : EZWindow(0,"TESTClass","Test")
{
  registerClass();
  create("Test",WS_OVERLAPPEDWINDOW,0,0,180,150);

  heart = new EZBitmap(1);

  timer = new EZTimer(this,false);
  timer->start(1000);

  taskicon = new EZTaskbarIcon(this,1,"Test",WM_USER);

  menu = new EZPopupMenu(this,"Properties");
  menu->addItem("Close menu",101);
  menu->addSeparator();
  menu->addItem("Quit",102);

  EZImageWindow *imagewin = new EZImageWindow(this,1, 100,0,100,100);
  EZButton * button = new EZButton(this,"Press me",1,80,100,50);
}
TESTWindow::~TESTWindow()
{
}
void TESTWindow::onTimer(EZEvent *ev)
{
  //redraw();
}
void TESTWindow::onUser(EZEvent *ev)
{
     if(ev->getLParam()==WM_RBUTTONDOWN)
     {
       //POINT p = getMousePos();
       // display popup menu here
       MessageBeep(0xFFFFFFFF);
       menu->show();
     }
}
void TESTWindow::onPaint(EZEvent *ev)
{
  EZGfx painter(this);
  EZRect rect = getClientRect();
}

/*
 * create a main window type with our special processing in it.
 * we want to know when to paint and when to close the application
 */
class MyWindow : public EZMainWindow
{
public:
  MyWindow();
  virtual ~MyWindow();
protected:
  virtual void onPaint(EZEvent *ev);
  virtual void onDestroy(EZEvent *ev);
};

// constructor - give ourselves a title
// would also create any child windows here
MyWindow::MyWindow()
: EZMainWindow("MyWindow")
{

}
MyWindow::~MyWindow()
{

}

// function called each time a paint is required
void MyWindow::onPaint(EZEvent *ev)
{
   EZGfx painter(this);

   EZRect rect = getClientRect();

   painter.drawText("Hello World", rect, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
}
// function called when the window is closed.
void MyWindow::onDestroy(EZEvent *ev)
{
   getApp()->quit();
}

// starting function for windows
int PASCAL WinMain(HINSTANCE hCurInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nCmdShow)
{
   // create the app
   EZApplication app(hCurInstance,"Test");

   // open up the mainwindow
   //EZWindow * win = new TESTWindow();
   EZWindow * win = new MyWindow();

   // set the main window
   app.setMainWindow(win);

   // make it visible  // wont be done here :)
   win->show();

   // run everything
   return app.run();
}
/*
int PASCAL WinMain(HINSTANCE hCurInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nCmdShow)
{
   // create the app
   EZApplication app(hCurInstance,"Test");

   EZConfig c(EZConfig::EZCONFIG_CURRENT_USER);

   EZConfig info = c.createKey("Software\\Cupid\\info");

   string s,p;
   info.getStringValue("hello",p);

   info.setStringValue("Hello","World");

   info.flush();

   // open up the mainwindow
   EZWindow * win = new TESTWindow();

   // set the main window
   app.setMainWindow(win);

   // make it visible  // wont be done here :)
   win->show();

   // run everything
   return app.run();
}
*/