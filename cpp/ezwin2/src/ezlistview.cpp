#include <ezlistview.h>

EZListViewItem::EZListViewItem(EZListView *listview, const char *text, int pos)
{
  _parent = listview;

  LV_ITEM lm = { 0 };

  if(pos<0) pos=-1; // TODO: append at end -> calc where the end is first

  lm.mask = LVIF_TEXT; // LVIF_IMAGE
  lm.iItem = pos;      // the row
  lm.iSubItem = 0;     // the col
  lm.pszText = (char *)text;
  lm.cchTextMax = strlen(text);

  _index = ListView_InsertItem(_parent->getHandle(), &lm);
  
}
EZListViewItem::EZListViewItem(EZListView *listview, int index)
{
	 _parent = listview;
	 _index = index;
}
std::string EZListViewItem::getItemText(int col)
{
  char buff[256]="";

  ListView_GetItemText(_parent->getHandle(), _index, col, buff, 255);

  return std::string(buff);
}

void EZListViewItem::setItemText(const char *text, int col)
{
  if(text) ListView_SetItemText(_parent->getHandle(), _index, col, (char *)text);
}

void EZListViewItem::setItemImage(int imagenum)
{
  LV_ITEM lm = { 0 };

  lm.mask = LVIF_IMAGE;
  lm.iItem = _index; // the row
  lm.iSubItem = 0;   // the col
  lm.iImage = imagenum;

  ListView_SetItem(_parent->getHandle(), &lm);
}


//--------------------------------------------------------

EZListView::EZListView()
{
}

bool EZListView::create(EZWindow *parent,char *text,const EZRect &rect,int id)
{

  unsigned long flags = /*WS_BORDER |*/ WS_VISIBLE | LVS_REPORT;

  // create the window
  return EZWindow::create(parent,text,flags,rect,id);
}

EZListView::~EZListView()
{

}

void EZListView::setColumns(char *text1,char *text2,char *text3,char *text4)
{
  LV_COLUMN lm = { 0 };
  int index=0;

  lm.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
  lm.cx = 100;
  lm.fmt = LVCFMT_LEFT;

  if(text1) {
    lm.pszText = text1;
    SendMessage(getHandle(),LVM_INSERTCOLUMN,index,(LPARAM)&lm);
    index++;
  }
  if(text2) {
    lm.pszText = text2;
    SendMessage(getHandle(),LVM_INSERTCOLUMN,index,(LPARAM)&lm);
    index++;
  }
  if(text3) {
    lm.pszText = text3;
    SendMessage(getHandle(),LVM_INSERTCOLUMN,index,(LPARAM)&lm);
    index++;
  }
  if(text4) {
    lm.pszText = text4;
    SendMessage(getHandle(),LVM_INSERTCOLUMN,index,(LPARAM)&lm);
    index++;
  }

  return;
}


EZListViewItem EZListView::addItem(int index,const char *text)
{
	return EZListViewItem(this, text,index);
}

bool EZListView::setViewMode(EZListView::ViewMode mode)
{
   DWORD style = getStyle();

   style = style & ~LVS_TYPEMASK;
   style |= mode;
   setStyle(style);

   return style != 0;
}

void EZListView::setImageList(const EZImageList &l, int type)
{
  ListView_SetImageList(getHandle(), l.getHandle(), type);
}

void EZListView::arrangeIcons(UINT code)
{
  assert( getHandle() != 0 );
  ListView_Arrange(getHandle(),code);  
}

EZListViewItem EZListView::findItem(const char *text, int startpos)
{
  if(text==0) return EZListViewItem(this, -1);

//VC  LVFINDINFO lm = { 0 };

  LV_FINDINFO lm = { 0 };

  if(startpos<0) startpos = -1; // append at end -> calc where the end is first


  lm.flags = LVFI_STRING;
  lm.psz = text;

  int pos = ListView_FindItem(getHandle(), startpos, &lm);

  return EZListViewItem(this, pos);
}


EZListViewItem EZListView::getItem(int index)
{
  return EZListViewItem(this,index);
}

void EZListView::onPreCreate(CREATESTRUCT *cs)
{
  static const char *classname = WC_LISTVIEW;

  cs->lpszClass = classname;
  cs->style |= LVS_REPORT;
}
