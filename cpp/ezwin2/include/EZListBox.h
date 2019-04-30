
/***********************************************************
 * EZWIN2
 *
 * Name:      ezlistbox.h
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

#ifndef ezlistbox_h
#define ezlistbox_h

#include <ezwindow.h>

class DLL_EXP EZListBox : public EZWindow  
{
public:
	EZListBox();
	
	bool create(EZWindow *parent,char *name,const EZRect &rect = EZRect(),int id=-1);

	virtual ~EZListBox();

	void addItem(const char *str);

//	void delItem(int index);
//  loadDir();
//	int findItem(const char *str);
//	int getSelectedIndex();

    int getCount();
//	std::string getText(int index);

protected:
	virtual void onPreCreate(CREATESTRUCT *cs);
};

#endif // ezlistbox_h
