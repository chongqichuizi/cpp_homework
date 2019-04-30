#include <ezimagelist.h>

#ifdef __BORLANDC__
  // note: borland c is not updated enough for this
  // TODO !!!!
  HIMAGELIST _import WINAPI ImageList_Duplicate(HIMAGELIST tocopy)
  {
   return 0;
  }
  //
#endif

EZImageList::EZImageList(int imagesize)
{
	_handle = ImageList_Create(imagesize, imagesize ,TRUE, 1, 0);
}
EZImageList::~EZImageList()
{
  if(_handle) ImageList_Destroy(_handle);
}
EZImageList::EZImageList(const EZImageList &lst)
{
	_handle = ImageList_Duplicate(lst.getHandle() );
}
EZImageList & EZImageList::operator=(const EZImageList &lst)
{
  if(_handle) ImageList_Destroy(_handle);
  _handle = ImageList_Duplicate(lst.getHandle() );  
  return *this;
}

int EZImageList::addImage(const EZIcon &icon)
{
  return ImageList_AddIcon(_handle, icon.getHandle() );
}
