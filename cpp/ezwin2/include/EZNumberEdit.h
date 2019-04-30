
/***********************************************************
 * EZWIN2
 *
 * Name:      eznumberedit.h
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
 ***********************************************************////

#ifndef eznumberedit_h
#define eznumberedit_h

#include <ezlineedit.h>

class DLL_EXP EZNumberEdit : public EZLineEdit 
{
public:
	float getFloatNumber();
	int getIntNumber();

	EZNumberEdit();
	
	virtual ~EZNumberEdit();

    // setMaxLength in LineEdit

protected:
	void onChildControlAction(EZEvent *ev);
	virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif // eznumberedit_h
