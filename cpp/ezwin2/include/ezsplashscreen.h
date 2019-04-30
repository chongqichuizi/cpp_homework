

/***********************************************************
 * EZWIN2
 *
 * Name:      ezsplashscreen.h
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

#ifndef ezsplashscreen_h
#define ezsplashscreen_h

#include <ezwindow.h>

class DLL_EXP EZSplashScreen
 : EZWindow
{
public:
  EZSplashScreen();
  
  bool create(int timeout);
  virtual ~EZSplashScreen();
protected:
	virtual void onCreate(EZEvent *ev);
  virtual void onTimer(EZEvent *ev);
  virtual void onPreCreate(CREATESTRUCT *cs);
};


#endif // ezsplashscreen_h
