
/***********************************************************
 * Name:      ezezample.cpp
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
#include <ezevent.h>
#include <ezwindow.h>
#include <ezbutton.h>

#include <ezmainwindow.h>
#include <ezmenubar.h>

#include <ezlayout.h>
#include <ezdragbar.h>
#include <eztextedit.h>

#include "ezexampleresource.h"

#include <ezdialog.h>


#include <eztreeview.h>
#include <ezlistview.h>
#include <ezlineedit.h>
#include <eztextedit.h>
#include <ezbutton.h>
#include <ezmenubar.h>
#include <ezmenu.h>
#include <ezstatusbar.h>
#include <eztoolbar.h>
#include <ezclientwindow.h>

#include <ezdragbar.h>
#include <ezcombobox.h>

#include <ezlistbox.h>
#include <ezimagelist.h>

#include <ezlayout.h>

#include "ezexampleresource.h"

#include <ezmultilinebutton.h>
#include <ezimagelist.h>



class ExampleWindow
  : public EZMainWindow
{

  EZTreeView tree;
  EZListView list;
  EZLineEdit lineedit;
  EZTextEdit textedit;
  EZButton   *button;
  EZMenuBar  *menubar;
  EZDragBar dragbar;
  EZPopupMenu popup;
  EZStatusBar  *statusbar;
  EZToolBar *toolbar;
  EZClientWindow    clientwindow;
  EZListBox listbox;
  EZComboBox combobox;

  EZTextEdit t1,t2;

  EZImageList imagelist;
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
//  virtual void onPaint(EZEvent *ev);
//  virtual void onTimer(EZEvent *ev);
//  virtual void onUser(EZEvent *ev);
  virtual void onDestroy(EZEvent *ev);

  virtual void onCreate(EZEvent *ev);

  virtual void onChar(EZEvent *ev);

  virtual void onMouseUp(EZEvent *ev, int button);

  virtual void onControlAction(EZEvent *ev);
  virtual void onMenuSelect(EZEvent *ev);
};


int PASCAL WinMain(HINSTANCE hCurInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nCmdShow)
{
   // create the app
   EZApplication app(hCurInstance,"Example");
   
   // open up the mainwindow
   EZWindow * win = new EZMainWindow(); //ExampleWindow();

   //win->create(0,"hello",WS_BORDER|WS_CAPTION|WS_SYSMENU);

   ((EZMainWindow *)win)->create("Example");

   EZMenuBar *menubar = ((EZMainWindow *)win)->getMenuBar();

   menubar->create(win,IDR_MENU1);

   ((EZMainWindow *)win)->getToolBar();
   ((EZMainWindow *)win)->getStatusBar();

   EZMainWindowLayout *layout = (EZMainWindowLayout *)win->getLayout();

   // make it visible  // wont be done here :)
   win->show();

   EZDragBar db;
   db.create(win,"d",true);

   EZButton b;
   b.create(&db,"Hello",EZRect(10,10,400,200),101);

   db.setLeftPane(&b);

   b.show();
   
   EZTextEdit t;
   t.create(&db,"Hello",EZRect(10,10,400,200),101);

   db.setRightPane(&t);

   t.show();

   layout->setMainWindow(&db);

   win->rethinkLayout();

   // example window class
   ExampleWindow exwin;
   exwin.create("Example");
   exwin.show();


   // run everything
   return app.run();
}

ExampleWindow::ExampleWindow()
{
}
ExampleWindow::~ExampleWindow()
{
}
void ExampleWindow::onDestroy(EZEvent *ev)
{
	getApp()->quit();
}
void ExampleWindow::onCreate(EZEvent *ev)
{
    setIcon(EZIcon(IDI_ICON1));

//	EZMainWindowLayout * layout = (EZMainWindowLayout *)getLayout();
//	if(layout)
//	{
		//layout->
//		layout->setStatusbar(statusbar);
//		layout->setToolbar(toolbar);

		
//	statusbar = new EZStatusbar(this,"ok");
//	toolbar = new EZToolbar(this,"tools");

//	}

	// auto create stat and toolbar
    statusbar = (EZStatusBar *)this->getStatusBar();

	toolbar = (EZToolBar *)this->getToolBar();

	menubar = (EZMenuBar *)this->getMenuBar();

	clientwindow.create(this);

	EZMainWindowLayout * layout = (EZMainWindowLayout *)getLayout();
	if(layout)
	{
		layout->setMainWindow(&clientwindow);
	}

  	toolbar->addStdButton(STD_HELP,1);
    toolbar->addSeperator();
    toolbar->addStdButton(STD_FILEOPEN,2);
	toolbar->addButton(IDB_BITMAP1,201);

	menubar->create(this,IDR_MENU1);

	EZMenu * menu = new EZMenu();
	menu->create(this,"&Tools");
	menu->addItem("Tool1");
	menu->addSeparator();
	menu->addItem("Tool2",2000);

	menubar->addMenu("Tools", menu);
	menubar->redraw();


	tree.create(&clientwindow,"tree");
	tree.setRect( EZRect(10,10, 100, 200) );

	int pos = imagelist.addImage( EZIcon(IDI_ICON1) );
	tree.setImageList(imagelist);

	EZTreeViewItem it = tree.addItem(0,"Item0");
	it.setItemImage(pos);

	EZTreeViewItem x = tree.addItem(&it,"Item0_1");
    x.setItemImage(pos);
	tree.addItem(&it,"Item0_2");

	tree.addItem(0,"Item1");
	tree.addItem(0,"Item2");
	tree.addItem(0,"Item3");
	tree.addItem(0,"Item4");

	list.create(&clientwindow, "list");
	list.setRect( EZRect(10,210, 300, 400) );
	list.setColumns("Name", "Size", "Date");
	list.setViewMode( EZListView::ICON_VIEW );

	int row = list.addItem(0,"Hello");
	int row2 = list.addItem(0,"Hello2");
	EZImageList *imagelist = new EZImageList();

	list.setImageList(*imagelist);
    int p = imagelist->addImage( EZIcon(IDI_ICON1) );
    int p1 = imagelist->addImage( EZIcon(IDI_ICON2) );

	list.setImageList(*imagelist);
	EZListViewItem item = list.getItem(row);
	item.setItemImage(p);
    item = list.getItem(row2);
	item.setItemImage(p1);

	lineedit.create(&clientwindow,"Some edit text");
	lineedit.setRect( EZRect(110,10, 300, 30) );

    textedit.create(&clientwindow,"lots of text in here\r\nIsnt this great");
	textedit.setRect( EZRect(110,40, 300, 200) );

	button = new EZButton();
	button->create(&clientwindow,"Open File", EZRect(0,0,0,0), 1001);
	button->setRect( EZRect(310,10, 400, 30) );

	button = new EZButton();
	button->create(&clientwindow,EZIcon(IDI_ICON1));
	button->setRect( EZRect(310,40, 400, 100) );

	combobox.create(&clientwindow,"combo");
	combobox.setRect( EZRect(310,110, 400, 110 + 200) );

	combobox.addItem("hello1");
	combobox.addItem("hello2");
	combobox.addItem("hello3");
	combobox.addItem("hello4");


    dragbar.create(&clientwindow, "dragger");
	dragbar.setRect( EZRect(410,10, 600, 100) );
	
	t1.create(&dragbar,"left pane");
	dragbar.setLeftPane(&t1);
    //EZTextEdit t2;
	t2.create(&dragbar,"right pane");
	dragbar.setRightPane(&t2);
	dragbar.setDragRatioPos(50);
	dragbar.rethinkLayout();

	popup.create(&clientwindow,"popup");
	popup.addItem("An Item");
	popup.addItem("Another Item");
    popup.addSeparator();
	popup.addItem("And yet another Item");
    popup.addSeparator();
	popup.addItem("Exit",2000);

	listbox.create(&clientwindow,"list");
	listbox.setRect( EZRect(410,110,600,300) );
	listbox.addItem("Item 1");
	listbox.addItem("Item 2");
	listbox.addItem("Item 3");
	listbox.addItem("Item 4");
	listbox.addItem("Item 5");
	listbox.addItem("Item 6");
	listbox.addItem("Item 7");
	listbox.addItem("Item 8");
	listbox.addItem("Item 9");
	listbox.addItem("Item 10");
	listbox.addItem("Item 11");
	listbox.addItem("Item 12");
	listbox.addItem("Item 13");


	// make sure everything is recalced
	if(layout) rethinkLayout();


	EZMultilineButton *btn = new EZMultilineButton();
	
	btn->create(&clientwindow,"help\r\nme",EZRect(310,330,400,330+60),-1);
}
void ExampleWindow::onChar(EZEvent *ev)
{
	if(ev->getWParam() == '\t')
		Beep(220,100);

	EZDialog d;
	d.create(this, IDD_DIALOG1);

	d.show();

	//EZApp->tempWindow( getHandle() );
}

void ExampleWindow::onMouseUp(EZEvent *ev, int button)
{
//  if(button == 2) // Beep(220,100);
//	  EZDialog::showFileDialog(this,"Open file");
	if(button == 2 && popup.getHandle()!=0)
		popup.show();
}
void ExampleWindow::onControlAction(EZEvent *ev)
{
  //if(HIWORD(ev->getWParam()) == ) 
//	EZWindow * w = getApp()->findWindow((HWND)ev->getLParam());
//	if(w)
//	{
//		if(w->getID() == 1001)
//        //if((HWND)ev->getLParam()	  
//		  EZDialog::showFileDialog(this,"Open file");
//	}
	char buffer[1024] = "none.txt";
	if(LOWORD(ev->getWParam()) == 1001)
		EZDialog::showFileDialog(this,"Open file", buffer, EZDialog::OPEN);

}
void ExampleWindow::onMenuSelect(EZEvent *ev)
{
  if(LOWORD(ev->getWParam()) == ID_FILE_EXIT)
	  getApp()->quit();
}
