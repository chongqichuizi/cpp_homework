

/***********************************************************
 * EZWIN2
 *
 * Name:      ezsimplescrollwindow.h
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

/*
 * a simple one child scroll area - will scroll a single child around the 
 * view
 *
 * this would work later with a view window that has many children
 */

#ifndef ezsimplescrollwindow_h
#define ezsimplescrollwindow_h

#include <ezwindow.h>

class EZScrollBar;

class DLL_EXP EZSimpleScrollWindow : public EZWindow
{
  EZScrollBar * vscroll;
  EZScrollBar * hscroll;
public:
	virtual void rethinkLayout();
  EZSimpleScrollWindow();
  
  bool create(EZWindow *parent);

  virtual ~EZSimpleScrollWindow();

protected:
  virtual void onSize(EZEvent *ev);
  virtual void onScroll(EZEvent *ev, int type);
  virtual void onCreate(EZEvent *ev);
  virtual void onPreCreate(CREATESTRUCT *cs);
private:
  void calcScrollBarPos();
};

#endif //ezsimplescrollwindow_h