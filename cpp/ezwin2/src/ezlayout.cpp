#include <ezlayout.h>
#include <ezsize.h>
#include <ezwindow.h>



//----------------------------------------------------------------
EZLayout::EZLayout(EZWindow *parent)  { _parent=parent; }
EZLayout::~EZLayout() { }
//----------------------------------------------------------------

EZMainWindowLayout::EZMainWindowLayout(EZWindow *parent)
  : EZLayout(parent)
{
  _mainw = 0;
  _toolbar = 0;
  _statusbar = 0;
}
EZMainWindowLayout::~EZMainWindowLayout()
{

}

void EZMainWindowLayout::setToolBar(EZWindow *toolbar)
{
  _toolbar = toolbar;
}
void EZMainWindowLayout::setMainWindow(EZWindow *mainw)
{
  _mainw = mainw;
}
void EZMainWindowLayout::setStatusBar(EZWindow *status)
{
  _statusbar = status;
}

void EZMainWindowLayout::doLayout()
{
  // do the layout for the direct children of this parent
  if(_parent==0) return;

  EZRect s = _parent->getClientRect();
  if(_statusbar && _statusbar->isVisible())
  {
    EZSize statsize = _statusbar->getSize();
    EZRect r(0,s.getHeight()-statsize.getHeight()-1,s.getWidth(),s.getHeight()); //statsize.getHeight());
    _statusbar->setRect(r);

    s.setBottom(s.getBottom()-statsize.getHeight()+1);
    //_statusbar->redraw();
  }

  if(_toolbar && _toolbar->isVisible())
  {
    EZSize toolsize = _toolbar->getSize();
    EZRect r1(EZSize(s.getWidth(),toolsize.getHeight()));
    _toolbar->setRect(r1);
    s.setTop(s.getTop()+toolsize.getHeight());
    //_toolbar->redraw();
  }
  if(_mainw)
  {
    if(s.isValid())
      _mainw->setRect(s);
  }
  return;
}
//--------------------------------------------------------------
EZColumnLayout::EZColumnLayout(EZWindow *parent)
: EZLayout(parent)
{

}
EZColumnLayout::~EZColumnLayout()
{

}
int EZColumnLayout::setWidth(int col, int width)
{
	int old = _widths[col];

	_widths[col] = width;

	return old;
}
void EZColumnLayout::doLayout()
{
  EZWindow *child;
  int childcount = 0;
  int i;
  int t;
  double x;

  if(_parent)
  {
	// calc num of children we have
    child= _parent->getFirstChild();
	while(child)
	{
		childcount++;
		child = _parent->getNextChild(child);
	}

	if(childcount > 0)
	{
        // work out any fixed stuff
		int fixed=0;
		int fixedcount=0;
		for(i=0;i<childcount;i++)
		{
			if(_widths[i]>0)
			{
				fixed += _widths[i];
				fixedcount ++;
			}
		}
		

		// can work out sizes for them
		EZRect rect = _parent->getClientRect();

		double width;
		
		if(fixedcount < childcount) 
			width = ((double)(rect.getWidth() - fixed)/(childcount-fixedcount));
		else 
			width = 1.0;
		if(width < 0.0) 
			width=1.0;

		child = _parent->getFirstChild();
        x = 0.0;

        for(i=0;i<childcount && child!=0;i++)
		{
		   t = _widths[i];

		   if(t<=0) 
		   {
				child->setRect( EZRect((int)x,rect.getY(),
			        (int)(x + width), rect.getBottom() ) );

				x += width;
		   }
		   else if(i == childcount-1) // is last one, and has fixed size 
			                         // -> ignore size - it should be correct size
									 // unless we ran out of room
		   {
			    child->setRect( EZRect((int)x,rect.getY(),
			        rect.getRight(), rect.getBottom() ) );
		   }
		   else { // has a specified size

				child->setRect( EZRect((int)x,rect.getY(),
			        (int)(x + t), rect.getBottom() ) );

				x += t;

		   }

		   child = _parent->getNextChild(child);
		}
	}
  }
}

//--------------------------------------------------------------
EZRowLayout::EZRowLayout(EZWindow *parent)
: EZLayout(parent)
{

}
EZRowLayout::~EZRowLayout()
{

}
int EZRowLayout::setHeight(int col, int height)
{
	int old = _heights[col];

	_heights[col] = height;

	return old;
}
void EZRowLayout::doLayout()
{
  EZWindow *child;
  int childcount = 0;
  int visiblechild = 0;
  int i;
  int t;
  double y;

  if(_parent)
  {
	// calc num of children we have
    child= _parent->getFirstChild();
	while(child)
	{
		childcount++;
		if(child->isVisible()) visiblechild++;

		child = _parent->getNextChild(child);
	}

    child= _parent->getFirstChild();
	if(childcount > 0)
	{
        // work out any fixed stuff
		int fixed=0;
		int fixedcount=0;
		for(i=0;i<childcount;i++)
		{
			if(_heights[i]>0)
			{
				if(child && !child->isVisible()) {}
				else 
				{
					fixed += _heights[i];
				    fixedcount ++;
				}
			}
			child = _parent->getNextChild(child);
		}
		

		// can work out sizes for them
		EZRect rect = _parent->getClientRect();

		double height;
		
		if(fixedcount < childcount) 
			height = ((double)(rect.getHeight() - fixed)/(visiblechild-fixedcount));
		else 
			height = 1.0;
		if(height < 0.0) 
			height=1.0;

		child = _parent->getFirstChild();
        y = 0.0;

        for(i=0;i<childcount && child!=0;i++)
		{
		   t = _heights[i];

		   if(t<=0) 
		   {
			    if(child->isVisible())
				{
				  child->setRect( EZRect(rect.getX(), (int)y,
			        rect.getRight(), (int)(y + height) ) );

				  y += height;
				}
		   }
		   else if(i == childcount-1) // is last one, and has fixed size 
			                         // -> ignore size - it should be correct size
									 // unless we ran out of room
		   {
			    if(child->isVisible())
				    child->setRect( EZRect(rect.getX(), (int)y,
			          rect.getRight(), rect.getBottom() ) );
		   }
		   else { // has a specified size

				if(child->isVisible())
				{
					child->setRect( EZRect( rect.getX(), (int)y,
			        rect.getRight(), (int)(y + t) ) );

				    y += t;
				}

		   }

		   child = _parent->getNextChild(child);
		}
	}
  }
}
//---------------------------------------------------------------------
EZSingleClientLayout::EZSingleClientLayout(EZWindow *parent)
: EZLayout(parent)
{

}
EZSingleClientLayout::~EZSingleClientLayout()
{
}
void EZSingleClientLayout::doLayout()
{
  if(_parent)
  {
	EZWindow * w = _parent->getFirstChild();

	if(w)
	{
		EZRect r = _parent->getClientRect();
		
		w->setRect(r);
    }
  }
}