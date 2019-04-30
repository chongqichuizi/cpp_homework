
/***********************************************************
 * EZWIN2
 *
 * Name:      ezdialog.h
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

#ifndef ezdialog_h
#define  ezdialog_h

#include <ezwindow.h>

#include <ezbrush.h>

class DLL_EXP EZDialog
 : public EZWindow
{
  DWORD _res; // the handle to the dialog resource if it has one
  DLGPROC _dlgProc;

public:
  EZDialog();

  virtual ~EZDialog();

  bool create(EZWindow *parent,DWORD resource);

public:
  // static methods

  typedef enum { SAVE, OPEN } FileDialogType;

  static int showColourDialog(EZWindow *parent,EZBrush &brush);

  static int showInputDialog(EZWindow *parent, const char * title, const char *prompt, 
	   char *input, UINT maxinputsize,const char *input_tip_text=0);

  static int showDialog(EZWindow *parent,DWORD resource);

  static int showFileDialog(EZWindow *parent,const char *title,char *file, // NOTE: must give a buffer can modify
    FileDialogType type = OPEN, const char *filter="All Files (*.*)\0*.*\0\0");

  static void showLastError(EZWindow *parent);
 
  static int showMessageDialog(EZWindow *parent,const char *title,const char *text,UINT flags);

  static int showWarningDialog(EZWindow *parent,const char *title,const char *text);
  static int showErrorDialog(EZWindow *parent,const char *title,const char *text);
  static int showInfoDialog(EZWindow *parent,const char *title,const char *text);

  static int showOKCancelDialog(EZWindow *parent,const char *title,const char *text);

public:
  LRESULT sendDlgItemMessage(int id, UINT uMessage, WPARAM wParam, LPARAM lParam);

  EZWindow * getDlgItem(int id);

  virtual bool show(); // reimplement show for dialogs

private:
  static BOOL CALLBACK DlgWndProc(HWND hWindow,UINT uMessage,
			WPARAM wParam,LPARAM lParam);

  virtual bool processMessage(UINT uMessage,EZEvent *e);

  virtual LRESULT processDefaultMessage(UINT uMessage,EZEvent *msg);
protected:

  virtual void onClose(EZEvent *ev);
};

#endif // ezdialog_h