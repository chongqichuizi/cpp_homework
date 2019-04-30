#include <ezmdichildwindow.h>
#include <ezevent.h>

EZMDIChildWindow::EZMDIChildWindow()
{
}

bool EZMDIChildWindow::create(EZWindow *parent,const char *name,const EZRect &rect)
{
  return EZWindow::create(parent,name,WS_VISIBLE,rect,0);
}

void EZMDIChildWindow::onCreate(EZEvent *ev)
{
/*
  if(getParent())
  {
	  EZWindow *p = getParent();

	  char buffer[256];
	  if(GetClassName(p->getHandle(), buffer, 255)!=0)
	  {
         if(stricmp("MDICLIENT", buffer)!= 0)
		 {
			 // isnt the mdi client
			p = p->getFirstChild();
			if(p)
			{
	            if(GetClassName(p->getHandle(), buffer, 255)!=0)
				{
                   if(stricmp("MDICLIENT", buffer)== 0)
				   {
					   // found the MDI -> put it to here
					   setParent(p);
				   }
				}
			}
		 }
	  }
  }
*/
}
EZMDIChildWindow::~EZMDIChildWindow()
{
}

void EZMDIChildWindow::onPreCreate(CREATESTRUCT *cs)
{
  assert( getParent() != 0 );
  cs->style |= (WS_VISIBLE|WS_OVERLAPPEDWINDOW | WS_SYSMENU |WS_VISIBLE|MDIS_ALLCHILDSTYLES);
  cs->dwExStyle |= WS_EX_MDICHILD;
}

void EZMDIChildWindow::onDestroy(EZEvent *ev)
{
	processDefault();
}

void EZMDIChildWindow::onClose(EZEvent *ev)
{
	processDefault();
}

LRESULT EZMDIChildWindow::processDefaultMessage(UINT message, EZEvent *ev)
{
  return DefMDIChildProc(getHandle(),message, ev->getWParam(), ev->getLParam());
}
