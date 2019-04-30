

/***********************************************************
 * EZWIN2
 *
 * Name:      eztimer.h
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

#ifndef eztimer_h
#define eztimer_h

#include <ezwin.h>

class EZWindow;

class DLL_EXP EZTimer
{
  EZWindow *_win;
  unsigned int _timerid;
  bool _oneshot;

 public:
	 // NOTE: currently timer cant be oneshot
   EZTimer(EZWindow *win,bool oneshot=true);
   virtual ~EZTimer();

   
   bool start(unsigned int timeval);
   void stop();
};

#endif // eztimer_h
