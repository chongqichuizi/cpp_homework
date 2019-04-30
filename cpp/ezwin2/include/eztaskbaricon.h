

/***********************************************************
 * EZWIN2
 *
 * Name:      eztaskbaricon.h
 * version:   0.1
 * date:      20 April 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef eztaskbaricon_h
#define eztaskbaricon_h

#include <ezwin.h>

#include <ezicon.h>
#include <shellapi.h>

class DLL_EXP EZTaskbarIcon
 : public EZIcon
{
  NOTIFYICONDATA nd;
  static int uid_counter; //REM now a global in the body code 
public:
  EZTaskbarIcon(EZWindow *parent,DWORD iconresource,LPSTR tip,UINT messageID=0);
  virtual ~EZTaskbarIcon();

};

#endif // eztaskbaricon_h
