
/***********************************************************
 * EZWIN2
 *
 * Name:      ezbutton.h
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

#ifndef ezbutton_h
#define ezbutton_h

#include <ezwin.h> 

#include <ezwindow.h>
#include <ezicon.h>

class DLL_EXP EZButton : public EZWindow
{

public:
  EZButton();

  bool create(EZWindow *parent,const EZIcon &_icon,
	const EZRect &rect=EZRect(),int id=-1);

  bool create(EZWindow *parent,const char *label,
	const EZRect &rect=EZRect(),
	int id=-1);

  virtual ~EZButton();
protected:
  virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif // ezbutton_h
