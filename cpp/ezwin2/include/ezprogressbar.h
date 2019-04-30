

/***********************************************************
 * EZWIN2
 *
 * Name:      ezprogressbar.h
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

#ifndef ezprogressbar_h
#define ezprogressbar_h

#include <ezwindow.h>

class DLL_EXP EZProgressBar
: public EZWindow
{
  long _pos;
public:
  EZProgressBar();
  
  bool create(EZWindow *parent,char *name,const EZRect &rect = EZRect(), int id=-1);

  virtual ~EZProgressBar();

  void setRange(long rn);
  void setPos(long pos);
protected:
  virtual void onCreate(EZEvent *ev);
  virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif // ezprogressbar_h
