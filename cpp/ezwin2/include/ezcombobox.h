
/***********************************************************
 * EZWIN2
 *
 * Name:      ezcombobox.h
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

#ifndef ezcombobox_h
#define ezcombobox_h

#include <ezwindow.h>

class DLL_EXP EZComboBox : public EZWindow
{
public:
  void setReadOnly(bool yes);
 
  void setCurrItem(int index);
  int getCurrItem();

  int findItem(const char *text);

  void remItem(int index);
  int addItem(const char *str);

  int getCount();

  bool create(EZWindow *parent,const char *name,const EZRect &rect = EZRect(),int id=-1);  

  EZComboBox();

  virtual ~EZComboBox();

protected:
	virtual void onPreCreate(CREATESTRUCT *cs);
};
#endif // ezcombobox_h