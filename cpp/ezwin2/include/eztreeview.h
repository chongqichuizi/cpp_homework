

/***********************************************************
 * EZWIN2
 *
 * Name:      eztreeview.h
 * version:   0.1
 * date:      20 April 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef eztreeview_h
#define eztreeview_h

#include <ezwindow.h>

#include <commctrl.h>
#include <ezimagelist.h>

class EZTreeView;

class DLL_EXP EZTreeViewItem
{
  HTREEITEM _handle;
  EZTreeView *_tree;
public:
  std::string getItemText();
  void * getItemData();
  void setItemData(void *data);
  void setItemImage(int imagenum);

  EZTreeViewItem(EZTreeView *treeview,EZTreeViewItem *parent,char *text);
  virtual ~EZTreeViewItem();
};


class DLL_EXP EZTreeView : public EZWindow
{
  EZTreeViewItem *root;
public:
  void setImageList(const EZImageList &I);

  EZTreeView();
  
  bool create(EZWindow *parent,const char *name,bool showroot=true);

  virtual ~EZTreeView();

  EZTreeViewItem addItem(EZTreeViewItem *parentitem,char *item);

  EZTreeViewItem *getRoot() { return root; }
protected:
  virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif // eztreeview_h
