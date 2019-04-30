#include <ezapp.h>
#include <ezwindow.h>
#include <ezevent.h>

#include <commctrl.h>

#include <ezgdiresource.h> // for debug

// global application instance
EZApplication *EZApp=0;

/*
 * create application instance
 */
EZApplication::EZApplication(HINSTANCE inst,char * appname)
{
  // can aonly be one application instance
  assert( EZApp == 0);

  // set up data members

  _instance = inst;

  _appname = appname;

  // set the global
  EZApp = this;

  // setup commom controls
#if defined(__BORLANDC__)
  InitCommonControls();
#else // vc++
  INITCOMMONCONTROLSEX cex;
  cex.dwSize = sizeof(INITCOMMONCONTROLSEX);
  cex.dwICC = ICC_BAR_CLASSES | ICC_LISTVIEW_CLASSES | ICC_PROGRESS_CLASS |
	  ICC_TAB_CLASSES | ICC_TREEVIEW_CLASSES | ICC_USEREX_CLASSES  | ICC_WIN95_CLASSES;

  InitCommonControlsEx(&cex);
#endif  
}

EZApplication::~EZApplication()
{
}

//DEL void EZApplication::setMainWindow(EZWindow *w)
//DEL {
//DEL   _mainw = w;
//DEL }

HINSTANCE EZApplication::getInstance() { return _instance; }

void EZApplication::quit()
{
  PostQuitMessage(0);
}

int EZApplication::run()
{
	MSG msg;
	int ret;

	/* window control loop */
	while((ret = GetMessage(&msg,NULL,NULL,NULL)))
	{

		if(ret == -1)
		{
			MessageBox(NULL, "GetMessage errored.","EZWin", MB_OK|MB_ICONERROR);
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// check all GDI handles were freed
	EZGDIResource::dump();

	return msg.wParam;
}
const char * EZApplication::getName()
{
  return _appname.c_str();
}

// private window list manipulation functions --------------
void EZApplication::addWindow(EZWindow *w)
{
  // adds window to list
  if(w && w->getHandle()) _winlist.insert(EZWindowList::value_type(w->getHandle(),w));
  return;
}

EZWindow * EZApplication::findWindow(HWND win)
{
  EZWindowList::iterator p = _winlist.find(win);

  if (p != _winlist.end())
    return (*p).second;
  return 0;
}

EZWindow * EZApplication::tempWindow(HWND h)
{
	EZWindow *w = 0;

	// is it in the list of our created normal types already?
	w = EZApp->findWindow(h);

    // is it in temp windows we already have ?
	if(!w)
	{
      EZWindowList::iterator p = _templist.find(h);

      if (p != _winlist.end())
        w =  (*p).second;
	}
	// still dont have :( - going to have to see if can create a temporary one
	if(!w)
	{
		// have to see if can work out the type and create one of this type
		char buffer[256];
		if(GetClassName(h, buffer, 255)==0)
			return 0;

		// have class name - can we create the class ?
        if(stricmp("EDIT",buffer)==0)
		{
			// single or multiline
		}
		else if(stricmp("BUTTON",buffer)==0)
		{

		}
		else if(stricmp("COMBOBOX",buffer)==0)
		{

		}

	}
  return w;
}

void EZApplication::idleCleanup()
{
  // TODO - call on clean up temp mem
}
