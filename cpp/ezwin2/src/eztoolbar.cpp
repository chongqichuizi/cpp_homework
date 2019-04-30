#include <eztoolbar.h>
#include <ezapp.h>
#include <commctrl.h>

#include <ezevent.h>


EZToolBar::EZToolBar()
{

}
EZToolBar::~EZToolBar()
{

}
bool EZToolBar::create(EZWindow *parent,const char *name,int id)
{
  unsigned long flags = WS_BORDER | WS_VISIBLE | CCS_TOP; 
  // | CCS_NODIVIDER;
  //CCS_TOP; // | CCS_NORESIZE | WS_CLIPSIBLINGS;

  if(parent) flags |= WS_CHILD;

  bool ok = EZWindow::create(parent,name,flags,EZRect(CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT),id);

  TBADDBITMAP bminfo = { HINST_COMMCTRL, /*IDB_STD_LARGE_COLOR*/ IDB_STD_SMALL_COLOR };

  sendMessage(TB_BUTTONSTRUCTSIZE,sizeof(TBBUTTON),0);
  sendMessage(TB_ADDBITMAP,1,(LPARAM)&bminfo);

  return ok;
}
void EZToolBar::onPreCreate(CREATESTRUCT *cs)
{
	static const char * classname = TOOLBARCLASSNAME;
	cs->lpszClass = classname;

	cs->style |= (WS_BORDER | WS_VISIBLE | CCS_TOP);
}

/*
#define STD_CUT                 0
#define STD_COPY                1
#define STD_PASTE               2
#define STD_UNDO                3
#define STD_REDOW               4
#define STD_DELETE              5
#define STD_FILENEW             6
#define STD_FILEOPEN            7
#define STD_FILESAVE            8
#define STD_PRINTPRE            9
#define STD_PROPERTIES          10
#define STD_HELP                11
#define STD_FIND                12
#define STD_REPLACE             13
#define STD_PRINT               14
*/
void EZToolBar::addStdButton(int bmapid,int buttonid)
{
  TBBUTTON btn = { bmapid,buttonid,TBSTATE_ENABLED,TBSTYLE_BUTTON,{0,0},0,0};

  sendMessage(TB_INSERTBUTTON,-1,(LPARAM)&btn);
  return;
}

void EZToolBar::addSeperator()
{
  TBBUTTON btn = { 0,0,TBSTATE_ENABLED,TBSTYLE_SEP,{0,0},0,0};
  sendMessage(TB_INSERTBUTTON,-1,(LPARAM)&btn);
  return;
}


void EZToolBar::addButton(UINT bmapid, int buttonid, int style)
{
  // load and add the bitmap
  TBADDBITMAP bm;
  bm.hInst = EZApp->getInstance();
  bm.nID = bmapid;

  int bm_index = sendMessage(TB_ADDBITMAP, 1, (LPARAM)&bm);

  TBBUTTON btn = { bm_index,buttonid,TBSTATE_ENABLED,style, 0,0};

  sendMessage(TB_INSERTBUTTON,-1,(LPARAM)&btn);
}

int EZToolBar::getButtonState(int id)
{
  // get state of the button - -1 if it failed
  return sendMessage(TB_GETSTATE, (WPARAM)id, 0);
}

int EZToolBar::setButtonState(int id, int state)
{
  return sendMessage(TB_SETSTATE,(WPARAM)id,MAKELONG(state,0));
}
