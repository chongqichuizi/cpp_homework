#include <ezmenu.h>

EZMenu::EZMenu()
{
  _parent = 0;
  _menu = 0;
}

EZMenu::~EZMenu()
{

}

bool EZMenu::create(EZWindow *parent,const char *winname)
{
  _parent = parent;
  _menu = CreateMenu();
  return true;
}

void EZMenu::addItem(const char *text,int id)
{
  AppendMenu((HMENU)_menu,MF_STRING,id,text);
}
void EZMenu::addSeparator()
{
  AppendMenu((HMENU)_menu,MF_SEPARATOR,0,0);
}
