#include <ezmenubar.h>
#include <ezmenu.h>
#include <ezapp.h>

EZMenuBar::EZMenuBar()
//EZWindow *parent,char *name)
//: EZWindow(parent,"MENUBAR",name)
{
  _menubar = 0;
  _parent = 0;

  // dont have to register anything  - this one is predefined

  //unsigned long flags = 0; // /*WS_BORDER |*/ WS_VISIBLE;
  //ES_AUTOVSCROLL

  //if(parent) flags |= WS_CHILD;

  // create the menu - note this has overloaded the
  // window creation
  //create(name,flags,0,0,0,0,0);
}

EZMenuBar::~EZMenuBar()
{
  _menubar = 0;
}

bool EZMenuBar::create(EZWindow *parent)
{
  assert( parent != 0);

  _parent = parent;

  if(!_menubar) _menubar = CreateMenu();

  if(_parent) SetMenu(_parent->getHandle(),(HMENU)_menubar);

  return true;
}

bool EZMenuBar::create(EZWindow *parent, DWORD res)
{
  assert( parent != 0);

  _parent = parent;

//  loadMenuBar(res);
   _menubar = LoadMenu(EZApp->getInstance(), MAKEINTRESOURCE(res));

//  if(!_menubar) _menubar = CreateMenu();

  if(_parent) SetMenu(_parent->getHandle(),(HMENU)_menubar);



  return true;
}

void EZMenuBar::addMenu(char *text,EZMenu *menu)
{
  AppendMenu((HMENU)_menubar,MF_POPUP,(UINT) menu->getHandle(),text);
}

/*
EZMenuBar::EZMenuBar(EZWindow *parent, DWORD res)
: EZWindow(parent,"MENUBAR","")
{
	_window  = 0;

	//create("",0,0,0,0,0,0);
	loadMenuBar(res);
}
*/

void EZMenuBar::redraw()
{
  if(_parent) DrawMenuBar(_parent->getHandle());
}


/*
void EZMenuBar::loadMenuBar(DWORD res)
{
   if(_menubar) DestroyMenu(_menubar);
   _menubar = 0;

   _menubar = LoadMenu(EZApp->getInstance(), MAKEINTRESOURCE(res));

   //create("",0,0,0,0,0,0);  
}
*/
void EZMenuBar::setMenuItemState(int id, DWORD state)
{
	MENUITEMINFO info = { 0 };
  
  info.cbSize = sizeof(MENUITEMINFO);
  info.fMask = MIIM_STATE;
  info.fState = state;
 
  SetMenuItemInfo(_menubar,id, FALSE, &info);
}

DWORD EZMenuBar::getMenuItemState(int id)
{
	MENUITEMINFO info = { 0 };
  
  info.cbSize = sizeof(MENUITEMINFO);
  info.fMask = MIIM_STATE;
//  info.fState = state;
 
  GetMenuItemInfo(_menubar,id, FALSE, &info);

  return info.fState;
}

void EZMenuBar::setMenuItemCheck(int id, bool checked)
{
  DWORD state = getMenuItemState(id);
  state &= ~(MFS_CHECKED);
  if(checked) state |= MFS_CHECKED;

  setMenuItemState(id, state);
}

bool EZMenuBar::getMenuItemCheck(int id)
{
  DWORD state = getMenuItemState(id);
  if(state & MFS_CHECKED) return true;
  return false;
}
