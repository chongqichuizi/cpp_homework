

/***********************************************************
 * Name:      ezmdichildwindow.h
 * version:   0.1
 * date:      10 March 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezmdichildwindow_h
#define ezmdichildwindow_h

#include <ezwindow.h>

class DLL_EXP EZMDIChildWindow : public EZWindow
{
public:
  EZMDIChildWindow();
  
  bool create(EZWindow *parent,const char *name, const EZRect &rect = EZRect());

  virtual ~EZMDIChildWindow();
protected:
  virtual LRESULT processDefaultMessage(UINT message, EZEvent *ev);

  virtual void onClose(EZEvent *ev);
  virtual void onDestroy(EZEvent *ev);
  virtual void onPreCreate(CREATESTRUCT *cs);
  virtual void onCreate(EZEvent *ev);
};
#endif // ezmdichildwindow_h