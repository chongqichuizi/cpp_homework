
/***********************************************************
 * EZWIN2
 *
 * Name:      ezcursor.h
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

#ifndef ezcursor_h
#define ezcursor_h

#include <ezwin.h>

/* 
 standard types we can create

 IDC_APPSTARTING Standard arrow and small hourglass 
 IDC_ARROW Standard arrow 
 IDC_CROSS Crosshair 
 IDC_HAND Windows NT 5.0 and later: Hand
 IDC_HELP Arrow and question mark
 IDC_IBEAM I-beam 
 IDC_ICON Obsolete for applications marked version 4.0 or later.
 IDC_NO Slashed circle 
 IDC_SIZE Obsolete for applications marked version 4.0 or later. Use IDC_SIZEALL. 
 IDC_SIZEALL Four-pointed arrow pointing north, south, east, and west
 IDC_SIZENESW Double-pointed arrow pointing northeast and southwest 
 IDC_SIZENS Double-pointed arrow pointing north and south
 IDC_SIZENWSE Double-pointed arrow pointing northwest and southeast 
 IDC_SIZEWE Double-pointed arrow pointing west and east 
 IDC_UPARROW Vertical arrow 
 IDC_WAIT Hourglass
*/

class DLL_EXP EZCursor
{
public:
  static EZCursor getSystemCursor(LPCTSTR lpCursorName);

  HCURSOR getHandle() const;

  EZCursor();
  EZCursor(DWORD res);
  EZCursor(LPCTSTR lpCursorName);
  EZCursor(const EZCursor &curs);
  EZCursor(HCURSOR h);

  EZCursor & operator=(const EZCursor &curs);

  virtual ~EZCursor();

private:
	HCURSOR _handle;
};

#endif // ezcursor_h