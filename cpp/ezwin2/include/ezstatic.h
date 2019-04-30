
/***********************************************************
 * EZWIN2
 *
 * Name:      ezstatic.h
 * version:   0.1
 * date:      128 April 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezstatic_h
#define ezstatic_h

#include <ezwindow.h>

class DLL_EXP EZStatic : public EZWindow
{
public:
  EZStatic();
  
  bool create(EZWindow *parent,const char *text, const EZRect &rect = EZRect(), int id=-1);

  virtual ~EZStatic();
protected:
  virtual void onPreCreate(CREATESTRUCT *cs);
};


#endif // ezstatic_h