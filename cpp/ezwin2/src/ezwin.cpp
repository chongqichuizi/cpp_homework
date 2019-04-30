//#include <windows.h>

#include <ezwin.h>

//#ifndef BUILD_DLL
//  #define BUILD_DLL
//#endif
/*
#include <ezapp.h>
#include <ezbrush.h>
#include <ezbutton.h>
#include <ezconfig.h>
#include <ezdialog.h>
#include <ezdragbar.h>
#include <ezgfx.h>
#include <ezicon.h>
#include <ezlayout.h>
#include <ezlineedit.h>
#include <ezlistview.h>
#include <ezmainwindow.h>
#include <ezmenu.h>
#include <ezmenubar.h>
#include <ezprogressbar.h>
#include <ezsocket.h>
#include <ezsplashscreen.h>
#include <ezstatusbar.h>
#include <eztaskbaricon.h>
#include <eztextedit.h>
#include <ezthread.h>
#include <eztimer.h>
#include <eztoolbar.h>
#include <eztreeview.h>
#include <ezevent.h>
#include <ezwindow.h>
*/
HINSTANCE dllInstance = 0;

HINSTANCE EZWIN_Instance()
{
  return dllInstance;
}

DWORD EZWIN_Version()
{
	return ( (0 << 16) |  1 ); // version 0.1
}

//int __declspec(dllimport) CRT_INIT (HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);

/*
 * visual c dll entry call 
 */
BOOL APIENTRY DllMain( HINSTANCE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{


    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			dllInstance = hModule;
		case DLL_THREAD_ATTACH:
//			CRT_INIT (hModule, ul_reason_for_call, lpReserved);
			break;
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
//			CRT_INIT (hModule, ul_reason_for_call, lpReserved);
			break;
    }
    return TRUE;
}

/*
 * borland c calls this one 
 */
BOOL WINAPI DllEntryPoint(

    HINSTANCE hinstDLL,	// handle to DLL module
    DWORD fdwReason,	// reason for calling function
    LPVOID lpvReserved 	// reserved
   )
{
  return DllMain(hinstDLL,fdwReason,lpvReserved);
}