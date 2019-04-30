#include <ezcombobox.h>

EZComboBox::EZComboBox()
{
}
bool EZComboBox::create(EZWindow *parent, const char *name, const EZRect &rect, int id)
{
	/// dont have to register class
    // CBS_DROPDOWN CBS_DROPDOWN_LIST CBS_SIMPLE
    // CBS_NOINTEGRALHEIGHT|CBS_DISABLENOSCROLL

	return EZWindow::create(parent,name,WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,rect,id); // dropdown
}
EZComboBox::~EZComboBox()
{
}

int EZComboBox::addItem(const char *str)
{
  int i = sendMessage(CB_ADDSTRING, 0, (LPARAM)str); 
  if(i == CB_ERR || i==CB_ERRSPACE) return -1;
  return i;
}

void EZComboBox::remItem(int index)
{
  sendMessage(CB_DELETESTRING,(WPARAM)index, 0);
}

int EZComboBox::getCount()
{
  int i = sendMessage(CB_GETCOUNT,0,0);
  if(i==CB_ERR) return 0;
  return i;
}

int EZComboBox::findItem(const char *text)
{
  int i = sendMessage(CB_FINDSTRINGEXACT, -1, (LPARAM)text);
  if(i==CB_ERR) return -1;
  return i;
}

int EZComboBox::getCurrItem()
{
  int i = sendMessage(CB_GETCURSEL,0,0);
  if(i==CB_ERR) return -1;
  return i;
}

void EZComboBox::setCurrItem(int index)
{
  sendMessage(CB_SETCURSEL, index, 0);
}

void EZComboBox::setReadOnly(bool yes)
{
  DWORD s = getStyle();

  s = s & ~(CBS_DROPDOWN|CBS_DROPDOWNLIST|CBS_SIMPLE);

  if(yes)
	  s |= CBS_DROPDOWNLIST;
  else
	  s |= CBS_DROPDOWN;

  setStyle(s);
}

void EZComboBox::onPreCreate(CREATESTRUCT *cs)
{
  static const char * classname =  "COMBOBOX";

  cs->lpszClass = classname;
}
