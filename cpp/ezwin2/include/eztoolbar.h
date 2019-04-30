
/***********************************************************
 * EZWIN2
 *
 * Name:      eztoolbar.h
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

#ifndef eztoolbar_h
#define eztoolbar_h

#include <ezwindow.h>

#include <commctrl.h>
#include <ezimagelist.h>

class DLL_EXP EZToolBar
: public EZWindow
{
public:
  int setButtonState(int id, int state);
  int getButtonState(int id);

  // TBSTYLE_BUTTON,  TBSTYLE_CHECK, TBSTYLE_DROPDOWN, TBSTYLE_SEP
  void addButton(UINT bmapid, int buttonid, int style=TBSTYLE_BUTTON);

  EZToolBar(); 
  virtual ~EZToolBar();

  virtual bool create(EZWindow *parent,const char *name="",int id=-1);

  void addStdButton(int bmapid,int buttonid=-1);
  void addSeperator();

protected:
	virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif // eztoolbar_h