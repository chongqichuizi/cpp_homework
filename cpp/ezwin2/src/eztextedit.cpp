#include <eztextedit.h>
#include <fstream>
#include <sys/types.h> 
#include <sys/stat.h> 

EZTextEdit::EZTextEdit()
{
	
}

EZTextEdit::~EZTextEdit()
{

}
bool EZTextEdit::create(EZWindow *parent,const char *name,
	  const EZRect &rect,
	  int id)
{
    unsigned long flags = /*WS_BORDER |*/ WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL|WS_VSCROLL;

	return EZWindow::create(parent,name,flags,rect,id);
}
void EZTextEdit::onPreCreate(CREATESTRUCT *cs)
{
  static const char *classname = "EDIT";
  cs->lpszClass = classname;
}

bool EZTextEdit::loadFile(const char *name)
{
    struct stat statbuf;

	if( stat( name, &statbuf )!=0) return false;

#ifdef __BORLANDC__
    ifstream file(name, ios::in);
#else
    std::ifstream file(name, std::ios::in);
#endif
	if(file)
	{

	}
	return false;
}
bool EZTextEdit::saveFile(const char *name)
{
	return false;
}

void EZTextEdit::setReadOnly(bool yes)
{
  if(yes)
	  sendMessage(EM_SETREADONLY,(WPARAM)(BOOL)TRUE, 0);
  else
	  sendMessage(EM_SETREADONLY,(WPARAM)(BOOL)FALSE, 0);
}

int EZTextEdit::getNumLines()
{
  return sendMessage(EM_GETLINECOUNT, 0,0);
}

std::string EZTextEdit::getLine(int line)
{
  char buffer[1024];
  short *ptr;
  ptr = (short *)buffer;
  *ptr = 1023;

  int i = sendMessage(EM_GETLINE, line, (LPARAM)buffer);
  if(i<=0) 
	  return "";
  else 
	  return buffer;
}

bool EZTextEdit::addLine(const char *str)
{
/*
  CString str = mesg + _T("\r\n");

  int len = m_wndEdit.GetWindowTextLength();
  //SendMessage(EM_SETSEL,len,len);
  //SendMessage(EM_REPLACESEL,(WPARAM)FALSE,(LPARAM)LPCTSTR(mesg));
  m_wndEdit.SetSel(len,len);
  m_wndEdit.ReplaceSel(str);
*/
	return false;
}
