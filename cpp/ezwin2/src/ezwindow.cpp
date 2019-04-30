
#include <ezwindow.h>
#include <ezapp.h>
#include <ezevent.h>
#include <ezlayout.h>
#include <ezgfx.h>
#include <ezsize.h>

EZWindow::EZWindow()
{
  _parent = 0;
  _closing = false;

  _layout = 0;

  _created = false;

  _window = 0;
}
EZApplication * EZWindow::getApp() const
{
  return EZApp;
}

bool EZWindow::create(EZWindow *parent, const char *name,ULONG flags,const EZRect &rect,int id)
{

   assert(_window == 0);

   _parent = parent;

   if(_parent) flags |= WS_CHILD;

   CREATESTRUCT cs;

   if(rect.isValid())
   {
     cs.cx  = rect.getWidth();
     cs.cy  = rect.getHeight();
     cs.x   = rect.getX();
     cs.y   = rect.getY();
   }
   else
   {
     cs.cx  = CW_USEDEFAULT;
     cs.cy  = CW_USEDEFAULT;
     cs.x   = CW_USEDEFAULT;
     cs.y   = CW_USEDEFAULT;
   }
   cs.dwExStyle = 0;
   cs.hInstance = EZApp->getInstance();

   cs.hMenu = (HMENU)id;
   cs.hwndParent = _parent!=0 ? _parent->_window : NULL;
   cs.lpCreateParams = 0;
   cs.lpszClass = NULL; 
   cs.lpszName = name;
   cs.style = flags;

   // get additional options here
   // such as class name etc
   onPreCreate(&cs);

   // still no class name?
   if(cs.lpszClass == 0)
   {
      cs.lpszClass = createEZWindowClass();
	  //cs.lpszClass = "EDIT";
   }

   assert(cs.lpszClass != 0);
   
   _window = CreateWindowEx(
		  cs.dwExStyle,cs.lpszClass,cs.lpszName,
		  cs.style,
		  cs.x, cs.y, cs.cx, cs.cy,
		  _parent!=0 ? _parent->_window : NULL,
          cs.hMenu,
		  cs.hInstance, cs.lpCreateParams);

   assert(_window != 0);

  // add to window list
  EZApp->addWindow(this);

  _created = true;

  // send message on for create notify ( will be used to process onCreate )
  if(_window) postMessage(WM_POSTCREATE, 0,0);

  return true;
}
//----------------------------------------------------------------------



EZPoint EZWindow::getMousePos()
{
   POINT p;

   GetCursorPos(&p);
   
   return p;
}

EZPoint EZWindow::translatePoint(EZWindow *fromwin, const EZPoint &pt)
{
  POINT points = pt.toPOINT();

  MapWindowPoints((fromwin ? fromwin->getHandle() : 0) , getHandle(), (LPPOINT)&points, 1);

  return points;
}
//----------------------------------------------

EZWindow::~EZWindow()
{
  destroy();
}

HWND EZWindow::getHandle() { return _window; }

EZWindow * EZWindow::getFrame()
{
  assert(_window != 0);

  EZWindow *w = this;

  while(w->_parent) w = w->_parent;

  return w;
}

int EZWindow::getID()
{
  assert(_window != 0);

  return GetWindowLong(_window,GWL_ID);
}

/**
 * show/hide window
 */
bool EZWindow::show()
{
  assert(_window != 0);

  ShowWindow(_window, SW_SHOWNORMAL);
  UpdateWindow(_window);
  
  rethinkLayout();
  return true;
}
bool EZWindow::hide()
{
  assert(_window != 0);

  return ShowWindow(_window, SW_HIDE) == TRUE;
}

bool EZWindow::minimize()
{
  assert(_window != 0);

  // NOTE: if we were using window CE, would have to use SW_SHOWMINIMIZED etc
  return ShowWindow(_window, SW_MINIMIZE) == TRUE;
}
bool EZWindow::maximize()
{
  assert(_window != 0);

  return ShowWindow(_window, SW_MAXIMIZE) == TRUE;
}
bool EZWindow::focus()
{
  assert(_window != 0);

  SetFocus(_window);
  return true;
}
bool EZWindow::isVisible()
{
  assert(_window != 0);

  return IsWindowVisible(_window) == TRUE;
}
bool EZWindow::hasFocus()
{
  assert(_window != 0);

   return GetFocus() == _window;
}
bool EZWindow::isMinimized()
{
  assert(_window != 0);

  return IsIconic(_window) == TRUE;
}
bool EZWindow::isMaximized()
{
  assert(_window != 0);

  return IsZoomed(_window) == TRUE;
}

bool EZWindow::clear(int x,int y, int w,int h)
{
  assert(_window != 0);

  RECT r;
  r.left = x;
  r.top = y;
  r.bottom = y + h;
  r.right = x + w;

  return InvalidateRect(_window,&r,TRUE) == TRUE;
}
bool EZWindow::repaint(int x,int y, int w,int h,bool cl)
{
  assert(_window != 0);

  RECT r;

  r.left = x;
  r.top = y;
  r.bottom = y + h;
  r.right = x + w;

  InvalidateRect(_window,&r,cl);

  return true;
}
bool EZWindow::repaint(const EZRect &r,bool cl)
{
  return repaint(r.getLeft(), r.getTop(), r.getWidth(), r.getHeight(), cl);
}

/**
 * send close
 */
bool EZWindow::close()
{
  assert(_window != 0);

  _closing = true;
  if(_created) SendMessage(_window,WM_CLOSE,0,0);
  return true;
}
/**
 * kill the window
 */
bool EZWindow::destroy()
{
  // if(_created)
  return true;
}

/**
 * get window pos
 */
int EZWindow::getX() const
{
  return getRect().getX();
}
int EZWindow::getY() const
{
  return getRect().getY();
}
unsigned int EZWindow::getWidth() const
{
  return getRect().getWidth();
}
unsigned int EZWindow::getHeight() const
{
  return getRect().getHeight();
}

EZRect EZWindow::getRect() const
{
   assert(_window != 0);

   RECT r;
   POINT pts={0,0};

   // relative to screen
   GetWindowRect(_window,&r);

   EZRect rect = r;

   // convert to relative to parent
   if(_parent != 0)
   {
	  POINT pts;
	  pts.x = r.left;
	  pts.y = r.top;

	  ScreenToClient(_parent->getHandle(), &pts);

	  rect.moveTo(pts.x,pts.y);
   }

   return rect;
}

EZRect EZWindow::getClientRect() const
{
  assert(_window != 0);

   RECT r;

   GetClientRect(_window,&r);

   return EZRect(r);
}

EZSize EZWindow::getSize() const
{
  return getRect().getSize();
}

/**
 * setting window sizes
 */
void EZWindow::setSize(unsigned int w,unsigned h)
{
  assert(_window != 0);

  EZRect r = getRect();

  MoveWindow(_window, r.getX(), r.getY(), w, h ,FALSE);
}
void EZWindow::setPos(int x,int y)
{
  assert(_window != 0);

  EZRect r = getRect();
  MoveWindow(_window, x,y, r.getWidth(), r.getHeight(),FALSE);
}

LRESULT EZWindow::processDefaultMessage(UINT uMessage,EZEvent *msg)
{
  return (DefWindowProc( getHandle(),uMessage, msg->getWParam(), msg->getLParam()));
}
bool EZWindow::processMessage(UINT uMessage,EZEvent *msg)
{
	switch (uMessage)
	{
      case WM_COMMAND:
      {
        int wNotifyCode = HIWORD(msg->getWParam()); // notification code
        int wID = LOWORD(msg->getWParam());         // item, control, or accelerator identifier
        HWND hwndCtl = (HWND) msg->getLParam();     // handle of control

        if(wNotifyCode==0 && hwndCtl==0)   // is a menu selection
        {
          EZEvent msg1(wID,(LPARAM)hwndCtl); // change so that wParam is only the id
          onMenuSelect(&msg1);
        }
        else if(wNotifyCode==1)   // is a accelerator selection
        {
           processDefault();
        }
        else // from a control
        {
          onControlAction(msg);
        }
        return true;
      }
	  case WM_HSCROLL:
		  onScroll(msg,SBS_HORZ);
		  return true;
	  case WM_VSCROLL:
		  onScroll(msg,SBS_VERT);
		  return true;
	  case WM_HELP:
		  onHelp(msg);
		  return true;
	  case WM_SETFOCUS:
		  onSetFocus(msg);
		  return true;
	  case WM_KILLFOCUS:
		  onKillFocus(msg);
		  return true;
      case WM_SETTEXT:
		  onSetText(msg);
		  return true;
	  case WM_NOTIFY:
		  onNotify(msg);
		  return true;
	  case WM_POSTCREATE:
		  onCreate(msg);
		  rethinkLayout(); // force the draw for the added items we may have
		  return true;
	  case WM_CREATE:
        // TODO this wont get called coz we dont have the window handle yet
        return true;
	  case WM_CHAR:
		onChar(msg);
		return true;
	  case WM_KEYDOWN:
		  onKeyDown(msg);
		  return true;
	  case WM_KEYUP:
		  onKeyUp(msg);
		  return true;
      case WM_SIZE:
        onSize(msg);
        return true;
	  case WM_PAINT:
         onPaint(msg);
         return true;
      case WM_MOUSEMOVE:
         onMouseMove(msg);
         return true;
      case WM_LBUTTONDOWN:
         onMouseDown(msg,0);
         return true;
      case WM_LBUTTONUP:
         onMouseUp(msg,0);
         return true;
	  case WM_LBUTTONDBLCLK:
		  onDoubleClick(msg,0);
		  break;
      case WM_MBUTTONDOWN:
         onMouseDown(msg,1);
         return true;
      case WM_MBUTTONUP:
         onMouseUp(msg,1);
         return true;
	  case WM_MBUTTONDBLCLK:
		  onDoubleClick(msg,1);
		  break;
      case WM_RBUTTONDOWN:
         onMouseDown(msg,2);
         return true;
      case WM_RBUTTONUP:
         onMouseUp(msg,2);
         return true;
	  case WM_RBUTTONDBLCLK:
		  onDoubleClick(msg,2);
		  break;
      case WM_TIMER:
         onTimer(msg);
         return true;

      case WM_SETCURSOR:
		 if(getHandle() == (HWND)msg->getWParam())
		 {
           onSetCursor(msg);
           return true;
		 }
		 else
		   return false;

      case WM_USER:
         onUser(msg);
         return true;

		case WM_CLOSE:
         onClose(msg);
         return true;

		case WM_DESTROY:
         onDestroy(msg);
         return true;
   }
   return false;
}

LRESULT CALLBACK EZWindow::WndProc(HWND hWindow,UINT uMessage,
			WPARAM wParam,LPARAM lParam)
{

   EZWindow * ezwindow = EZApp->findWindow(hWindow); //(EZWindow *)GetWindowLong(hWindow,0);
   if(!ezwindow) 
   {
     HWND w = GetWindow(hWindow, GW_CHILD);
     char buffer [256];
   
	 if(w != 0 && GetClassName(w, buffer, 255)!=0 && stricmp("MDICLIENT",buffer)==0)
	   DefFrameProc(hWindow, w, uMessage, wParam, lParam);
     else
	   return (DefWindowProc(hWindow,uMessage, wParam, lParam));

   }

   EZEvent msg(wParam,lParam);

   ezwindow->_processdefault = false;

   if(ezwindow->processMessage(uMessage,&msg)==false || ezwindow->_processdefault == true)
	  return ezwindow->processDefaultMessage(uMessage,&msg);

   return 0;
}

void EZWindow::onPreCreate(CREATESTRUCT *cs)
{
//  processDefault();
}

void EZWindow::onCreate(EZEvent *ev)
{
  if(_layout) _layout->doLayout();
  processDefault();
}
void EZWindow::onClose(EZEvent *ev)
{
  DestroyWindow(_window);
  processDefault();
}
void EZWindow::onDestroy(EZEvent *ev)
{
  processDefault();
}
void EZWindow::onPaint(EZEvent *ev)
{
  EZGfx painter(this);
  processDefault();
}
void EZWindow::onSetFocus(EZEvent *ev)
{
  processDefault();
}
void EZWindow::onKillFocus(EZEvent *ev)
{
  processDefault();
}
void EZWindow::onHelp(EZEvent *ev)
{
  processDefault();
}

void EZWindow::onMouseUp(EZEvent *ev,int button)
{
  processDefault();
}
void EZWindow::onMouseDown(EZEvent *ev,int button)
{
  processDefault();
}

void EZWindow::onMouseMove(EZEvent *ev)
{
  processDefault();
}
void EZWindow::onTimer(EZEvent *ev)
{
  processDefault();
}

void EZWindow::onSetCursor(EZEvent *ev)
{
  EZPoint pt = translatePoint(0, getMousePos());

  EZRect rect = getClientRect();

  if(rect.contains(pt.getX(), pt.getY())==false)
  {
	processDefault();
	return;
  }

  SetCursor(_cursor.getHandle());

  // DO NOT call processDefault();
  //DefWindowProc(_window,WM_SETCURSOR, ev->getWParam(), ev->getLParam());
  _processdefault = false;
}

void EZWindow::onUser(EZEvent *ev)
{
  processDefault();
}

void EZWindow::onSize(EZEvent *ev)
{

  if(_layout) 
  {
		_layout->doLayout();
		//_processdefault = false;
  }
  else
	  processDefault();
}

void EZWindow::onChar(EZEvent *ev)
{
  processDefault();
}

void EZWindow::onMenuSelect(EZEvent *ev)
{
  processDefault();

  return;
}

void EZWindow::onDoubleClick(EZEvent *ev, int button)
{
  processDefault();
}

void EZWindow::onControlAction(EZEvent *ev)
{
	// pass to the control who caused us - later may want to see what the notification
	// was for and send to more appropriate functions
	//
	HWND cntrl = (HWND) ev->getLParam();

	EZWindow * w = EZApp->findWindow( cntrl );

	if(w)
	{
		w->onChildControlAction(ev);
	}

  processDefault();
  return;
}
void EZWindow::onScroll(EZEvent *ev, int type)
{
  processDefault();
}
/*
#define NM_CLICK                (NM_FIRST-2)    // uses NMCLICK struct
#define NM_DBLCLK               (NM_FIRST-3)
#define NM_RETURN               (NM_FIRST-4)
#define NM_RCLICK               (NM_FIRST-5)    // uses NMCLICK struct
#define NM_RDBLCLK              (NM_FIRST-6)
#define NM_SETFOCUS             (NM_FIRST-7)
#define NM_KILLFOCUS            (NM_FIRST-8)
#if (_WIN32_IE >= 0x0300)
#define NM_CUSTOMDRAW           (NM_FIRST-12)
#define NM_HOVER                (NM_FIRST-13)
#endif
#if (_WIN32_IE >= 0x0400)
#define NM_NCHITTEST            (NM_FIRST-14)   // uses NMMOUSE struct
#define NM_KEYDOWN              (NM_FIRST-15)   // uses NMKEY struct
#define NM_RELEASEDCAPTURE      (NM_FIRST-16)
#define NM_SETCURSOR            (NM_FIRST-17)   // uses NMMOUSE struct
#define NM_CHAR                 (NM_FIRST-18)   // uses NMCHAR struct
*/
void EZWindow:: onNotify(EZEvent *ev)
{
    LPNMHDR pnmh = (LPNMHDR) ev->getLParam();
	
	EZWindow * w = EZApp->findWindow( pnmh->hwndFrom );
	int code = pnmh->code;

	if(w)
	{
		w->onChildNotify(ev);
	}
  processDefault();
}
void EZWindow:: onChildNotify(EZEvent *ev)
{

}

void EZWindow::setRect(EZRect &r)
{
  assert(_window != 0);

  MoveWindow(_window, r.getX(), r.getY(), r.getWidth(), r.getHeight(), TRUE); // WAS FALSE
}


EZWindow * EZWindow::getFirstChild()
{
  assert(_window != 0);

  HWND w = GetWindow(_window, GW_CHILD);
  return EZApp->findWindow(w);
}

EZWindow * EZWindow::getNextChild(EZWindow *win)
{
  assert(_window != 0);

  if(!win || win->_window == 0) return 0;

  HWND w = GetWindow(win->_window, GW_HWNDNEXT);
  return EZApp->findWindow(w);
}

bool EZWindow::setLayout(EZLayout *layout)
{
  _layout = layout;

  return layout != 0;
}

void EZWindow::rethinkLayout()
{
  assert(_window != 0);

  if(_layout) _layout->doLayout();

  EZWindow *w = getFirstChild();

  //paint();
  repaint(getClientRect());
  
  while(w)
  {
     w->rethinkLayout();
     w = getNextChild(w);
  }
}

void EZWindow::captureMouse(bool yes)
{
  assert(_window != 0);

  if(yes)
    SetCapture(_window);
  else
    ReleaseCapture();

  return;
}

void EZWindow::setText(const char *text)
{
  assert(_window != 0);

   SendMessage(_window,WM_SETTEXT,0,(LPARAM)text);
}


LRESULT EZWindow::sendMessage(UINT message, WPARAM wparam, LPARAM lparam)
{
  assert(_window != 0);

  return SendMessage(_window,message,wparam,lparam);
}
LRESULT EZWindow::postMessage(UINT message, WPARAM wparam, LPARAM lparam)
{
  assert(_window != 0);

  return PostMessage(_window,message,wparam,lparam);
}

void * EZWindow::getUserData()
{
  assert(_window != 0);

  return (void *)GetWindowLong(_window,GWL_USERDATA);
}


void EZWindow::setUserData(void *d)
{
  assert(_window != 0);

  SetWindowLong(_window,GWL_USERDATA,(LONG)d);
}

void EZWindow::onChildControlAction(EZEvent *ev)
{

}
std::string EZWindow::getText()
{
  assert(_window != 0);

   char buffer[256];
   //SendMessage(_window,WM_GETTEXT, 255, (LPARAM)buffer);
   if(GetWindowText(getHandle(),buffer,255)==0)
   {
	   buffer[0] = '\0';
   }

   return std::string(buffer);
}

void EZWindow::onSetText(EZEvent *ev)
{
 processDefault(); // just do as normal processing for this window
}

DWORD EZWindow::getStyle()
{
  assert(_window != 0);

  return GetWindowLong(getHandle(), GWL_STYLE);
}

void EZWindow::setStyle(DWORD style)
{
  assert(_window != 0);

   SetWindowLong(getHandle(),GWL_STYLE,style);
}



void EZWindow::setFont(const EZFont &font)
{
  assert(_window != 0);

  // save font so that doesnt go out of scope
  _font = font;

  sendMessage(WM_SETFONT,(WPARAM)font.getHandle(), 1);
}

EZFont EZWindow::getFont()
{
  HFONT h = (HFONT)sendMessage(WM_GETFONT,0,0);

  if(h==0) return EZFont(); 

  return EZFont(h);
}

// TODO - handle setting to top level
bool EZWindow::setParent(EZWindow *win)
{
  if(!win) return false;

  assert(_window != 0);

  if(SetParent(getHandle(), win->getHandle())==0) return false;

  DWORD flags = getStyle();

  if((flags & WS_CHILD) == 0)
  {
	  flags |= WS_CHILD;
      setStyle(flags);
  }

  _parent = win;

  return true;
}

EZCursor EZWindow::setCursor(const EZCursor &c)
{
  EZCursor old = _cursor;
  _cursor = c;
  SetCursor(_cursor.getHandle());
  return old;
}

const char * EZWindow::createEZWindowClass(const char *name)
{
	static char *class_name = "EZWinClass"; //[256];

    if(name == 0)
		name = class_name;

	ATOM Result;
	WNDCLASS wc;


	// do we already have?
	if(GetClassInfo(EZApp->getInstance(),name,&wc))
	{
		return name;
	}

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 4;
	wc.hInstance = EZApp->getInstance();
    wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // we have to do the cursor //LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
	wc.lpszMenuName =  0;
	wc.lpszClassName = name;

	Result = RegisterClass(&wc);
	if(Result) return name;

	return 0;
}

void EZWindow::onKeyUp(EZEvent *ev)
{
  processDefault();
}

void EZWindow::onKeyDown(EZEvent *ev)
{
  processDefault();
}

bool EZWindow::showCaret()
{
  assert(_window != 0);

  return ShowCaret(_window) == TRUE;
}

bool EZWindow::hideCaret()
{
  assert(_window != 0);

  return HideCaret(_window) == TRUE;
}

EZPoint EZWindow::getCaretPos()
{
   POINT p;

   GetCaretPos(&p);

   return p;
}

bool EZWindow::setCaretPos(const EZPoint &pt)
{
	return  SetCaretPos(pt.getX(), pt.getY()) == TRUE;
}

UINT EZWindow::getCaretBlinkTime()
{
  return GetCaretBlinkTime();
}

bool EZWindow::setCaretBlinkTime(UINT t)
{
  return SetCaretBlinkTime(t) == TRUE;
}

bool EZWindow::createCaret(EZBitmap &bm)
{
  return CreateCaret(_window,bm.getHandle(), 0,0) == TRUE;
}

bool EZWindow::createCaret(int width, int height)
{
  return CreateCaret(_window,0, width, height) == TRUE;
}

bool EZWindow::destroyCaret()
{
	return DestroyCaret() == TRUE;
}

