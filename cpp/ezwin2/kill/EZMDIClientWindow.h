

/***********************************************************
 * EZWIN2
 *
 * Name:      ezmdiclientwindow.h
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

#ifndef ezmdiclientwindow_h
#define ezmdiclientwindow_h

#include <ezwin.h>
#include <ezwindow.h>

class DLL_EXP EZMDIClientWindow : public EZWindow
{
public:
  EZMDIClientWindow();
  
  bool create(EZWindow *parent);

  virtual ~EZMDIClientWindow();

protected:
  virtual LRESULT processDefaultMessage(UINT uMessage,EZEvent *msg);

  virtual void onCreate(EZEvent *ev);
  virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif //ezmdiclientwindow_h