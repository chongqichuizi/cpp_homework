

/***********************************************************
 * EZWIN2
 *
 * Name:      ezsystem.h
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

#ifndef ezsystem_h
#define ezsystem_h

#include <ezwin.h>

#include <ezpen.h>
#include <ezbrush.h>

class DLL_EXP EZSystem
{
public:
static EZPen getSystemPen(int index);
static EZBrush getSystemBrush(int index);
};

#endif // ezsystem_h