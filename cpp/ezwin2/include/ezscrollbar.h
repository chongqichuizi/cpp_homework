

/***********************************************************
 * EZWIN2
 *
 * Name:      ezscrollbar.h
 * version:   0.1
 * date:      15 March 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezscrollbar_h
#define ezscrollbar_h

#include <ezwindow.h>

// NOTE: DONT call close and size on a windows scrollbars - as will change the 
// window NOT the scrollbar

class DLL_EXP EZScrollBar : public EZWindow
{
  friend EZWindow;
public:
  typedef enum { HORIZONTAL=SBS_HORZ, VERTICAL=SBS_VERT } EZScrollType;

  EZScrollBar();
  
  bool create(EZWindow *parent, EZScrollType type=VERTICAL, int scrollflags=0, int id=-1);
  virtual ~EZScrollBar();  

  int getScrollPage();
  bool setScrollPos(int pos, bool refresh=false);

  int getTrackPos();
  int getScrollPos();

  int getMax();

  bool setScrollInfo(LPSCROLLINFO lpsi, bool refresh=false);

  virtual bool hide();
  virtual bool show();

  bool getScrollInfo(LPSCROLLINFO lpsi);

  // get a window scrollbar
  static EZScrollBar * getScrollBar(EZWindow *window, EZScrollType type);

private:

  bool _control_only;
  EZScrollType _type;  

protected:
	virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif // ezscrollbar_h