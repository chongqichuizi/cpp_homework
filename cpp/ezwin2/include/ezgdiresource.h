
/***********************************************************
 * EZWIN2
 *
 * Name:      ezgdiresource.h
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

#ifndef ezgdi_resource_h
#define ezgdi_resource_h

#if defined(_MSC_VER)
  #pragma warning(disable: 4251)
  #pragma warning(disable: 4786)
#endif

#include <ezwin.h>
#include <map>

class DLL_EXP EZGDIResource
{
  typedef std::map<HANDLE, unsigned int,std::less<HANDLE> > HandleList;

  static HandleList handles;
protected:
  EZGDIResource();
  virtual ~EZGDIResource();

  static bool add(HANDLE h);
  static bool rem(HANDLE h);
public:
  static void dump();
};

#endif // ezgdi_resource_h