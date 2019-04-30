
#include <ezbutton.h>

EZButton::EZButton()
{
}

bool EZButton::create(EZWindow *parent,const EZIcon &_icon,const EZRect &rect,int id)
{

  unsigned long flags = WS_VISIBLE|BS_ICON;

  bool done = EZWindow::create(parent,"",flags,rect,id);

  if(done) sendMessage(BM_SETIMAGE,(WPARAM)IMAGE_ICON,(LPARAM)(_icon.getHandle()));

  return done;
}

bool EZButton::create(EZWindow *parent,const char *label,const EZRect &rect,int id)
{
  unsigned long flags = WS_VISIBLE;

  // create the window
  return EZWindow::create(parent,label,flags,rect,id);
}


EZButton::~EZButton()
{
}

void EZButton::onPreCreate(CREATESTRUCT *cs)
{
	static const char * classname = "BUTTON";
	cs->lpszClass = classname;
}