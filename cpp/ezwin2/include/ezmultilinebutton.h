
/***********************************************************
 * EZWIN2
 *
 * Name:      ezmultilinebutton.h
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

#ifndef ezmultilinebutton_h
#define ezmultilinebutton_h

#include <ezwindow.h>

class DLL_EXP EZMultilineButton : public EZWindow
{
  bool selected;
  bool capture;

public:
  EZMultilineButton();
  
  bool create(EZWindow *parent,const char *name,
	  const EZRect &rect = EZRect(),int id=-1);

  ~EZMultilineButton();

protected:
  virtual void onPaint(EZEvent *ev);
  virtual void onMouseDown(EZEvent *ev, int button);
  virtual void onMouseUp(EZEvent *ev, int button);
  virtual void onMouseMove(EZEvent *ev);
  virtual void onSetText(EZEvent *ev);
};

#endif //ezmultilinebutton_h