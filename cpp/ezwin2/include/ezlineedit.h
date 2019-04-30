
/***********************************************************
 * EZWIN2
 *
 * Name:      ezlineedit.h
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

#ifndef ezlineedit_h
#define ezlineedit_h

#include <ezwindow.h>

class DLL_EXP EZLineEdit
 : public EZWindow
{
public:

  EZLineEdit();
  
  bool create(EZWindow *parent,const char *text,const EZRect &rect=EZRect(),int id=-1);

  virtual ~EZLineEdit();
  
  virtual void setMaxLength(UINT m);

protected:
  virtual void onPreCreate(CREATESTRUCT *cs);
};


#endif // ezlineedit_h