
/***********************************************************
 * EZWIN2
 *
 * Name:      ezclientwindow.h
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

#ifndef ezclientwindow_h
#define ezclientwindow_h

#include <ezwindow.h>

/*
 * basic client window class that sends all actions bck to its parent
 */
class DLL_EXP EZClientWindow : public EZWindow  
{
public:
	EZClientWindow();
	bool create(EZWindow *parent);
	virtual ~EZClientWindow();
protected:
    virtual void onPreCreate(CREATESTRUCT *cs);

    virtual void onNotify(EZEvent *ev);
    virtual void onMenuSelect(EZEvent *ev);
    virtual void onControlAction(EZEvent *ev);
	virtual void onMouseUp(EZEvent *ev, int button);
	virtual void onMouseDown(EZEvent *ev, int button);

};

#endif ezclientwindow_h
