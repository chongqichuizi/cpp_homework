
/***********************************************************
 * EZWIN2
 *
 * Name:      eztxetedit.h
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

#ifndef eztextedit_h
#define eztextedit_h

#include <ezwindow.h>

class DLL_EXP EZTextEdit
 : public EZWindow
{
public:
  EZTextEdit();
  
  virtual ~EZTextEdit();

  bool create(EZWindow *parent,const char *name,
	  const EZRect &rect=EZRect(),
	  int id=-1);


  bool addLine(const char *str);
  std::string getLine(int line);
  int getNumLines();
  void setReadOnly(bool yes);

  bool loadFile(const char *name);
  bool saveFile(const char *name);
protected:
	virtual void onPreCreate(CREATESTRUCT *cs);
};


#endif // eztextedit_h
