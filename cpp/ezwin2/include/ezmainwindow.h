

/***********************************************************
 * EZWIN2
 *
 * Name:      ezmainwindow.h
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

#ifndef ezmainwindow_h
#define ezmainwindow_h

#include <ezwin.h>

#include <ezwindow.h>
#include <ezicon.h>

class EZMenuBar;

class DLL_EXP EZMainWindow : public EZWindow
{
  EZWindow *_statusbar;
  EZWindow *_toolbar;
  EZMenuBar *_menubar;
public:
  EZMainWindow();
  
  virtual bool create(const char *windowname,unsigned long flags=WS_OVERLAPPEDWINDOW,const EZRect &rect = EZRect());

  virtual ~EZMainWindow();

  EZWindow *getStatusBar();
  EZWindow *getToolBar();
  EZMenuBar *getMenuBar();

  bool setIcon(EZIcon &icon);  	 

protected:
  virtual void onCreate(EZEvent *ev);
  virtual void onPreCreate(CREATESTRUCT *cs);

  virtual void onSize(EZEvent *ev);
  virtual void onDestroy(EZEvent *ev);
};

#endif // ezmainwindow_h
