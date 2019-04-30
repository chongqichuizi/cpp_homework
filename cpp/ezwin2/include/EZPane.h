
/***********************************************************
 * EZWIN2
 *
 * Name:      ezpane.h
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

#ifndef ezpane_h
#define ezpane_h

#include <ezwindow.h>

/*
 * basic class that does basically nothing
 */
class DLL_EXP EZPane : public EZWindow  
{
public:
	EZPane();
	
	virtual bool create(EZWindow *parent, const EZRect &rect = EZRect());
	virtual ~EZPane();
protected:
    virtual void onPreCreate(CREATESTRUCT *cs);

};

#endif // ezpane_h
