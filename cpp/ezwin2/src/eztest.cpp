
/***********************************************************
 * Name:      ezapp.h
 * version:   0.1
 * date:      3 March 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#include <ezapp.h>
#include <ezmainwindow.h>
#include <ezdialog.h>
#include <ezgfx.h>
#include <ezpane.h>
#include <ezbutton.h>

#include <ezlayout.h>

#include <windows.h>
#include <ezlineedit.h>
#include <ezmenu.h>
#include <ezmenubar.h>

#include <EZMDIClientWindow.h>
#include <EZMDIChildWindow.h>

#include <ezmultilinebutton.h>
#include <eztooltip.h>

#include <ezscrollbar.h>
#include <ezsimplescrollwindow.h>

#include <eztextedit.h>

#include <ezevent.h>

class DrawWin : public EZPane
{
public:
	DrawWin() {}
	
	bool create(EZWindow *parent) //: EZPane(parent) 
	{ 
		bool ok = EZPane::create(parent,EZRect(0,0, 400, 334));

		setRect( EZRect(0,0, 400, 334) );
		
		return ok;
	}
	virtual ~DrawWin() {}

	virtual void onPreCreate(CREATESTRUCT *cs)
	{
		EZPane::onPreCreate(cs);

	  cs->style |= WS_BORDER;
	}

    virtual void onPaint(EZEvent *ev)
	{
	   EZGfx painter(this);

	   EZRect rect = getClientRect();

	   painter.setPen(EZPen(RGB(0xff,0,0), PS_SOLID, 5) );

	   painter.drawRect(rect);
	}
};

//#include "resource.h> SetWindowLong
LPSTR te = "My text here :)";

class TESTWindow
  : public EZMainWindow
{
	EZMDIClientWindow *mdi;
	EZToolTip *tooltip;
public:
	TESTWindow() {}
	//: EZMainWindow("Test") {}
  virtual ~TESTWindow() {}

  bool create()
  {
	  return EZMainWindow::create("Test"); //,WS_BORDER);
  }
protected:
  virtual void onNotify(EZEvent *ev)
  {
	  int idCtrl = (int) ev->getWParam(); 
      LPNMHDR pnmh = (LPNMHDR) ev->getLParam();

	  if(pnmh->code == TTN_NEEDTEXT /*vc - TTN_GETDISPINFO*/)
	  {
	    //vc LPNMTTDISPINFO lpnmtdi = (LPNMTTDISPINFO)ev->getLParam();
       LPTOOLTIPTEXT lpnmtdi = (LPTOOLTIPTEXT)ev->getLParam();


		lpnmtdi->lpszText = te;
		lpnmtdi->hinst = 0;
		if(lpnmtdi->uFlags & TTF_IDISHWND)
		{
			// id is a window handle
		}
		else
		{ // is an ID

		}
		
	  }
	  //processDefault();
  }
  virtual void onPaint(EZEvent *ev)
  {
      EZGfx painter(this);
      EZPen pen(RGB(0xff,0,0), PS_SOLID, 3);
      EZBrush brush = EZBrush::white(); //(RGB(0,0xff,0));

	  //EZBrush *b = new EZBrush(brush);

	  EZPen oldp = painter.setPen( pen );
	  EZBrush oldb = painter.setBrush( brush );

	  painter.setTextColour(EZPen(RGB(0xff,0,0xff)));
	  EZPen p = EZPen::white();

	  painter.setBkColour(EZPen(RGB(0,0,0xff)));

	  painter.setBkMode(TRANSPARENT);

//	  painter.drawText("Hello world",EZPoint(10,10),DT_LEFT);
	  painter.drawRect(10,40,200,60);
	  painter.fillRect(10,65,100,75, RGB(0,0xff,0xff));

	  //TextOut(painter.getHandle(), 200,10,"Hello World", 12);

	  painter.moveTo(10,80);
	  painter.lineTo(100,80);

	  painter.setPen(oldp);
	  painter.setBrush(oldb);

  }
//  virtual void onTimer(EZEvent *ev);
//  virtual void onUser(EZEvent *ev);
  virtual void onDestroy(EZEvent *ev)
  {
     getApp()->quit();
	  //EZApp->quit();
  }
//  virtual void onTimer(EZEvent *ev)
//  {
//    EZDialog::showAskDialog(this,"Timer","What are you doing here? ");     
//  }
  virtual void onCreate(EZEvent *ev)
  {
//    int x;
//
//	x++;
//    EZDialog::showAskDialog(this,"Hello","What are you doing here? ");

//	Beep(100,400);
	  EZMenuBar * mb = (EZMenuBar *)getMenuBar();
	  EZMenu * m = new EZMenu(); //this);
	  m->create(this,"X");
	  m->addItem("quit");

	  mb->addMenu("File", m);

	  mb->redraw();

	  mdi = new EZMDIClientWindow();
	  mdi->create(this);
	  mdi->setRect( EZRect(200,0,700, 500) );

      EZMDIChildWindow *mdichild = new EZMDIChildWindow();
	  mdichild->create(mdi->getFirstChild(),"Test",EZRect()); //200,0, 200,200);
	  EZLineEdit *line = new EZLineEdit();
	  line->create(mdichild,"Hello text is here :)");

	  //mdi->redraw();

	  mdichild->setRect( EZRect( 50,50, 200,200) );

	  EZPane *p = new EZPane();
	  p->create(this);
	  //EZColumnLayout *layout = new EZColumnLayout(p);
	  EZRowLayout *layout = new EZRowLayout(p);
      //layout->setWidth(0,10);
      //layout->setWidth(1,30);
      //layout->setWidth(2,20);
	  p->setLayout( layout );
	  p->setRect( EZRect(10,50,200, 100) );

	  EZButton *b = new EZButton();
	  b->create(p,"hello",EZRect(0,0,50,30));
	  b = new EZButton();
	  b->create(p,"hello2",EZRect(0,0,50,30));
	  b = new EZButton();
	  b->create(p,"hello3",EZRect(0,0,50,30));
	  b->hide();
	  p->rethinkLayout();


	  //SetWindowLong( p->getHandle(), GWL_STYLE, WS_CHILD|WS_BORDER);

      EZMultilineButton * mlb = new EZMultilineButton();
	  mlb->create(this,"My Button is here\nso lets see if it\nwill actually work !!!",201);
	  mlb->setRect( EZRect(10,150,180,250) );

      tooltip = new EZToolTip();
	  tooltip->create(this);
      tooltip->addTool(mlb);

	  tooltip->addTool(b,"Hello");

	  tooltip->addTool(this,EZRect(0,0,30,30),100,"Square");
	  tooltip->addTool(this,EZRect(30,0,60,30),101,"My Button is here\r\nso lets see if it\r\nwill ");

	  EZScrollBar *scroll = new EZScrollBar();
	  scroll->create(this, EZScrollBar::VERTICAL, 0, 1000);
	  scroll->setRect( EZRect(10,260,30,350) );

	  EZScrollBar::getScrollBar(this,EZScrollBar::VERTICAL);

	  EZSimpleScrollWindow *swin = new EZSimpleScrollWindow();
	  swin->create(this);
	  swin->setRect( EZRect(10,360,200,500) );

	  //EZTextEdit *t = new EZTextEdit(swin, "test", 20, 50, 200,400);
      DrawWin *win = new DrawWin();
	  win->create(swin);

	  swin->rethinkLayout();

  }
  virtual void onChar(EZEvent *ev)
  {
//	  EZDialog::showOKCancelDialog(this,"Title","Help me");
      char buff[25] = "1";

     EZDialog::showFileDialog(this, "file", buff);
	  int x = EZDialog::showInputDialog(this,"Title","Eneter a number scum bag", buff, 20);

	  tooltip->remTool(this,101);

     //EZDialog::showLastError(this);
     
	  //showDialog(this,IDD_EZINPUT_DIALOG);

//	  buff[1] = 0;
/*
	  Beep(220,100);

      FINDREPLACE fr;
   char buffer[80] = "find string";
// Initialize FINDREPLACE
ZeroMemory(&fr, sizeof(FINDREPLACE));
fr.lStructSize = sizeof(FINDREPLACE);
fr.hwndOwner = this->getHandle();
fr.lpstrFindWhat = "Find String";
fr.wFindWhatLen = 80;
fr.Flags = 0;


      HWND w = FindText(&fr);

*/

  }
//  virtual void onMouseUp(EZEvent *ev,int button)
//  {
//    if(button==2) menu->show();
//  }
};


int PASCAL WinMain(HINSTANCE hCurInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nCmdShow)
{
   // create the app
   EZApplication app(hCurInstance,"Test");
   
   // open up the mainwindow
   TESTWindow * win = new TESTWindow();

   win->create();

   // set the main window
   //app.setMainWindow(win);

   // make it visible  // wont be done here :)
   win->show();

   std::string s = "hello";

   // run everything
   return app.run();
}

