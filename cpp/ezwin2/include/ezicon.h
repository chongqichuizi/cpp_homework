

/***********************************************************
 * EZWIN2
 *
 * Name:      ezicon.h
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

#ifndef ezicon_h
#define ezicon_h

#include <ezwin.h>

#include <ezapp.h>

class DLL_EXP EZIcon
{
  HICON _icon;
public:
  EZIcon(DWORD iconresource);
  EZIcon(const char *filename);

  virtual ~EZIcon();

  inline HICON getHandle() const { return _icon; }

  EZIcon & operator=(const EZIcon &icon);
  EZIcon(const EZIcon &icon);
};

#endif // ezicon_h
