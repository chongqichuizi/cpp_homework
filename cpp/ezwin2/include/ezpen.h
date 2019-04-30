

/***********************************************************
 * EZWIN2
 *
 * Name:      ezpen.h
 * version:   0.1
 * date:      3 March 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezpen_h
#define ezpen_h

#include <ezwin.h>
#include <ezgdiresource.h>

class DLL_EXP EZPen : private EZGDIResource
{
  HPEN handle; 
  COLORREF rgb;
public:
  EZPen(HPEN br);
  EZPen(const EZPen &p);
  EZPen(COLORREF cr = RGB(0,0,0), int style = PS_SOLID, int width = 1);
  ~EZPen();

  EZPen & operator=(const EZPen &p);

  inline COLORREF getRGB() const { return rgb; }

  inline HPEN getHandle() const { return handle; }

  static EZPen black();
  static EZPen white();

  /*
   COLOR_3DDKSHADOW	Dark shadow for three-dimensional display elements.
   COLOR_3DFACE,
   COLOR_BTNFACE	Face color for three-dimensional display elements.
   COLOR_3DHILIGHT, COLOR_3DHIGHLIGHT, COLOR_BTNHILIGHT, COLOR_BTNHIGHLIGHT	Highlight color for three-dimensional display elements (for edges facing the light source.)
   COLOR_3DLIGHT	Light color for three-dimensional display elements (for edges facing the light source.)
   COLOR_3DSHADOW, COLOR_BTNSHADOW	Shadow color for three-dimensional display elements (for edges facing away from the light source).
   COLOR_ACTIVEBORDER	Active window border.
   COLOR_ACTIVECAPTION	Active window caption.
   COLOR_APPWORKSPACE	Background color of multiple document interface (MDI) applications.
   COLOR_BACKGROUND, COLOR_DESKTOP	Desktop.
   COLOR_BTNTEXT	Text on push buttons.
   COLOR_CAPTIONTEXT	Text in caption, size box, and scroll bar arrow box.
   COLOR_GRAYTEXT	Grayed (disabled) text. This color is set to 0 if the current display driver does not support a solid gray color.
   COLOR_HIGHLIGHT	Item(s) selected in a control.
   COLOR_HIGHLIGHTTEXT	Text of item(s) selected in a control.
   COLOR_INACTIVEBORDER	Inactive window border.
   COLOR_INACTIVECAPTION	Inactive window caption.
   COLOR_INACTIVECAPTIONTEXT	Color of text in an inactive caption.
   COLOR_INFOBK	Background color for tooltip controls.
   COLOR_INFOTEXT	Text color for tooltip controls.
   COLOR_MENU	Menu background.
   COLOR_MENUTEXT	Text in menus.
   COLOR_SCROLLBAR	Scroll bar gray area.
   COLOR_WINDOW	Window background.
   COLOR_WINDOWFRAME	Window frame.
   COLOR_WINDOWTEXT	Text in windows.
  */
  static EZPen getSystemPen(int index);

};

#endif // ezpen_h
