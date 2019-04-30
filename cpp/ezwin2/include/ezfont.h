
/***********************************************************
 * EZWIN2
 *
 * Name:      ezfont.h
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

#ifndef ezfont_h
#define ezfont_h

#include <ezwin.h>
#include <ezgdiresource.h>
#include <ezsize.h>

#define EZFONTSTYLE_ANY       0
#define EZFONTSTYLE_BOLD      1
#define EZFONTSTYLE_ITALIC    2
#define EZFONTSTYLE_UNDERLINE 4


class DLL_EXP EZFont : private EZGDIResource
{
  HFONT _handle;
public:

  EZFont();
  EZFont(const EZFont &f);
  EZFont &operator=(const EZFont &f);

  EZFont(const char *name, int w, int h, int pitch = FIXED_PITCH, int quality = DRAFT_QUALITY, int style=EZFONTSTYLE_ANY);
  virtual ~EZFont();

  EZFont(LOGFONT &logFont);
  EZFont(HFONT font);

  HFONT getHandle() const { return _handle; }

  int getHeight();
  int getWidth();
  EZSize getSize();

  bool getInfo(LOGFONT *info);
};

#endif // ezfont_h