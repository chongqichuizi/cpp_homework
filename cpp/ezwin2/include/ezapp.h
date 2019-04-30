
/***********************************************************
 * EZWIN2
 *
 * Name:      ezapp.h
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

#ifndef ezapp_h
#define ezapp_h

#include <ezwin.h>

#if defined(_MSC_VER)
  #pragma warning(push)
  #pragma warning(disable: 4251)
  #pragma warning(disable: 4786)
#endif

#include <string>
#include <map>


class EZWindow;
class EZDialog;

typedef std::map<HWND,EZWindow *,std::less<HWND> > EZWindowList;

class DLL_EXP  EZApplication
{
  HINSTANCE _instance;
  std::string _appname;
  EZWindowList _winlist;
  EZWindowList _templist;

public:
  const char * getName();

  EZApplication(HINSTANCE inst,char * appname);
  virtual ~EZApplication();

  HINSTANCE getInstance();

  int run();
  void quit();

  EZWindow * findWindow(HWND win);

private:
  friend EZWindow;
  friend EZDialog; // to call add/find

  void addWindow(EZWindow *w);
  // bool delWindow(EZWindow *w);

  void idleCleanup();
  EZWindow * tempWindow(HWND h);


private:
  // no copy please
  EZApplication & operator==(const EZApplication &) { return *this; }
  EZApplication(const EZApplication &) {}
};

extern "C" DLL_EXP EZApplication *EZApp;

#if defined(_MSC_VER)
  #pragma warning(pop)
#endif

#endif // ezapp_h