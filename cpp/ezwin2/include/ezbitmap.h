
/***********************************************************
 * EZWIN2
 *
 * Name:      ezbitmap.h
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

#ifndef ezbitmap_h
#define ezbitmap_h

#include <ezwin.h>
#include <ezgdiresource.h>

class DLL_EXP EZBitmap : private EZGDIResource
{
 HBITMAP _handle;
 BITMAP bmapinfo;
public:
  EZBitmap(const EZBitmap &b);
  EZBitmap & operator=(const EZBitmap &b);

  EZBitmap(HBITMAP bm);
  EZBitmap(DWORD bmresource);
  EZBitmap(const char *filename);

  virtual ~EZBitmap();

  HBITMAP getHandle() const { return _handle; }

  int getWidth();
  int getHeight();
};

#endif // ezbitmap_h
