

/***********************************************************
 * EZWIN2
 *
 * Name:      ezmdiwindow.h
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

#ifndef ezmdiwindow_h
#define ezmdiwindow_h

#include <ezwin.h>
#include <ezwindow.h>

class DLL_EXP EZMDIWindow : public EZWindow
{
public:
	void MDIClose(EZWindow *w);
  EZMDIWindow();
  
  bool create(EZWindow *parent);

  virtual ~EZMDIWindow();


	void MDIActivate(EZWindow *w);
	EZWindow * MDIGetActive();
	void MDIPrev();
	void MDINext();
	void MDIMaximise(EZWindow *w);
	void MDIRestore(EZWindow *w);
	void MDITile(int flags);
	void MDICascade(int flags = 0);

protected:
	virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif //ezmdiwindow_h