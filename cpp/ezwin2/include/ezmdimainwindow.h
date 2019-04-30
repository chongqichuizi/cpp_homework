/***********************************************************
 * EZWIN2
 *
 * Name:      ezmdimainwindow.h
 * version:   0.1
 * date:      15 June 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#if !defined(AFX_EZMDIMAINWINDOW_H__9175ABA2_8C06_4B8B_B231_CD49468B517C__INCLUDED_)
#define AFX_EZMDIMAINWINDOW_H__9175ABA2_8C06_4B8B_B231_CD49468B517C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ezmainwindow.h>
class EZMDIWindow;

class DLL_EXP EZMDIMainWindow : public EZMainWindow  
{
  EZMDIWindow *_mdi;
public:
	void MDIClose(EZWindow *w);
	EZMDIWindow * getMDIWindow();
	EZMDIMainWindow();
	virtual ~EZMDIMainWindow();

	void MDIActivate(EZWindow *w);
	EZWindow * MDIGetActive();
	void MDIPrev();
	void MDINext();
	void MDIMaximise(EZWindow *w);
	void MDIRestore(EZWindow *w);
	void MDITile(int flags);
	void MDICascade(int flags = 0);
protected:
	virtual void onSize(EZEvent *ev);
	virtual LRESULT processDefaultMessage(UINT uMessage,EZEvent *e);
	virtual void onMenuSelect(EZEvent *ev);
	virtual void onControlAction(EZEvent *ev);
	virtual void onCreate(EZEvent *ev);
};

#endif // !defined(AFX_EZMDIMAINWINDOW_H__9175ABA2_8C06_4B8B_B231_CD49468B517C__INCLUDED_)
