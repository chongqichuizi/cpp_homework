
/***********************************************************
 * EZWIN2
 *
 * Name:      ezmenu.h
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

#ifndef ezmenu_h
#define ezmenu_h

#include <ezwin.h>
#include <assert.h>

#include <ezwindow.h>

class DLL_EXP EZMenu
{
protected:
  HMENU _menu;
  EZWindow *_parent;
public:

  EZMenu();
  
  virtual ~EZMenu();

  void addItem(const char *text,int id=-1);
  void addSeparator();

  virtual bool create(EZWindow *parent=0,const char *text=0);

  inline HMENU getHandle() { return _menu; }
};

class DLL_EXP EZPopupMenu
 : public EZMenu
{
public:
  EZPopupMenu() {}
  virtual ~EZPopupMenu() {}

  virtual bool show()
  {
    POINT p;

    GetCursorPos(&p);

    return show(p.x,p.y);
  }
  virtual bool show(int x,int y)
  {
	assert( _menu != 0 );

    return TrackPopupMenu((HMENU)_menu,
      TPM_RIGHTBUTTON|TPM_LEFTALIGN,	      // screen-position and mouse-button flags
      x,	// horizontal position, in screen coordinates
      y,	// vertical position, in screen coordinates
      0,	// reserved, must be zero
      _parent==0 ? 0 : _parent->getHandle(),  // handle of owner window
      NULL	// points to RECT that specifies no-dismissal area
    ) == TRUE;
  }

  virtual bool create(EZWindow *parent=0,const char *text=0)
  {
	assert( _menu == 0 );

	_parent = parent;

    _menu = CreatePopupMenu();
    return true;
  }
};

#endif // ezmenu_h
