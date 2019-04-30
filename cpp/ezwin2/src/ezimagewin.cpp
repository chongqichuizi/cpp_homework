#include <ezimagewin.h>
#include <ezgfx.h>

EZImageWindow::EZImageWindow()
{
  bitmap = 0;	
}
bool EZImageWindow::create(EZWindow *parent,DWORD bmresource,const EZRect &rect)
{
  unsigned long flags = WS_BORDER | WS_VISIBLE;

  if(parent) flags |= WS_CHILD;

  if(bmresource)
   bitmap = new EZBitmap(bmresource);
  else
   bitmap = 0;

  // create the window
  return EZWindow::create(parent,"",flags,rect,-1);
}
EZImageWindow::~EZImageWindow()
{
  if(bitmap) delete bitmap;
}
void EZImageWindow::onPreCreate(CREATESTRUCT *cs)
{
	cs->dwExStyle |= WS_EX_CLIENTEDGE;

	EZWindow::onPreCreate(cs);
}

void EZImageWindow::onPaint(EZEvent *ev)
{
  EZGfx painter(this);
  EZRect rect = getClientRect();

  EZBrush bg = EZBrush::getSystemBrush(COLOR_BTNFACE);

  painter.fillRect(rect,bg);

  if(bitmap)
  {
    painter.drawStretchedBitmap(0,0,rect.getWidth(),rect.getHeight(),*bitmap,RGB(0xff,0xff,0xff));
  }
} 

