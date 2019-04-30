
/***********************************************************
 * EZWIN2
 *
 * Name:      ezgfx.h
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

#ifndef ezgfx_h
#define ezgfx_h

#include <ezwin.h>

#include <ezsize.h>
#include <ezbrush.h>
#include <ezpen.h>
#include <ezbitmap.h>
#include <ezfont.h>

class EZWindow;

// EZGfx isnt a gdi resource itself as it isnt created here -
// it is only gotten from the window

class DLL_EXP EZGfx
{
  PAINTSTRUCT _ps;
  HDC _hdc;
  EZWindow *_win;
  bool _paint;

  EZPen _oldpen;
  EZBrush _oldbrush;
  EZFont _oldfont;

  EZPen _currpen;
  EZBrush _currbrush;
  EZFont _currfont;
public:
	int getROP2();

  EZSize getTextExtent(const char *string,  int cnt=-1);

  EZGfx(EZWindow *w,bool paint=true);
  virtual ~EZGfx();

  EZRect getPaintRect();

  bool setROP2(int mode);

  int getDeviceCaps(int index);
  bool getTextMetrics(LPTEXTMETRIC lpm);

  void setBkMode(int mode);
  int getBkMode();

  EZPen setBkColour(const EZPen &p);
  EZPen setTextColour(const EZPen &p);
  EZPen getBkColour();
  EZPen getTextColour();

  EZFont setFont(const EZFont &f);
  EZBrush setBrush(const EZBrush &b);
  EZPen setPen(const EZPen &pen);

  EZFont getFont();
  EZPen getPen();
  EZBrush getBrush();

  inline HDC getHandle() { return _hdc; }

  EZPoint getCurrentPosition();

  void floodFill(int x, int y, const EZPen &p);

  void drawArc(const EZRect &rect, const EZPoint &start, const EZPoint &end);
  void drawArc(int left, int top, int right, int bottom, int start_x, int start_y, int end_x, int end_y);

  void drawCircle(const EZRect &rect);
  void drawCircle(int left, int top, int right, int bottom);

  void moveTo(int x,int y);
  void lineTo(int x,int y);

  void drawLine(int x1,int y1,int x2,int y2);
  void draw3DLine(int x1,int y1,int x2,int y2);

  void setPixel(int x,int y, const EZPen &p);
  EZPen getPixel(int x,int y);

  void fillRect(const EZRect &r,const EZBrush &cr);
  void fillRect(int x1, int y1, int x2, int y2,const EZBrush &cr);

  void drawRect(const EZRect &r);
  void drawRect(int x1, int y1, int x2, int y2);
  void draw3DRect(const EZRect &r, bool inverted=false);

  void patBlt(EZRect &r,int mode);

  void drawText(const char *str,const EZRect &r,UINT flags=DT_LEFT, int len=-1);
  void drawText(const char *str,const EZPoint &pt,UINT flags=DT_LEFT, int len=-1);

  EZRect calcTextRect(const char *str, const EZPoint &pt, UINT flags=DT_LEFT, int len=-1); 

  void drawBitmap(int x,int y,const EZBitmap &bm,COLORREF col=-1);
  void drawStretchedBitmap(int x,int y,int sizex,int sizey,const EZBitmap &bm,COLORREF col=-1);

  void bitBlit(const EZRect &destrect,const EZGfx &gfx,int fromx,int fromy,DWORD oper=SRCCOPY);

private:
  // no copy allowed
  EZGfx(const EZGfx &) { }
  EZGfx & operator=(const EZGfx &) { return *this; }
};

#endif // ezgfx_h