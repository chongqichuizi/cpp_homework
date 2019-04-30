#include <ezstatic.h>

EZStatic::EZStatic()
{
}

bool EZStatic::create(EZWindow *parent,const char *text, const EZRect &rect, int id)
{
	return EZWindow::create(parent, text, WS_VISIBLE, rect, id);
}

EZStatic::~EZStatic()
{
}

void EZStatic::onPreCreate(CREATESTRUCT *cs)
{
  static const char * classname = "STATIC";

  cs->lpszClass = classname;
}
