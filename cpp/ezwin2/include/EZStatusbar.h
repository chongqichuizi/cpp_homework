
/***********************************************************
 * Name:      ezstatusbar.h
 * version:   0.1
 * date:      3 March 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezstatusbar_h
#define ezstatusbar_h

 #include <ezwin.h>

#include <ezwindow.h>

class DLL_EXP EZStatusBar
 : public EZWindow
{
  //bool partmode;
public:
  EZStatusBar();
  virtual ~EZStatusBar();

  virtual bool create(EZWindow *parent,const char *text, int id=-1);
protected:
  virtual void onPreCreate(CREATESTRUCT *cs);       
};



#endif // ezstatusbar_h
