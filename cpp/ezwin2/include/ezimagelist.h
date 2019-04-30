
/***********************************************************
 * EZWIN2
 *
 * Name:      ezimagelist.h
 * version:   0.1
 * date:      28 APril 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezimagelist_h
#define ezimagelist_h

#include <ezwin.h>
#include <commctrl.h>
#include <ezicon.h>

class DLL_EXP EZImageList
{
  HIMAGELIST _handle;
public:
  inline HIMAGELIST getHandle() const { return _handle; }

  int addImage(const EZIcon &icon);

  EZImageList(int imagesize=32);
  virtual ~EZImageList();    

  EZImageList(const EZImageList &);
  EZImageList &operator=(const EZImageList &);
};

#endif //ezimagelist_h