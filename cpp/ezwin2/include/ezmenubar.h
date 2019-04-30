

/***********************************************************
 * EZWIN2
 *
 * Name:      ezmenubar.h
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

#ifndef ezmenubar_h
#define ezmenubar_h

#include <ezwin.h>

class EZWindow;
class EZMenu;

class DLL_EXP EZMenuBar
{
	HMENU _menubar;
	EZWindow *_parent;

public:
    EZMenuBar(); 
    virtual ~EZMenuBar();

	void loadMenuBar(DWORD res);
	virtual bool create(EZWindow *parent);
	virtual bool create(EZWindow *parent, DWORD res);

	inline HMENU getHandle() { return _menubar; }

	bool getMenuItemCheck(int id);
	void setMenuItemCheck(int id, bool checked);

	DWORD getMenuItemState(int id);
	void setMenuItemState(int id, DWORD state);

    void addMenu(char *text,EZMenu *menu);
 
    virtual void redraw();
};

#endif // ezmenubar_h