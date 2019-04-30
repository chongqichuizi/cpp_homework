#include <ezdialog.h>
#include <ezapp.h>
#include <ezevent.h>

//#include <iostream>

#include "ezresource.h"

#if defined(__BORLANDC__)
  #include <mem.h> // for memset
#else
  #include <cstring>
#endif

#include <commctrl.h> // for tooltips

extern HINSTANCE dllInstance;

// InputType
#define PROMPTINPUT_FLOAT   2
#define PROMPTINPUT_INT     1
#define PROMPTINPUT_STRING  0

typedef BOOL CALLBACK PROMPTINPUT_HOOKPROC(HWND hWindow,UINT uMessage,WPARAM wParam,LPARAM lParam);
typedef PROMPTINPUT_HOOKPROC * LPPROMPTINPUT_HOOKPROC;
// CALLBACK
//typedef int (* NDB_Change_Callback)(NDB_ID id);

typedef struct tagPROMPTINPUT
{
	DWORD lStructSize;
	HINSTANCE hInstance;
	HWND      hwndOwner;
	LPCTSTR   lpstrTitle;
	LPCTSTR   lpstrPromptText;
	LPTSTR    lpstrInputText;
	UINT      nMaxInputText;
	DWORD     dwFlags;
	DWORD     dwInputType;
	LPCSTR    lpstrToolTipText;
	//
	//LPOFNHOOKPROC lpXXXX;
	LPCTSTR   lpTemplateName;
	LPARAM    lCustData;
	LPPROMPTINPUT_HOOKPROC lpHookProc;

} PROMPTINPUT, * LPPROMPTINPUT;


BOOL CALLBACK InputTextDlgWndProc(HWND hWindow,UINT uMessage,
			WPARAM wParam,LPARAM lParam)
{
   LPPROMPTINPUT promptdata;
   BOOL result;

   if(uMessage == WM_INITDIALOG)
   {
         //lParam should = a pointer to info we need

	     // save it for later	     
	     SetWindowLong(hWindow,DWL_USER,lParam);

         if(lParam!=0)
         {
		   promptdata = (LPPROMPTINPUT)lParam;

		   SetWindowLong(hWindow,DWL_USER,lParam);
           // dialog init processing
		   if(promptdata->lpstrTitle)
		   {
			   SendMessage(hWindow,WM_SETTEXT,0,(LPARAM)promptdata->lpstrTitle);
		   }
		   if(promptdata->lpstrPromptText)
			   SetDlgItemText(hWindow, IDC_PROMPTTEXT, promptdata->lpstrPromptText);

		   if(promptdata->lpstrInputText)
			   SetDlgItemText(hWindow, IDC_PROMPTEDIT, promptdata->lpstrInputText);

		   if(promptdata->nMaxInputText > 0 && GetDlgItem(hWindow,IDC_PROMPTEDIT))
		   {
			   // NOTE: if is num of chararcters ( if wide chars - bytes is 2x ) 
				SendMessage(GetDlgItem(hWindow,IDC_PROMPTEDIT),EM_SETLIMITTEXT, promptdata->nMaxInputText*sizeof(TCHAR), 0);
		   }

		   // the tooltip needed?
		   if(promptdata->lpstrToolTipText != 0 && GetDlgItem(hWindow,IDC_PROMPTEDIT)!=0)
		   {
				HWND tooltip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS,
					NULL,WS_POPUP|TTS_NOPREFIX|TTS_ALWAYSTIP,
					CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
					hWindow, NULL, dllInstance, NULL);

				if(tooltip)
				{
					SetWindowPos(tooltip, HWND_TOPMOST, 0,0,0,0,
						SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);

					TOOLINFO ti;
					ti.cbSize = sizeof(TOOLINFO);
					ti.uFlags = TTF_SUBCLASS|TTF_IDISHWND;
					ti.hinst = dllInstance;
					ti.uId = (UINT)GetDlgItem(hWindow,IDC_PROMPTEDIT);
					ti.lpszText = (char *)promptdata->lpstrToolTipText;
					ti.rect.left = ti.rect.right = ti.rect.top = ti.rect.bottom =0;
					SendMessage(tooltip, TTM_ADDTOOL, 0, (LPARAM)&ti);
				}
		   }
         }
		 // we are setting the focused control ourselves

         result = TRUE;

         if(promptdata->lpHookProc)
            result = promptdata->lpHookProc(hWindow,uMessage,wParam,lParam);

		 // still have yet to set a control
		 if(result == TRUE && GetDlgItem(hWindow,IDC_PROMPTEDIT))
		 {
		   SetFocus(GetDlgItem(hWindow,IDC_PROMPTEDIT));
		   // select all text
		   SendMessage(GetDlgItem(hWindow,IDC_PROMPTEDIT),EM_SETSEL,0,-1);

           return FALSE;
		 }
			
		 return result;
   }

   promptdata = (LPPROMPTINPUT)GetWindowLong(hWindow, DWL_USER);

   if(!promptdata) return FALSE;

   if(promptdata->lpHookProc)
   {
      result = promptdata->lpHookProc(hWindow,uMessage,wParam,lParam);
	  if(result == TRUE) return TRUE; // hook handled processing
   }

   // still up to us to process

   if(uMessage==WM_COMMAND)
   {
          if(wParam==IDCANCEL)
          {
      	 	  EndDialog(hWindow,FALSE);
			  if(promptdata && promptdata->lpstrInputText)
				  *promptdata->lpstrInputText = '\0';
	 	      return(TRUE);
          }
          else if(wParam==IDOK)
          {
      	 	EndDialog(hWindow,TRUE);
			if(promptdata && promptdata->lpstrInputText)
				SendMessage(GetDlgItem(hWindow,IDC_PROMPTEDIT),WM_GETTEXT, promptdata->nMaxInputText, (LPARAM)promptdata->lpstrInputText);
	 	    return(TRUE);
          }

          return FALSE; 
   }

	return FALSE;
}

int GetInputText(PROMPTINPUT *pi)
{

  int result;

  if(!pi) return -1;

  DLGPROC dlgProc;

  dlgProc = (DLGPROC) MakeProcInstance(InputTextDlgWndProc, dllInstance);

  if(!dlgProc) return -1;

  if(pi->hInstance && pi->lpTemplateName)
  {
    result = DialogBoxParam(pi->hInstance, pi->lpTemplateName,
      pi->hwndOwner , dlgProc, (LPARAM)pi);
  }
  else
  {
    result = DialogBoxParam(dllInstance, MAKEINTRESOURCE(IDD_EZINPUT_DIALOG),
      pi->hwndOwner , dlgProc, (LPARAM)pi);
  }

  FreeProcInstance((FARPROC) dlgProc);

  return result;
}

//-------------------------------------------------------------------------

int EZDialog::showDialog(EZWindow *parent,DWORD resource)
{
  int result;

  DLGPROC dlgProc;
  dlgProc = (DLGPROC) MakeProcInstance(DlgWndProc, EZApp->getInstance());

  result = DialogBox(EZApp->getInstance(),MAKEINTRESOURCE(resource),
    parent!=0 ? parent->getHandle() : 0 , dlgProc);

  FreeProcInstance((FARPROC) dlgProc);

  return result;
}

EZDialog::EZDialog()
{
_dlgProc = 0;	
_res = 0;
}

EZDialog::~EZDialog()
{
   if(_dlgProc!=0) FreeProcInstance((FARPROC) _dlgProc);
}

bool EZDialog::create(EZWindow *parent,DWORD resource)
{
  _res = resource;
  _parent = parent;

  _dlgProc = (DLGPROC) MakeProcInstance(DlgWndProc, EZApp->getInstance());

  return _dlgProc != 0;
}

bool EZDialog::show()
{
  int result=0;

  // we have a function and we havent been created yet
  if(_dlgProc != 0 && _window == 0)
  {
    result = DialogBoxParam(EZApp->getInstance(),MAKEINTRESOURCE(_res),
      _parent!=0 ? _parent->getHandle() : 0 , _dlgProc,(LPARAM)this);

  }
  // otherwise use the normal show method
  else return EZWindow::show();

  return result!=0;
}


int EZDialog::showMessageDialog(EZWindow *parent,const char *title,const char *text,UINT type)
{
  return MessageBox(parent!=0 ? parent->getHandle() : 0,
    text,title,type);
}

int EZDialog::showWarningDialog(EZWindow *parent,const char *title,const char *text)
{
  return showMessageDialog(parent,title,text,MB_OK|MB_ICONWARNING);
}
int EZDialog::showErrorDialog(EZWindow *parent,const char *title,const char *text)
{
  return showMessageDialog(parent,title,text,MB_OK|MB_ICONERROR);
}
int EZDialog::showInfoDialog(EZWindow *parent,const char *title,const char *text)
{
  return showMessageDialog(parent,title,text,MB_OK|MB_ICONINFORMATION);
}

int EZDialog::showOKCancelDialog(EZWindow *parent,const char *title,const char *text)
{
  return showMessageDialog(parent,title,text,MB_OKCANCEL);
}

int EZDialog::showFileDialog(EZWindow *parent,const char *title,char *file,
							 EZDialog::FileDialogType type, const char *filter)
{
  int result;
  OPENFILENAME ofn;

  memset(&ofn,0,sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = parent!=0 ? parent->getHandle() : 0;
  ofn.lpstrFilter = filter;
  ofn.lpstrTitle = title;
  //ofn.nMaxFileTitle = strlen(title);
  ofn.lpstrFile = file;
  ofn.nMaxFile = 256;
  //ofn.Flags = 0; //OFN_CREATEPROMPT;
  ofn.Flags  |= OFN_HIDEREADONLY;

  if(type == OPEN)
	  result = GetOpenFileName(&ofn);
  else // SAVE
	  result = GetSaveFileName(&ofn);

  if(result==0)
  {
    result = CommDlgExtendedError();
    char *d=0;
    switch(result)
    {
    case FNERR_BUFFERTOOSMALL:
        d = "buff to small";
        break;
      case CDERR_DIALOGFAILURE:
        d = "dialog failure";
        break;
      case CDERR_FINDRESFAILURE:
        d = "find res failure";
        break;
      case CDERR_INITIALIZATION:
        d = "init error";
        break;
      default:
        d = "unknowm";
        break;  
    }
  }
  return result;
}

BOOL CALLBACK EZDialog::DlgWndProc(HWND hWindow,UINT uMessage,
			WPARAM wParam,LPARAM lParam)
{

   if(uMessage == WM_INITDIALOG)
   {
         //lParam should = a pointer to the dialog - we hope :)
         if(lParam!=0)
         {
           EZDialog *dlg = (EZDialog *)lParam;
           dlg->_window = hWindow;

           // add us to this windowlist
           EZApp->addWindow(dlg);

		   dlg->postMessage(WM_POSTCREATE,0,0);
         }
         return TRUE;
   }

   EZDialog * ezwindow = (EZDialog *)EZApp->findWindow(hWindow); //(EZWindow *)GetWindowLong(hWindow,0);
   /*
    * if we dont have this window in the list then just process any command presses for
    * closing the window - i guess there isnt much else we can do
    */
   if(!ezwindow && uMessage==WM_COMMAND)
   {
          if(wParam==IDCANCEL)
          {
      	 	EndDialog(hWindow,FALSE);
	 	      return(TRUE);
          }
          else if(wParam==IDOK)
          {
      	 	EndDialog(hWindow,TRUE);
	 	      return(TRUE);
          }

          return FALSE; 
   }
   else if(!ezwindow) return FALSE;

   EZEvent msg(wParam,lParam);

    bool result = ezwindow->processMessage(uMessage, &msg);

	if(result==false || ezwindow->_processdefault == true)
	   return ((BOOL)ezwindow->processDefaultMessage(uMessage,&msg));

	return (BOOL)result;
}

int EZDialog::showInputDialog(EZWindow *parent, const char * title, const char *prompt, char *input, 
							  UINT maxinputsize, const char *input_tip_text)
{

  PROMPTINPUT pi;

  memset(&pi,0,sizeof(pi));
  pi.hInstance = EZApp->getInstance(); 
  pi.lStructSize = sizeof(pi);
  pi.hwndOwner = parent!=0 ? parent->getHandle() : 0;
  pi.lpstrTitle = title;
  pi.lpstrPromptText = prompt;
  pi.lpstrInputText = input;
  pi.nMaxInputText = maxinputsize;
  pi.lpstrToolTipText = input_tip_text;

  return GetInputText(&pi);

}

void EZDialog::showLastError(EZWindow *parent)
{
    LPVOID lpMsgBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
    );

    if(lpMsgBuf)
    {
        // Display the string.
        showErrorDialog(parent,"EZError",(char *)lpMsgBuf);


        // Free the buffer.
        LocalFree( lpMsgBuf );
    }
    return;
}


LRESULT EZDialog::processDefaultMessage(UINT uMessage, EZEvent *msg)
{
  return (LRESULT)FALSE;
}

bool EZDialog::processMessage(UINT uMessage, EZEvent *e)
{
   /*
    * normal dialog processing
    */
	switch (uMessage)
	{
	   case WM_CREATE:  // shouldnt ever get
		   return false;

       case WM_COMMAND:
          EZWindow::processMessage(uMessage,e);

          // NOTE: if command -> should not always do this??

          if(e->getWParam()==IDCANCEL)
          {
         	      EndDialog(getHandle(),FALSE);
	 	      return(true);
          }
          else if(e->getWParam()==IDOK)
          {
      	 	EndDialog(getHandle(),TRUE);
	 	      return(true);
          }

          return false;
/*
		case WM_PAINT:
         ezwindow->onPaint(&msg);
         return 0;
      case WM_MOUSEMOVE:
         ezwindow->onMouseMove(&msg);
         return TRUE;
      case WM_LBUTTONDOWN:
         ezwindow->onMouseDown(&msg,0);
         return TRUE;
      case WM_LBUTTONUP:
         ezwindow->onMouseUp(&msg,0);
         return TRUE;
      case WM_MBUTTONDOWN:
         ezwindow->onMouseDown(&msg,1);
         return TRUE;
      case WM_MBUTTONUP:
         ezwindow->onMouseUp(&msg,1);
         return TRUE;
      case WM_RBUTTONDOWN:
         ezwindow->onMouseDown(&msg,2);
         return TRUE;
      case WM_RBUTTONUP:
         ezwindow->onMouseUp(&msg,2);
         return TRUE;

      case WM_TIMER:
         ezwindow->onTimer(&msg);
         return TRUE;
*/
   	 default:
         return EZWindow::processMessage(uMessage,e);

         //return FALSE; //(DefWindowProc(hWindow,uMessage, wParam, lParam));
	}
	return false;
}

EZWindow * EZDialog::getDlgItem(int id)
{
    HWND h = GetDlgItem(getHandle(), id);

	// cant find
	if(h==0) return 0;

	return EZApp->tempWindow(h); // NOTE: DO NOT call delete on a temp window
}

LRESULT EZDialog::sendDlgItemMessage(int id, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
   return SendDlgItemMessage(getHandle(), id, uMessage, wParam, lParam);
}

void EZDialog::onClose(EZEvent *ev)
{
  EndDialog(getHandle(),FALSE);
}

int EZDialog::showColourDialog(EZWindow *parent, EZBrush &brush)
{
  int result;
  CHOOSECOLOR cc;
  static COLORREF custcolours[16];

  memset(&cc,0,sizeof(cc));
  cc.lStructSize = sizeof(cc);
  cc.hwndOwner = parent!=0 ? parent->getHandle() : 0;
  cc.lpCustColors = custcolours;
  cc.Flags = CC_RGBINIT | CC_FULLOPEN;
  cc.rgbResult = brush.getRGB();

  result =  ChooseColor(&cc);

  if(result == 1)
	  brush = cc.rgbResult;

  return result;
}
