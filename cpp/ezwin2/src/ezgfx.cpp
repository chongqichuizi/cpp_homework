#include <ezgfx.h>
#include <ezwindow.h>
#include <ezsize.h>

#include <ezbrush.h>
#include <ezpen.h>


EZGfx::EZGfx(EZWindow *w,bool paint)
{
  if(paint)
    _hdc = BeginPaint(w->getHandle(), &_ps);
  else
    _hdc = GetDC(w->getHandle());

  _paint=paint;
  _win = w;

  _oldpen = setPen(_currpen);
  _oldbrush = setBrush(_currbrush);
  _oldfont = setFont(_currfont);

}
EZGfx::~EZGfx()
{
  // restore old gdi resources
  setPen(_oldpen);
  setBrush(_oldbrush);
  setFont(_oldfont);


  if(_paint) EndPaint(_win->getHandle(),&_ps);
  else ReleaseDC(_win->getHandle(),_hdc);
}
bool EZGfx::getTextMetrics(LPTEXTMETRIC lpm)
{
  if(lpm == 0) return false;

  return GetTextMetrics(_hdc,lpm) == TRUE;
}
int EZGfx::getDeviceCaps(int index)
{
  return GetDeviceCaps(_hdc,index); 
}
void EZGfx::setBkMode(int mode)
{
	SetBkMode(_hdc, mode);
}
void EZGfx::drawLine(int x1,int y1,int x2,int y2)
{
   moveTo(x1,y1);
   lineTo(x2,y2);
   return;
}
void EZGfx::setPixel(int x1, int y1, const EZPen &p)
{
  SetPixel(_hdc,x1,y1, p.getRGB());
}
EZPen EZGfx::getPixel(int x, int y)
{
  return EZPen(GetPixel(_hdc,x,y));
}
void EZGfx::draw3DLine(int x1,int y1,int x2,int y2)
{
   EZPen shadow = EZPen::getSystemPen(COLOR_BTNSHADOW);
   EZPen light =  EZPen::getSystemPen(COLOR_BTNHIGHLIGHT);

   EZPen old = setPen(light);
   drawLine(x1,y1,x2,y2);
   setPen(shadow);
   drawLine(x1-1,y1-1,x2-1,y2-1);
   setPen(old);
   return;
}
EZFont EZGfx::getFont()
{
  return _currfont;
}
EZPen EZGfx::getPen()
{
  return _currpen;
}
EZBrush EZGfx::getBrush()
{
  return _currbrush;
}

EZFont EZGfx::setFont(const EZFont &font)
{
  HFONT old = (HFONT)SelectObject(_hdc,font.getHandle());

  _currfont = font;

  return EZFont(old);
}
EZPen EZGfx::setPen(const EZPen &pen)
{
  HPEN old = (HPEN)SelectObject(_hdc,pen.getHandle());

  _currpen = pen;

  return EZPen(old);
}
EZBrush EZGfx::setBrush(const EZBrush &brush)
{
  HBRUSH old = (HBRUSH)SelectObject(_hdc,brush.getHandle());

  _currbrush = brush;

  return EZBrush(old);
}
EZPen EZGfx::setTextColour(const EZPen &p)
{
   COLORREF rgb = SetTextColor(_hdc,p.getRGB());

   return EZPen(rgb);
}
EZPen EZGfx::getTextColour()
{
	return EZPen(GetTextColor(_hdc));
}
EZPen EZGfx::setBkColour(const EZPen &p)
{
   COLORREF rgb = SetBkColor(_hdc,p.getRGB());

   return EZPen(rgb);
}
EZPen EZGfx::getBkColour()
{
	return EZPen(GetBkColor(_hdc));
}
void EZGfx::floodFill(int x, int y, const EZPen &p)
{
  FloodFill(_hdc,x,y,p.getRGB());
}

EZPoint EZGfx::getCurrentPosition()
{
   POINT lppoint;

   GetCurrentPositionEx(_hdc,&lppoint);
  
   return EZPoint(lppoint.x, lppoint.y);
}

void EZGfx::moveTo(int x, int y)
{
   MoveToEx(_hdc, x,y, NULL);  
}
void EZGfx::drawCircle(const EZRect &rect)
{
   drawCircle(rect.getLeft(), rect.getTop(), rect.getRight(), rect.getBottom());	
}
void EZGfx::drawCircle(int left, int top, int right, int bottom)
{
   drawArc(left, top, right, bottom,left+(right-left)/2,top,left+(right-left)/2,top);	
}
void EZGfx::drawArc(const EZRect &rect, const EZPoint &start, const EZPoint &end)
{
   drawArc(rect.getLeft(), rect.getTop(), rect.getRight(), rect.getBottom(), start.getX(), start.getY(), end.getX(), end.getY());	
}
void EZGfx::drawArc(int left, int top, int right, int bottom, int start_x, int start_y, int end_x, int end_y)
{
   Arc(_hdc, left, top, right, bottom, start_x, start_y, end_x, end_y);	
}

void EZGfx::lineTo(int x, int y)
{
   LineTo(_hdc, x,y);
}

void EZGfx::fillRect(const EZRect &r,const EZBrush &cr)
{
   RECT rt = r.toRECT();

   FillRect(_hdc,&rt,cr.getHandle());

}
void EZGfx::fillRect(int x1, int y1, int x2, int y2, const EZBrush &cr)
{
   fillRect(EZRect(x1,y1,x2,y2),cr);
}

void EZGfx::drawText(const char *str,const EZRect &r,UINT flags, int len)
{
  RECT rt = r.toRECT();
  if(len < 0) len = strlen(str);

  DrawText(_hdc,str,len,&rt,flags);
}
void EZGfx::drawText(const char *str,const EZPoint &pt,UINT flags, int len)
{
  if(len < 0) len = strlen(str);

  EZRect rt = calcTextRect(str,pt,flags, len);

  drawText(str,rt,flags, len);
}

EZRect EZGfx::calcTextRect(const char *str, const EZPoint &pt, UINT flags, int len)
{
   RECT rt;
   flags |= DT_CALCRECT;
  
   if(len < 0) len = strlen(str);

   rt.left = pt.getX();
   rt.top  = pt.getY();

   DrawText(_hdc,str,len,&rt,flags);

   return rt;
}

void EZGfx::drawRect(const EZRect &r)
{
  drawRect(r.getX(), r.getY(), r.getRight(), r.getBottom() );
}
void EZGfx::drawRect(int x1, int y1, int x2, int y2)
{
  moveTo(x1,y1);
  lineTo(x2,y1);
  lineTo(x2,y2);
  lineTo(x1,y2);
  lineTo(x1,y1);
}

void EZGfx::patBlt(EZRect &r,int mode)
{
  PatBlt(_hdc,r.getX(),r.getY(),r.getWidth(),r.getHeight(),mode);
}

void EZGfx::draw3DRect(const EZRect &r, bool inverted)
{
	HANDLE old;

   EZPen shadow = EZPen::getSystemPen(COLOR_BTNSHADOW);
   EZPen light =  EZPen::getSystemPen(COLOR_BTNHIGHLIGHT);

   if(!inverted) old=SelectObject(_hdc,shadow.getHandle());
   else old = SelectObject(_hdc,light.getHandle());

   drawLine(r.getRight()-1,r.getTop(),r.getRight()-1,r.getBottom()-1);
   drawLine(r.getRight()-1,r.getBottom()-1,r.getLeft(),r.getBottom()-1);

   if(!inverted) SelectObject(_hdc,light.getHandle());
   else SelectObject(_hdc,shadow.getHandle());

   drawLine(r.getLeft(),r.getBottom()-1,r.getLeft(),r.getTop());
   drawLine(r.getLeft(),r.getTop(),r.getRight()-1,r.getTop());

   SelectObject(_hdc,old);

   return;
}
void EZGfx::bitBlit(const EZRect &destrect,const EZGfx &gfx,int fromx,int fromy,DWORD oper)
{
  BitBlt(
    _hdc, // handle to destination device context
    destrect.getX(),  // x-coordinate of destination rectangle's upper-left
               // corner
    destrect.getY(),  // y-coordinate of destination rectangle's upper-left
               // corner
    destrect.getWidth(),  // width of destination rectangle
    destrect.getHeight(), // height of destination rectangle
    gfx._hdc,  // handle to source device context
    fromx,   // x-coordinate of source rectangle's upper-left corner
    fromy,   // y-coordinate of source rectangle's upper-left corner
    oper  // raster operation code
  );
}

void EZGfx::drawBitmap(int x,int y,const EZBitmap &bm,COLORREF col)
{
	HDC tDC;
	HBITMAP old;
	BITMAP bmap;

   if(col==-1)
   {
    	tDC=CreateCompatibleDC(_hdc);
	   old=(HBITMAP)SelectObject(tDC,(HANDLE)bm.getHandle());
   	GetObject(bm.getHandle(),sizeof(BITMAP),&bmap);

   	BitBlt(_hdc,x,y,bmap.bmWidth,bmap.bmHeight,tDC,0,0,SRCCOPY);
   	SelectObject(tDC,old);
   	DeleteDC(tDC);
   }
   else
   {
     GetObject(bm.getHandle(),sizeof(BITMAP),&bmap);

     HBITMAP monoBM;
     HBITMAP oldmonoBM;
     HDC monoDC;

     // create a mask of image
     monoDC=CreateCompatibleDC(NULL);
     monoBM=CreateBitmap(bmap.bmWidth,bmap.bmHeight, 1, 1, NULL);
     oldmonoBM=(HBITMAP)SelectObject(monoDC,(HANDLE)monoBM);

     // select the actual bm into mem
     tDC=CreateCompatibleDC(_hdc);
	  old=(HBITMAP)SelectObject(tDC,(HANDLE)bm.getHandle());



#if WINVER < 5 // works in nt/2000    // ONLY WORKS WHERE TRANSPARENT = WHITE
                                       // could perhaps swap for black
     //Make sure conversion of monochrome to color stays B&W
     SetTextColor(tDC, 0L);  //0's in mono -> 0
     // set color that is the one to consider as transparent
     SetBkColor(tDC,RGB(0xff,0xff,0xff)); //1's in mono -> 1

  	  BitBlt(monoDC,0,0,bmap.bmWidth,bmap.bmHeight,tDC,0,0,NOTSRCCOPY);
     SetTextColor(monoDC,0);  //0's in mono -> 0
     // set color that is the one to consider as transparent
     SetBkColor(monoDC,col); //1's in mono -> 1

     // we now have a mask where white is where the color is and black is hwere the
     // transparent should be
     // but in a bitmap white is 0 - but this used later !!!

     // copy it over to destination
    // where it is a 0 (white), do a srccopy, where it is black do a and( combine the 2 bitmaps )
    // but because the color is 1 on the src one, it will keep the colours the same
    MaskBlt(_hdc,x,y,bmap.bmWidth,bmap.bmHeight,tDC,0,0,monoBM,0,0,MAKEROP4(SRCCOPY,SRCAND));
#else
     // select the actual bm into mem

    HBITMAP imageBM;

    imageBM = CreateCompatibleBitmap(_hdc,bmap.bmWidth,bmap.bmHeight);
    old=(HBITMAP)SelectObject(tDC,imageBM);
    // select bm in here for a moment
    SelectObject(monoDC,bm.getHandle());
    BitBlt(tDC,0,0,bmap.bmWidth,bmap.bmHeight,monoDC,0,0,SRCCOPY);

    // copy the bitmap to the mono bitmap
    SelectObject(monoDC,monoBM);
     // set color that is the one to consider as transparent
    COLORREF tcolor = SetBkColor(tDC,col); //1's in mono -> 1
    BitBlt(monoDC,0,0,bmap.bmWidth,bmap.bmHeight,tDC,0,0,SRCCOPY);
    SetBkColor(tDC,tcolor);

    // need yet another bitmap
    HBITMAP notmonoBM;
    HDC notmonoDC;
    HBITMAP oldnotmonoBM;

    notmonoDC=CreateCompatibleDC(NULL);
    notmonoBM=CreateBitmap(bmap.bmWidth,bmap.bmHeight, 1, 1, NULL);
    oldnotmonoBM=(HBITMAP)SelectObject(notmonoDC,notmonoBM);

    // copy inverse of the mask
    BitBlt(notmonoDC,0,0,bmap.bmWidth,bmap.bmHeight,monoDC,0,0,NOTSRCCOPY);

    // the destination
    HBITMAP buildBM;
    HDC buildDC;
    HBITMAP oldbuildBM;

    buildDC = CreateCompatibleDC(_hdc);
    buildBM = CreateCompatibleBitmap(_hdc,bmap.bmWidth,bmap.bmHeight);
    oldbuildBM=(HBITMAP)SelectObject(buildDC,buildBM);

    // copy the place we are going to be blitting to, to the work area
    BitBlt(buildDC,0,0,bmap.bmWidth,bmap.bmHeight,_hdc,x,y,SRCCOPY);

    // mask out places where bitmap will be
    BitBlt(buildDC,0,0,bmap.bmWidth,bmap.bmHeight,monoDC,0,0,SRCAND);

    // mask out transparent pixels on bitmap
    BitBlt(tDC,0,0,bmap.bmWidth,bmap.bmHeight,notmonoDC,0,0,SRCAND);

    // xor the bitmap with background on dest
    BitBlt(buildDC,0,0,bmap.bmWidth,bmap.bmHeight,tDC,0,0,SRCPAINT);

    // copt bitmap to the screen
    BitBlt(_hdc,x,y,bmap.bmWidth,bmap.bmHeight,buildDC,0,0,SRCCOPY);


     SelectObject(buildDC,oldbuildBM);
     DeleteObject(buildBM);
     DeleteDC(buildDC);

     DeleteObject(imageBM);

     SelectObject(notmonoDC,oldnotmonoBM);
     DeleteObject(notmonoBM);
     DeleteDC(notmonoDC);

#endif

    // free up what we allocated
     SelectObject(monoDC,oldmonoBM);
     DeleteObject(monoBM);
     DeleteDC(monoDC);

     SelectObject(tDC,old);
     DeleteDC(tDC);

   }
}
void EZGfx::drawStretchedBitmap(int x,int y,int sizex,int sizey,const EZBitmap &bm,COLORREF col)
{
	HDC tDC;
	HBITMAP old;
	BITMAP bmap;

   if(col==-1)
   {
    	tDC=CreateCompatibleDC(_hdc);
	   old=(HBITMAP)SelectObject(tDC,bm.getHandle());
   	GetObject(bm.getHandle(),sizeof(BITMAP),&bmap);
   	StretchBlt(_hdc,x,y,sizex,sizey,tDC,0,0,bmap.bmWidth,bmap.bmHeight,SRCCOPY);
   	SelectObject(tDC,old);
   	DeleteDC(tDC);
   }
   else
   {
     GetObject(bm.getHandle(),sizeof(BITMAP),&bmap);

     HBITMAP monoBM;
     HBITMAP oldmonoBM;
     HDC monoDC;

     // create a mask of image
     monoDC=CreateCompatibleDC(NULL);
     monoBM=CreateBitmap(bmap.bmWidth,bmap.bmHeight, 1, 1, NULL);
     oldmonoBM=(HBITMAP)SelectObject(monoDC,monoBM);

     // select the actual bm into mem
     tDC=CreateCompatibleDC(_hdc);
	  old=(HBITMAP)SelectObject(tDC,bm.getHandle());

    HBITMAP imageBM;

    imageBM = CreateCompatibleBitmap(_hdc,bmap.bmWidth,bmap.bmHeight);
    old=(HBITMAP)SelectObject(tDC,imageBM);
    // select bm in here for a moment
    SelectObject(monoDC,bm.getHandle());
    BitBlt(tDC,0,0,bmap.bmWidth,bmap.bmHeight,monoDC,0,0,SRCCOPY);

    // copy the bitmap to the mono bitmap
    SelectObject(monoDC,monoBM);
     // set color that is the one to consider as transparent
    COLORREF tcolor = SetBkColor(tDC,col); //1's in mono -> 1
    BitBlt(monoDC,0,0,bmap.bmWidth,bmap.bmHeight,tDC,0,0,SRCCOPY);
    SetBkColor(tDC,tcolor);

    // need yet another bitmap
    HBITMAP notmonoBM;
    HDC notmonoDC;
    HBITMAP oldnotmonoBM;

    notmonoDC=CreateCompatibleDC(NULL);
    notmonoBM=CreateBitmap(bmap.bmWidth,bmap.bmHeight, 1, 1, NULL);
    oldnotmonoBM=(HBITMAP)SelectObject(notmonoDC,notmonoBM);

    // copy inverse of the mask
    BitBlt(notmonoDC,0,0,bmap.bmWidth,bmap.bmHeight,monoDC,0,0,NOTSRCCOPY);

    // the destination
    HBITMAP buildBM;
    HDC buildDC;
    HBITMAP oldbuildBM;

    buildDC = CreateCompatibleDC(_hdc);
    buildBM = CreateCompatibleBitmap(_hdc,bmap.bmWidth,bmap.bmHeight);
    oldbuildBM=(HBITMAP)SelectObject(buildDC,buildBM);

    // copy the place we are going to be blitting to, to the work area
    BitBlt(buildDC,0,0,bmap.bmWidth,bmap.bmHeight,_hdc,x,y,SRCCOPY);

    // mask out places where bitmap will be
    BitBlt(buildDC,0,0,bmap.bmWidth,bmap.bmHeight,monoDC,0,0,SRCAND);

    // mask out transparent pixels on bitmap
    BitBlt(tDC,0,0,bmap.bmWidth,bmap.bmHeight,notmonoDC,0,0,SRCAND);

    // xor the bitmap with background on dest
    BitBlt(buildDC,0,0,bmap.bmWidth,bmap.bmHeight,tDC,0,0,SRCPAINT);

    // copt bitmap to the screen
    StretchBlt(_hdc,x,y,sizex,sizey,buildDC,0,0,bmap.bmWidth,bmap.bmHeight,SRCCOPY);


     SelectObject(buildDC,oldbuildBM);
     DeleteObject(buildBM);
     DeleteDC(buildDC);

     DeleteObject(imageBM);

     SelectObject(notmonoDC,oldnotmonoBM);
     DeleteObject(notmonoBM);
     DeleteDC(notmonoDC);

    // free up what we allocated
     SelectObject(monoDC,oldmonoBM);
     DeleteObject(monoBM);
     DeleteDC(monoDC);

     SelectObject(tDC,old);
     DeleteDC(tDC);

   }

}


bool EZGfx::setROP2(int mode)
{
  return SetROP2(_hdc, mode) != 0;
}

// return the rect from the 
// paint struct if we are painting
// otherwise return an empty rect
EZRect EZGfx::getPaintRect()
{
  if(_paint) return EZRect(_ps.rcPaint);
  else return EZRect();
}

EZSize EZGfx::getTextExtent(const char *string, int cnt)
{
  SIZE size;

  if(!string) return EZSize();

  if(cnt < 0) cnt = strlen(string);

  GetTextExtentPoint32(_hdc,string,cnt, &size);

  return size;
}

int EZGfx::getBkMode()
{
  return GetBkMode(_hdc);
}

int EZGfx::getROP2()
{
  return GetROP2(_hdc);
}
