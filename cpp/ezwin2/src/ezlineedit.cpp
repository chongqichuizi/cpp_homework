#include <ezlineedit.h>

EZLineEdit::EZLineEdit()
{
}

bool EZLineEdit::create(EZWindow *parent,const char *Line, const EZRect &rect, int id)
{

  unsigned long flags = /*WS_BORDER |*/ WS_VISIBLE;

  if(parent) flags |= WS_CHILD|WS_BORDER;

  // create the window
  return EZWindow::create(parent,Line,flags,rect,id);
}

EZLineEdit::~EZLineEdit()
{

}

void EZLineEdit::setMaxLength(UINT m)
{
  // NOTE: m is number of bytes used - if we were in widechar mode,
  // this would need to be bigger!
  SendMessage(getHandle(),EM_SETLIMITTEXT, m , 0);
}

void EZLineEdit::onPreCreate(CREATESTRUCT *cs)
{
  static const char *classname = "EDIT";

  cs->lpszClass = classname;
}
