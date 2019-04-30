
/***********************************************************
 * EZWIN2
 *
 * Name:      ezcolourbutton.h
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
#ifndef ezcolourbutton_h
#define ezcolourbutton_h

#include <ezwindow.h>
#include <ezbrush.h>

class DLL_EXP EZColourButton : public EZWindow
{
public:
  EZColourButton();
  
  bool create(EZWindow *parent,const EZBrush &colour=RGB(0,0,0), const EZRect &rect = EZRect(), int id=-1);

  virtual ~EZColourButton();

  void setColour(const EZBrush &colour);
  EZBrush getColour();
protected:
  virtual void onPaint(EZEvent *ev);
  virtual void onMouseDown(EZEvent *ev, int button);
  virtual void onMouseUp(EZEvent *ev, int button);
  virtual void onMouseMove(EZEvent *ev);
private:
  bool capture;
  bool selected;
  EZBrush _colour;
};


#endif // ezcolourbutton_h