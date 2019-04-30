
/***********************************************************
 * EZWIN2
 *
 * Name:      ezlayout.h
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

#ifndef ezlayout_h

#define ezlayout_h

#if defined(_MSC_VER)
  #pragma warning(disable: 4251)
  #pragma warning(disable: 4786)
#endif

#include <ezwin.h>

#include <map>

class EZWindow;

/*
//TODO BorderLayout
// have map with idex of North,South,East,West,Center and second of EZWIndow pointer
class DLL_EXP EZBorderLayout : public EZLayout
{
public:
	typedef enum { North,South,East,West,Center } Position;

    EZBorderLayout(EZWindow *parent);
	~EZBorderLayout();

	void setPosition(EZWindow *w, Position pos);
protected:
	void doLayout();
};
*/

/*
 * base layout class
 */
class DLL_EXP EZLayout
{
  protected:
    EZWindow *_parent;
  public:
    EZLayout(EZWindow *parent);
    virtual ~EZLayout();
    virtual void doLayout()=0;
};


class DLL_EXP EZMainWindowLayout
: public EZLayout
{
  EZWindow *_toolbar;
  EZWindow *_mainw;
  EZWindow *_statusbar;
public:
  EZMainWindowLayout(EZWindow *parent);
  virtual ~EZMainWindowLayout();

  void setToolBar(EZWindow *toolbar);
  void setMainWindow(EZWindow *mainw);
  void setStatusBar(EZWindow *status);

protected:
  void doLayout();
};

/*
 * basic ColumnLayout class 
 * has limitation that windows will not
 * layput correctly if they have a fixed size given 
 * no room to put them.
 */
class DLL_EXP EZColumnLayout
: public EZLayout
{
  typedef std::map<int,int,std::less<int> > WidthData;

  WidthData _widths;
public:
  EZColumnLayout(EZWindow *parent);
  virtual ~EZColumnLayout();

  int setWidth(int col, int width);
protected:
  void doLayout();
};

// same as ColumnLayout
class DLL_EXP EZRowLayout
: public EZLayout
{
  typedef std::map<int,int,std::less<int> > HeightData;

  HeightData _heights;
public:
  EZRowLayout(EZWindow *parent);
  virtual ~EZRowLayout();

  int setHeight(int col, int height);
protected:
  void doLayout();
};

class DLL_EXP EZSingleClientLayout : public EZLayout
{
public:
  EZSingleClientLayout(EZWindow *parent);
  virtual ~EZSingleClientLayout();
protected:
  void doLayout();
};

#endif // ezlayout_h