#include <ezmultilinebutton.h>
#include <ezgfx.h>
#include <ezevent.h>

EZMultilineButton::EZMultilineButton()
{
   selected = false;
   capture  = false;	
}

bool EZMultilineButton::create(EZWindow *parent, const char *name, const EZRect &rect, int id)
{
	return EZWindow::create(parent,name,WS_VISIBLE|WS_BORDER,rect,id);
}

EZMultilineButton::~EZMultilineButton()
{
}
void EZMultilineButton::onPaint(EZEvent *ev)
{
	EZGfx painter(this);

	EZRect rect = getClientRect();

	painter.fillRect(rect, EZBrush::getSystemBrush(COLOR_BTNFACE));

	UINT uStyle = DFCS_BUTTONPUSH;

	if(selected) uStyle |= DFCS_PUSHED;
    RECT r = rect.toRECT();

	DrawFrameControl(painter.getHandle(), &r, DFC_BUTTON, uStyle);
	
	std::string text = getText();

	if(text.length()>0)
	{
	
		painter.setBkMode(TRANSPARENT);
	    EZRect textrect = painter.calcTextRect(text.c_str(), EZPoint(0,0), DT_CENTER|DT_NOPREFIX); // DT_WORDBREAK
	    textrect = EZRect( rect.getWidth()/2 - textrect.getWidth()/2,  
			               rect.getHeight()/2 - textrect.getHeight()/2,
						   rect.getWidth()/2 + textrect.getWidth()/2,
						   rect.getHeight()/2 + textrect.getHeight()/2);

		if(selected)
		  textrect.moveBy(1,1);

		painter.drawText(text.c_str(), textrect, DT_CENTER|DT_NOPREFIX); //|DT_WORDBREAK);
	}
	
}
void EZMultilineButton::onSetText(EZEvent *ev)
{
   EZWindow::onSetText(ev);
   repaint(getClientRect()); // tell us to redraw 
}
void EZMultilineButton::onMouseDown(EZEvent *ev, int button)
{
  int x = LOWORD(ev->getLParam());
  int y = HIWORD(ev->getLParam());

  selected = true;

  repaint(getClientRect());

  captureMouse(true);

  capture = true;
}
void EZMultilineButton::onMouseUp(EZEvent *ev, int button)
{
  int x = LOWORD(ev->getLParam());
  int y = HIWORD(ev->getLParam());

  if(capture==true) 
  {
	  captureMouse(false);
	  capture = false;
  }

  if(selected)
  {
	  selected = false;
	  repaint(getClientRect());

	  EZWindow *p = getParent();

	  if(p) p->postMessage(WM_COMMAND,MAKELONG( getID(),BN_CLICKED),(LONG)getHandle());

  }
}

void EZMultilineButton::onMouseMove(EZEvent *ev)
{
	if(capture == true)
	{
		int x = LOWORD(ev->getLParam());
		int y = HIWORD(ev->getLParam());

		EZRect rect = getClientRect();

		if(x<0 || x > rect.getWidth()) 
		{
			if(selected == true)
			{
				selected = false;
				repaint(getClientRect());
			}
		}
		else if(y < 0 || y > rect.getHeight())
		{
			if(selected == true)
			{
				selected = false;
				repaint(getClientRect());
			}
		}
		else
		{
			// in area
			if(!selected)
			{
				selected = true;
				repaint(getClientRect());
			}
		}
	}
}