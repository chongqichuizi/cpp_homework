

/***********************************************************
 * EZWIN2
 *
 * Name:      ezimagewin.h
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

#ifndef EZIMAGEWIN_H
#define EZIMAGEWIN_H

#include <ezwin.h>

#include <ezwindow.h>
#include <ezbitmap.h>

class DLL_EXP EZImageWindow
 : public EZWindow
{
public:
  EZImageWindow();
  
  bool create(EZWindow *parent,DWORD bmresource,const EZRect &rect=EZRect());

  virtual ~EZImageWindow();

protected:
  virtual void onPaint(EZEvent *ev);
  virtual void onPreCreate(CREATESTRUCT *cs);
private:
  EZBitmap *bitmap;  
};

#endif // EZIMAGEWIN_H
