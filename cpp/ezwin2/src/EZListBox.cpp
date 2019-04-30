// EZListBox.cpp: implementation of the EZListBox class.
//
//////////////////////////////////////////////////////////////////////

#include "EZListBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EZListBox::EZListBox()
{
}

bool EZListBox::create(EZWindow *parent,char *name,const EZRect &rect,int id)
{
    return EZWindow::create(parent, name,WS_VISIBLE|WS_VSCROLL|LBS_NOINTEGRALHEIGHT,rect,id);

	// LBS_NOTIFY LBS_SORT
}

EZListBox::~EZListBox()
{

}
void EZListBox::addItem(const char *str)
{
	if(!str) return;

	sendMessage(LB_ADDSTRING,0,(LPARAM)str);
}

int EZListBox::getCount()
{
	LPARAM p = sendMessage(LB_GETCOUNT,0,0);

	if(p== LB_ERR) return 0;

	return p;
}

void EZListBox::onPreCreate(CREATESTRUCT *cs)
{
  static const char * classname = "LISTBOX";

  cs->lpszClass = classname;
}
