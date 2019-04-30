
/***********************************************************
 * EZWIN2
 *
 * Name:      ezdragbar.h
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

#ifndef ezdragbar_h
#define ezdragbar_h

#include <ezwindow.h>
#include <ezlayout.h>
#include <ezsize.h>

class DLL_EXP EZDragBar
  : public EZWindow, public EZLayout
{
  EZRect _drag;
  bool _moving;
  bool _vert;

  int _dragpos;

  EZWindow *_left,*_right;

public:
  EZDragBar(); 
  virtual ~EZDragBar();

  bool create(EZWindow *parent,const char *name,bool vert=true);

  EZWindow * getRightPane();
  EZWindow * getLeftPane();
  EZWindow * getTopPane();
  EZWindow * getBottomPane();

  void setLeftPane(EZWindow *w);
  void setRightPane(EZWindow *w);
  //
  void setTopPane(EZWindow *w);
  void setBottomPane(EZWindow *w);

  bool setDragPos(int pos);
  int getDragPos();

  bool setDragRatioPos(int pos); // set pos between 0 - 100%
  int getDragRatioPos();

protected:
  virtual void onPaint(EZEvent *ev);
  virtual void onSize(EZEvent *ev);
  virtual void onMouseDown(EZEvent *ev,int button);
  virtual void onMouseUp(EZEvent *ev,int button);
  virtual void onMouseMove(EZEvent *ev);
  virtual void onSetFocus(EZEvent *ev);
  virtual void onCreate(EZEvent *ev);

  // layout functionality
  void doLayout();
};

#endif  // ezdragbar_h
