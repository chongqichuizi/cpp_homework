#include <eztreeview.h>

EZTreeViewItem::EZTreeViewItem(EZTreeView *treeview,EZTreeViewItem *parent,char *text)
{
  TV_INSERTSTRUCT tvi = { 0 };

  _handle = 0;
  //memset(&_tvi,0,sizeof(_tvi));

  tvi.hParent = parent!=0 ? parent->_handle : TVI_ROOT;
  tvi.hInsertAfter = TVI_LAST;
  // TV_ITEM
  tvi.item.mask = TVIF_TEXT;
  tvi.item.pszText = text;
  tvi.item.cchTextMax = strlen(text);

  _handle = (HTREEITEM) SendMessage(treeview->getHandle(),TVM_INSERTITEM,0,
      (LPARAM)&tvi);

  _tree = treeview;

}
/*
TreeViewItem::TreeViewItem(EZTreeView *treeview,EZTreeViewItem *parent,HTREEITEM item)
{
  _handle = item;
}
*/
EZTreeViewItem::~EZTreeViewItem()
{

}
void EZTreeViewItem::setItemImage(int imagenum)
{
  TV_ITEM  iteminfo = {0};  //VC knows TVITEM, TVINSERT etc

  iteminfo.hItem = _handle;
  iteminfo.mask = /*TVIF_HANDLE|*/ TVIF_IMAGE|TVIF_SELECTEDIMAGE;
  iteminfo.iImage = imagenum;
  iteminfo.iSelectedImage = imagenum;


  _tree->sendMessage(TVM_SETITEM, 0, (LPARAM)&iteminfo);
}

void EZTreeViewItem::setItemData(void *data)
{
  TV_ITEM  iteminfo = {0};

  iteminfo.hItem = _handle;
  iteminfo.mask = TVIF_PARAM ;
  iteminfo.lParam = (LPARAM)data;

  _tree->sendMessage(TVM_SETITEM, 0, (LPARAM)&iteminfo);
}

void * EZTreeViewItem::getItemData()
{
  TV_ITEM  iteminfo = {0};

  iteminfo.hItem = _handle;
  iteminfo.mask = TVIF_PARAM ;

  _tree->sendMessage(TVM_GETITEM, 0, (LPARAM)&iteminfo);

  return (void *)iteminfo.lParam;
}

std::string EZTreeViewItem::getItemText()
{
   TV_ITEM  iteminfo = {0};
   char buffer [256];

  iteminfo.hItem = _handle;
  iteminfo.mask = TVIF_TEXT;
  iteminfo.cchTextMax = 255;
  iteminfo.pszText= buffer;

  _tree->sendMessage(TVM_GETITEM, 0, (LPARAM)&iteminfo);

  return buffer; 
}
//-----------------------------------------------------------------------------
/*
#define TVS_HASBUTTONS          0x0001
#define TVS_HASLINES            0x0002
#define TVS_LINESATROOT         0x0004
#define TVS_EDITLABELS          0x0008
#define TVS_DISABLEDRAGDROP     0x0010
#define TVS_SHOWSELALWAYS       0x0020
*/

EZTreeView::EZTreeView()
{
	root = 0;
}

bool EZTreeView::create(EZWindow *parent,const char *name,bool showroot)
{
// : EZWindow(parent,WC_TREEVIEW,name)
//{
  // dont have to register anything  - this one is predefined

  root = 0;

  unsigned long flags = /*WS_BORDER |*/ WS_VISIBLE; 
  //ES_AUTOVSCROLL

  if(parent) flags |= WS_CHILD;

  // create the window
  bool ok = EZWindow::create(parent,name,flags,EZRect(0,0,100,100),0);

  if(showroot)
  {
    EZTreeViewItem i = addItem(0,(char *)name);
    root = new EZTreeViewItem ( i );
  }
//  EZTreeViewItem it = addItem(0,"2nd one");
//  it = addItem(&it,"3nd one");

  return ok;

}
EZTreeView::~EZTreeView()
{

}
EZTreeViewItem EZTreeView::addItem(EZTreeViewItem *parentitem,char *text)
{
/*
  TV_INSERTSTRUCT tvi = { 0 };

  tvi.hParent = TVI_ROOT;
  tvi.hInsertAfter = TVI_LAST;
  // TV_ITEM
  tvi.item.mask = TVIF_TEXT;
  tvi.item.pszText = text;
  tvi.item.cchTextMax = strlen(text);

   HTREEITEM item = (HTREEITEM) SendMessage(_window,TVM_INSERTITEM,0,
      (LPARAM)&tvi);
   return EZTreeViewItem(item);
*/
   return EZTreeViewItem(this,parentitem,text);
}


void EZTreeView::setImageList(const EZImageList &I)
{
  TreeView_SetImageList(getHandle(), I.getHandle(), TVSIL_NORMAL ); //TVSIL_STATE );

  //TreeView_GetImageList(
}


void EZTreeView::onPreCreate(CREATESTRUCT *cs)
{
  static const char *classname = WC_TREEVIEW;

  cs->lpszClass = classname;
  cs->style |= (TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);
}
