

/***********************************************************
 * EZWIN2
 *
 * Name:      ezwindow.h
 * version:   0.1
 * date:      20 April 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezwindow_h
#define ezwindow_h

#include <ezwin.h>

#include <string>
#include <ezsize.h>
#include <ezfont.h>
#include <ezcursor.h>	
#include <ezbitmap.h>

#if defined(_MSC_VER)
  #pragma warning(push)
  #pragma warning(disable: 4251)
  #pragma warning(disable: 4786)
#endif

class EZEvent;
class EZLayout;
class EZApplication;

// private message used to do then call create
// AFTER the window has been added to the window list etc
#define WM_POSTCREATE 0x7fff

class DLL_EXP EZWindow
{
protected: // TODO FIX ME
  bool _processdefault; // used by event handler

  bool _created;

  bool _closing;

  EZWindow * _parent;

  HWND _window;

  EZLayout *_layout;

public:
  // constructors ----------------------------
  EZWindow();
  virtual ~EZWindow();

  // window creation -------------------------
  virtual bool create(EZWindow *parent, const char *name,ULONG flags=0,const EZRect &rect = EZRect(),int id=0);
  /**
   * kill the window
   */
  virtual bool destroy();

  // window relationships --------------------

  EZApplication * getApp() const;

  HWND getHandle();

  int getID();

  void setUserData(void *);
  void * getUserData();

  /**
   * get the windows parent
   */
  inline EZWindow * getParent() { return _parent; }
  bool setParent(EZWindow *win);

  EZWindow * getFrame();

  EZWindow * getFirstChild();
  EZWindow * getNextChild(EZWindow *win);

  // window text management ------------------ 
  void setText(const char *text);
  std::string getText();

  // mouse management ------------------------
  EZPoint getMousePos(); 
  EZPoint translatePoint(EZWindow *fromwin, const EZPoint &pt);

  void captureMouse(bool yes);

  // message sending -------------------------
  LRESULT sendMessage(UINT message, WPARAM wparam, LPARAM lparam);
  LRESULT postMessage(UINT message, WPARAM wparam, LPARAM lparam);

  // layout management -----------------------
  bool setLayout(EZLayout *layout);
  EZLayout *getLayout() const { return _layout; }
  virtual void rethinkLayout();

  // window size ------------------------------

  /**
   * get window pos
   */
  int getX() const;
  int getY() const;
  unsigned int getWidth() const;
  unsigned int getHeight() const;

  inline int getTop() const { return getY(); }
  inline int getBottom() const { return getY() + getHeight(); }
  inline int getLeft() const { return getX(); }
  int getRight() const { return getX() + getWidth(); }

  EZSize getSize() const;

  EZRect getRect() const;

  virtual EZRect getClientRect() const;

  /**
   * setting window sizes
   */
  void setSize(unsigned int w,unsigned h);
  void setPos(int x,int y);

  void setRect(EZRect &r);


  // general window manipulation --------------

  /**
   * show/hide window
   */
  virtual bool show();
  virtual bool hide();

  bool minimize();
  bool maximize();
  bool focus();

  bool isVisible();
  bool hasFocus();
  bool isMinimized();
  bool isMaximized();

  /**
   * send close
   */
  bool close();

  // window drawing ---------------------------
  bool clear(int x=0,int y=0, int w=-1,int h=-1);
  bool repaint(int x=0,int y=0, int w=-1,int h=-1,bool cl=false);
  bool repaint(const EZRect &r,bool cl=false);

  EZCursor setCursor(const EZCursor &c);

  EZFont getFont();
  void setFont(const EZFont &font);

  void setStyle(DWORD stle);
  DWORD getStyle();

  // caret functions
  bool hideCaret();
  bool showCaret();
  EZPoint getCaretPos();
  bool setCaretPos(const EZPoint &pt);
  UINT getCaretBlinkTime();
  bool setCaretBlinkTime(UINT tm);
  bool createCaret(EZBitmap &bm);
  bool createCaret(int width, int height);
  bool destroyCaret();

protected:
  const char * createEZWindowClass(const char *name = 0);

public:  // message functions

  virtual void onKeyDown(EZEvent *ev);
  virtual void onKeyUp(EZEvent *ev);

  // tell the event handler we want to do default processing on this
  void processDefault() { _processdefault = true; }

  // message functions
  virtual void onHelp(EZEvent *ev);

  virtual void onPreCreate(CREATESTRUCT *cs);
  virtual void onCreate(EZEvent *ev);

  // called from parents onNotify
  virtual void onChildNotify(EZEvent *ev);
  virtual void onNotify(EZEvent *ev);

  virtual void onClose(EZEvent *ev);
  virtual void onDestroy(EZEvent *ev);
  virtual void onSize(EZEvent *ev);

  virtual void onPaint(EZEvent *ev);

  virtual void onMouseUp(EZEvent *ev,int button);
  virtual void onMouseDown(EZEvent *ev,int button);
  virtual void onDoubleClick(EZEvent *ev, int button);
  virtual void onMouseMove(EZEvent *ev);

  virtual void onTimer(EZEvent *ev);

  virtual void onSetCursor(EZEvent *ev);

  virtual void onMenuSelect(EZEvent *ev);

  virtual void onControlAction(EZEvent *ev);
  virtual void onChildControlAction(EZEvent *ev);

  virtual void onUser(EZEvent *ev);

  virtual void onChar(EZEvent *ev);

  virtual void onSetFocus(EZEvent *ev);
  virtual void onKillFocus(EZEvent *ev);

  virtual void onSetText(EZEvent *ev);

  virtual void onScroll(EZEvent *ev, int type);

protected:

  virtual LRESULT processDefaultMessage(UINT uMessage,EZEvent *e);

  virtual bool processMessage(UINT uMessage,EZEvent *e);

private:
  EZCursor _cursor;
  EZFont _font;

  // dont allow copy and =
  EZWindow &operator=(const EZWindow &) { return *this; }
  EZWindow(const EZWindow &) {}

  // the window proc
  static LRESULT CALLBACK WndProc(HWND hWindow,UINT uMessage,
			WPARAM wParam,LPARAM lParam);

  // special constructor
  //EZWindow(HWND handle);
};

#if defined(_MSC_VER)
  #pragma warning(pop)
#endif

#endif // ezwindow_h
