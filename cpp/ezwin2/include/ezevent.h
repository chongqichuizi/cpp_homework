
/***********************************************************
 * EZWIN2
 *
 * Name:      ezevent.h
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

#ifndef ezevent_h
#define ezevent_h

#include <ezwin.h>

#include <ezapp.h>

class DLL_EXP EZEvent
{
  WPARAM _wparam;
  LPARAM _lparam;
public:
  EZEvent(WPARAM w, LPARAM l)
  {
    _wparam = w;
    _lparam = l;
  }
  EZEvent(const EZEvent &ev)
  {
	 _wparam = ev._wparam;
	 _lparam = ev._lparam;
  }
  inline WPARAM getWParam() { return _wparam; }
  inline LPARAM getLParam() { return _lparam; }
};

// event parsers  for events
class DLL_EXP EZControlActionEvent : public EZEvent 
{
public:
  EZControlActionEvent(const EZEvent &ev)
	  : EZEvent(ev)
  {
  }
  virtual ~EZControlActionEvent() {}

  int getNotifyCode()
  {
     return HIWORD(getWParam());
  }
  int getID()
  {
     return LOWORD(getWParam());
  }
  HWND getHWND()
  {
     return (HWND)getLParam();
  }
};

class DLL_EXP EZMenuSelectEvent : public EZEvent 
{
public:
  EZMenuSelectEvent(const EZEvent &ev)
	  : EZEvent(ev)
  {
  }
  virtual ~EZMenuSelectEvent() {}

  int getID()
  {
     return LOWORD(getWParam());
  }
};

class DLL_EXP EZPaintEvent : public EZEvent
{
public:

  EZPaintEvent(const EZEvent &ev)
   : EZEvent(ev)
  {
  }
  virtual ~EZPaintEvent()
  {
  }
  HDC getHDC()
  {
     return (HDC) getWParam();
  }
};

class DLL_EXP EZMouseEvent : public EZEvent
{
public:

  EZMouseEvent(const EZEvent &ev)
   : EZEvent(ev)
  {
  } 
  virtual ~EZMouseEvent()
  {
  }
  int getKeys()
  {
     return (int) getWParam();
  }
  int getX()
  {
	  return LOWORD(getLParam()); 
  }
  int getY()
  {
	  return HIWORD(getLParam()); 
  }
};

#endif // ezevent
