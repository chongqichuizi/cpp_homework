#include <ezcolourbutton.h>
#include <ezgfx.h>
#include <ezevent.h>
#include <ezdialog.h>

// TODO - needs to be a owner draw type button

EZColourButton::EZColourButton()
{
  selected = false;
  capture = false;

  _colour = RGB(0,0,0);
}

EZColourButton::~EZColourButton()
{
}

bool EZColourButton::create(EZWindow *parent,const EZBrush &colour, const EZRect &rect, int id)
{
  _colour = colour;
  return EZWindow::create(parent,"",WS_BORDER|WS_VISIBLE,rect,id);
}

void EZColourButton::setColour(const EZBrush &colour)
{
  _colour = colour;
  repaint(getClientRect(),true);
}

EZBrush EZColourButton::getColour()
{
  return _colour;
}

void EZColourButton::onPaint(EZEvent *ev)
{
	EZGfx painter(this);

	EZRect rect = getClientRect();

	painter.fillRect(rect, EZBrush::getSystemBrush(COLOR_BTNFACE));

	UINT uStyle = DFCS_BUTTONPUSH;

	if(selected) uStyle |= DFCS_PUSHED;
    RECT r = rect.toRECT();

	DrawFrameControl(painter.getHandle(), &r, DFC_BUTTON, uStyle);
	
	std::string text = getText();

    rect.moveBy(4,4);
	rect.setWidth( rect.getWidth() - 8);
	rect.setHeight( rect.getHeight() - 8);

	painter.fillRect(rect,_colour);
	
}
void EZColourButton::onMouseDown(EZEvent *ev, int button)
{
  int x = LOWORD(ev->getLParam());
  int y = HIWORD(ev->getLParam());

  selected = true;

  repaint(getClientRect());

  captureMouse(true);

  capture = true;
}
void EZColourButton::onMouseUp(EZEvent *ev, int button)
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

	  EZBrush newbrush = _colour;

	  int res = EZDialog::showColourDialog(this, newbrush);

	  if(res == 1)
	  {
		 setColour(newbrush);

	     EZWindow *p = getParent();

	     if(p) p->postMessage(WM_COMMAND,MAKELONG( getID(),BN_CLICKED),(LONG)getHandle());
	  }
  }
}

void EZColourButton::onMouseMove(EZEvent *ev)
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