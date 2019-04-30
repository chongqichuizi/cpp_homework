
/***********************************************************
 * Name:      ezgdiresource.cpp
 * version:   0.1
 * date:      6 March 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#include <ezgdiresource.h>

#include <assert.h>

#ifdef DEBUG_EZGDI
  #include <fstream.h> // NOTE: problems under vc - need to make <fstream>

  ofstream out_file("gdiresources.txt");
#endif

#if defined(_MSC_VER)
  #pragma warning(push)
  #pragma warning(disable: 4251)
  #pragma warning(disable: 4786)
#endif

EZGDIResource::HandleList EZGDIResource::handles;


EZGDIResource::EZGDIResource()
{
}
EZGDIResource::~EZGDIResource()
{
}
bool EZGDIResource::add(HANDLE hand)
{
  int cnt;

  if(hand)
  {
     cnt = handles[hand];
	 
	 //out_file << "Add HANDLE: " << hand << " count: " << cnt << endl;

	 handles[hand] = cnt+1;

  }

  return true;
}
bool EZGDIResource::rem(HANDLE hand)
{
  int cnt;

  if(hand)
  {
     cnt = handles[hand];
	 
	 //out_file << "Rem HANDLE: " << hand << " count: " << cnt << endl;

	 if(cnt == 1)
	 {
		 DeleteObject(hand); // noone else is using us
#ifdef DEBUG_EZGDI
		 out_file << "Handle -> Free\n";
#endif // DEBUG_EZGDI

	 }
#ifndef DEBUG_EZGDI
     assert(! (cnt<1) /* trying to free 0 ref GDI object */);
#else
	 if(cnt<1)
	   out_file << "Error - trying to free GDI Resource that is already free.\n";
#endif // DEBUG_EZGDI

	 if(cnt>0)
	 {
        handles[hand] = cnt-1;
	 }
  }
  return false;
}

void EZGDIResource::dump()
{
#ifdef DEBUG_EZGDI

  HandleList::const_iterator it;
  UINT t;
  int cnt;

  out_file << "Allocated GDI resources\n";
  out_file << "-----------------------\n";

  for(it = handles.begin(); it != handles.end(); ++it)
  {
      cnt = (*it).second;

	  if(cnt != 0)
	  {
        out_file << (*it).first << ": ";

	    t = GetObjectType((*it).first);

		switch(t)
		{
		case OBJ_BITMAP:
			out_file << "Bitmap";
			break;
		case OBJ_BRUSH:
			out_file << "Brush";
			break;
		case OBJ_FONT:
			out_file << "Font";
			break;
		case OBJ_PAL:
			out_file << "Pallete";
			break;
		case OBJ_PEN:
			out_file << "Pen";
			break;
		case OBJ_DC:
			out_file << "DC";
			break;
		case OBJ_MEMDC:
			out_file << "MemDC";
			break;
		default:
			out_file << "Unknown";
		}
		out_file << " RefCount: " << cnt << endl;
	  }
  }
#endif // DEBUG_EZGDI

  return;
}

#if defined(_MSC_VER)
  #pragma warning(pop)
#endif