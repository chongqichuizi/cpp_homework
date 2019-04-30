
/***********************************************************
 * Name:      ezwin.h
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

#ifndef EZWIN_H
#define EZWIN_H

#if !defined(DLL_EXP)
 #if !defined(BUILD_DLL)
  #define DLL_EXP __declspec(dllimport)
 #else
  #define DLL_EXP __declspec(dllexport)
 # endif
#endif 

#define WINDOWS_LEAN_AND_MEAN

#include <windows.h>

extern "C" 
{
	extern DWORD EZWIN_Version();
}

#include <assert.h>

#endif // EZWIN_H