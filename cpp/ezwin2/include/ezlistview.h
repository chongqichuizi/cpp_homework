
/***********************************************************
 * EZWIN2
 *
 * Name:      ezlistview.h
 * version:   0.1
 * date:      28 April 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezlistview_h
#define ezlistview_h

#include <ezwindow.h>
#include <commctrl.h>

#include <ezimagelist.h>

class EZListView;

class DLL_EXP EZListViewItem
{
	friend EZListView;

	int _index;
	EZListView *_parent;

public:
	void setItemImage(int imagenum);
	void setItemText(const char *text, int col=0);
	std::string getItemText(int col=0);

    virtual ~EZListViewItem() {}

	EZListViewItem(EZListView *listview, const char *text,int pos=-1);

	int getIndex() { return _index; }

	operator int() { return getIndex(); }

protected:
	EZListViewItem(EZListView *listview, int index);
};

class DLL_EXP EZListView
 : public EZWindow
{
public:
	EZListView();
	
	bool create(EZWindow *parent,char *text,const EZRect &rect = EZRect(), int id=-1);
  
	virtual ~EZListView();

    EZListViewItem addItem(int i,const char *text); // return pos or -1 if failed

	EZListViewItem getItem(int index);
	EZListViewItem findItem(const char *text,int startpos=-1);

	void arrangeIcons(UINT code=LVA_DEFAULT); // LVA_ALIGNLEFT , LVA_ALIGNTOP, LVA_DEFAULT, LVA_SNAPTOGRID
	void setImageList(const EZImageList &, int type=LVSIL_NORMAL);

	typedef enum { 
		ICON_VIEW=LVS_ICON, LIST_VIEW=LVS_LIST, DETAIL_VIEW=LVS_REPORT, SMALLICON_VIEW=LVS_SMALLICON
	} ViewMode;

    bool setViewMode(ViewMode mode);
  
    void setColumns(char *text1,char *text2=0,char *text3=0,char *text4=0);
protected:
	virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif // ezlistview_h