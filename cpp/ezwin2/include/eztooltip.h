
/***********************************************************
 * EZWIN2
 *
 * Name:      eztooltip.h
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

#ifndef eztooltip_h
#define eztooltip_h

#include <ezwindow.h>
#include <commctrl.h>

class DLL_EXP EZToolTip : public EZWindow
{
public:
  bool remTool(EZWindow *w, int ID);
  bool remTool(EZWindow *wnd);

  bool addTool(EZWindow *window,const EZRect &rect,int id, LPSTR text=LPSTR_TEXTCALLBACK);
  bool addTool(EZWindow *window, LPSTR text=LPSTR_TEXTCALLBACK);

  EZToolTip();
  
  bool create(EZWindow *parent);

  virtual ~EZToolTip();
protected:
  virtual void onCreate(EZEvent *ev);
  void onPreCreate(CREATESTRUCT *cs);
};

#endif //eztooltip_h