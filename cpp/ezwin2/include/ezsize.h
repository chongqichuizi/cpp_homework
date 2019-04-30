

/***********************************************************
 * EZWIN2
 *
 * Name:      ezsize.h
 * version:   0.1
 * date:      28 April 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezsize_h

#define ezsize_h

#include <ezwin.h>

class DLL_EXP EZSize : private SIZE
{
public:
  EZSize(unsigned int w = 0,unsigned int h = 0)
  {
    cx = w;
    cy = h;
  }
  EZSize(const SIZE &size)
  {
	  cx = size.cx;
	  cy = size.cy;
  }

  ~EZSize() { }

  inline unsigned int getWidth() const { return cx; }
  inline unsigned int getHeight() const { return cy; }

  inline bool isValid() const { return (cx!=0 && cy!=0); }

  inline SIZE toSIZE() const
  {
	  SIZE s;
	  s.cx = cx;
	  s.cy = cy;

	  return s;
  }

};

class DLL_EXP EZPoint : private POINT
{
public:
	EZPoint(int x=0, int y=0) { this->x = x; this->y = y; }
   ~EZPoint() {}

   EZPoint(POINT p)
   {
	   this->x = p.x;
	   this->y = p.y;
   }

   int getX() const { return x; }
   int getY() const { return y; }

   void setX(int x) { this->x = x; }
   void setY(int y) { this->y = y; }


   void setPoint(int x, int y)
   {
	 this->x = x;
	 this->y = y;
   }

   EZPoint &operator+=(EZPoint &pt)
   {
	  this->x += pt.x;
	  this->y += pt.y;

	  return *this;
   }
   EZPoint &operator-=(EZPoint &pt)
   {
	  this->x -= pt.x;
	  this->y -= pt.y;

	  return *this;
   }
   EZPoint operator+(EZPoint &pt)
   {
	  EZPoint result; 
	  result.x = x + pt.x;
	  result.y = y + pt.y;

	  return result;
   }
   EZPoint operator-(EZPoint &pt)
   {
	  EZPoint result; 
	  result.x = x - pt.x;
	  result.y = y - pt.y;

	  return result;
   }
   EZPoint operator*(int scale)
   {
	  EZPoint result; 
	  result.x = x * scale;
	  result.y = y * scale;

	  return result;
   }
   POINT toPOINT() const
   { 
	   POINT p; 
	   p.x = x; 
	   p.y = y;

	   return p;
   }
};

class DLL_EXP EZRect : private RECT
{
  public:

    ~EZRect() { }

    EZRect(int x1=0,int y1=0,int x2=-1,int y2=-1)
    {
      left = x1;
      right = x2;
      top = y1;
      bottom = y2;
    }
    EZRect(const RECT &r)
    {
      left = r.left;
      right = r.right;
      top = r.top;
      bottom = r.bottom;
    }
    EZRect(const EZSize &s)
    {
      left = 0;
      right = s.getWidth();
      top = 0;
      bottom = s.getHeight();
    }
    RECT toRECT() const
    {
      RECT r;
      r.left = left;
      r.right = right;
      r.top = top;
      r.bottom = bottom;

      return r;
    }
	bool fix()
	{
		int t;
		bool ch = false;

		// empty
		if(left == 0 && top == 0 && right == -1 && bottom == -1) return false;

		if(left > right)
		{
			t = left;
			left = right;
			right = t;
			ch = true;
		}
		if(top > bottom)
		{
			t = top;
			top = bottom;
			bottom = t;;
			ch = true;
		}
        return ch;
	}

	EZRect operator|(const EZRect &r) const
	{
       EZRect nr;

         if(!isValid()) return r;

	   nr.left = (left < r.left) ? left : r.left;
	   nr.right = (right > r.right) ? right : r.right;
	   nr.top = (top < r.top) ? top : r.top;
	   nr.bottom = (bottom > r.bottom) ? bottom : r.bottom;	  
	   
	   return nr;
	}

	void expand(int by_x, int by_y) // expand/conpress
	{
		left -= by_x;
		right += by_x;
		top -= by_y;
		bottom += by_y;
	}
	void expand(int by)
	{
		expand(by,by);
	}

    inline bool isValid() const { return ( left<right && top < bottom ); }

    inline int getX() const { return left; }
    inline int getY() const { return top; }

    inline int getLeft() const { return left; }
    inline int getTop() const { return top; }
    inline int getRight() const { return right; }
    inline int getBottom() const { return bottom; }

    inline void setLeft(int x) { left = x; }
    inline void setTop(int y) { top = y; }
    inline void setRight(int w) { right = w; }
    inline void setBottom(int h) { bottom = h; }

    void moveBy(int xoff,int yoff)
    {
      left += xoff;
      right += xoff;
      top += yoff;
      bottom += yoff;
    }
    void moveTo(int x,int y)
    {
      right = x + getWidth();
      left = x;
      bottom = y + getHeight();
      top = y;
    }


    inline unsigned int getWidth() const { return right - left; }
    inline unsigned int getHeight() const { return bottom - top; }

    inline void setWidth(int w) { right = left+w; }
    inline void setHeight(int h) { bottom = top+h; }

    inline EZSize getSize() const { return EZSize(getWidth(),getHeight()); }

    inline bool contains(int x,int y) const
    {
       if(x<left || y<top) return false;
       if(x>right || y>bottom) return false;

       return true;
    }
    EZPoint getCenter()
    {
       int x,y;
       x = left + (right - left)/2;
       y = top + (bottom - top)/2;
       return EZPoint(x,y);
    }

};

#endif // ezsize_h
