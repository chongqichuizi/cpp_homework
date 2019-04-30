# Microsoft Developer Studio Project File - Name="ezwin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ezwin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ezwin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ezwin.mak" CFG="ezwin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ezwin - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ezwin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ezwin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EZWIN_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EZWIN_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "ezwin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "../obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EZWIN_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "BUILD_DLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib wsock32.lib Advapi32.lib shell32.lib Comctl32.lib /nologo /dll /pdb:none /debug /machine:I386 /out:"../lib/ezwin2.dll"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "ezwin - Win32 Release"
# Name "ezwin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\ezapp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezbitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezbrush.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\EZClientWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezcolourbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezcombobox.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezconfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezcursor.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezdialog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezdragbar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezfont.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezgdiresource.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezgfx.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezicon.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezimagelist.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezimagewin.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezlayout.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezlineedit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\EZListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezlistview.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezmainwindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\EZMDIChildWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezmdimainwindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\EZMDIWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezmenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezmenubar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezmultilinebutton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\EZNumberEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\EZPane.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezpen.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezprogressbar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezscrollbar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezsimplescrollwindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezsocket.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezsplashscreen.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezstatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezstatusbar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezsystem.cpp
# End Source File
# Begin Source File

SOURCE=..\src\eztaskbaricon.cpp
# End Source File
# Begin Source File

SOURCE=..\src\eztextedit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezthread.cpp
# End Source File
# Begin Source File

SOURCE=..\src\eztimer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\eztoolbar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\eztooltip.cpp
# End Source File
# Begin Source File

SOURCE=..\src\eztreeview.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezwin.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ezwin.rc
# End Source File
# Begin Source File

SOURCE=..\src\ezwindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\ezapp.h
# End Source File
# Begin Source File

SOURCE=..\include\ezbitmap.h
# End Source File
# Begin Source File

SOURCE=..\include\ezbrush.h
# End Source File
# Begin Source File

SOURCE=..\include\ezbutton.h
# End Source File
# Begin Source File

SOURCE=..\include\EZClientWindow.h
# End Source File
# Begin Source File

SOURCE=..\include\ezcolourbutton.h
# End Source File
# Begin Source File

SOURCE=..\include\ezcombobox.h
# End Source File
# Begin Source File

SOURCE=..\include\ezconfig.h
# End Source File
# Begin Source File

SOURCE=..\include\ezcursor.h
# End Source File
# Begin Source File

SOURCE=..\include\ezdialog.h
# End Source File
# Begin Source File

SOURCE=..\include\ezdragbar.h
# End Source File
# Begin Source File

SOURCE=..\include\ezevent.h
# End Source File
# Begin Source File

SOURCE=..\include\ezfont.h
# End Source File
# Begin Source File

SOURCE=..\include\ezgdiresource.h
# End Source File
# Begin Source File

SOURCE=..\include\ezgfx.h
# End Source File
# Begin Source File

SOURCE=..\include\ezicon.h
# End Source File
# Begin Source File

SOURCE=..\include\ezimagelist.h
# End Source File
# Begin Source File

SOURCE=..\include\ezimagewin.h
# End Source File
# Begin Source File

SOURCE=..\include\ezlayout.h
# End Source File
# Begin Source File

SOURCE=..\include\ezlineedit.h
# End Source File
# Begin Source File

SOURCE=..\include\EZListBox.h
# End Source File
# Begin Source File

SOURCE=..\include\ezlistview.h
# End Source File
# Begin Source File

SOURCE=..\include\ezmainwindow.h
# End Source File
# Begin Source File

SOURCE=..\include\ezmdichildwindow.h
# End Source File
# Begin Source File

SOURCE=..\include\ezmdimainwindow.h
# End Source File
# Begin Source File

SOURCE=..\include\EZMDIWindow.h
# End Source File
# Begin Source File

SOURCE=..\include\ezmenu.h
# End Source File
# Begin Source File

SOURCE=..\include\ezmenubar.h
# End Source File
# Begin Source File

SOURCE=..\include\ezmultilinebutton.h
# End Source File
# Begin Source File

SOURCE=..\include\EZNumberEdit.h
# End Source File
# Begin Source File

SOURCE=..\include\EZPane.h
# End Source File
# Begin Source File

SOURCE=..\include\ezpen.h
# End Source File
# Begin Source File

SOURCE=..\include\ezprogressbar.h
# End Source File
# Begin Source File

SOURCE=..\src\ezresource.h
# End Source File
# Begin Source File

SOURCE=..\include\ezscrollbar.h
# End Source File
# Begin Source File

SOURCE=..\include\ezsimplescrollwindow.h
# End Source File
# Begin Source File

SOURCE=..\include\ezsize.h
# End Source File
# Begin Source File

SOURCE=..\include\ezsocket.h
# End Source File
# Begin Source File

SOURCE=..\include\ezsplashscreen.h
# End Source File
# Begin Source File

SOURCE=..\include\ezstatic.h
# End Source File
# Begin Source File

SOURCE=..\include\EZStatusbar.h
# End Source File
# Begin Source File

SOURCE=..\include\ezsystem.h
# End Source File
# Begin Source File

SOURCE=..\include\eztaskbaricon.h
# End Source File
# Begin Source File

SOURCE=..\include\eztextedit.h
# End Source File
# Begin Source File

SOURCE=..\include\ezthread.h
# End Source File
# Begin Source File

SOURCE=..\include\eztimer.h
# End Source File
# Begin Source File

SOURCE=..\include\eztoolbar.h
# End Source File
# Begin Source File

SOURCE=..\include\eztooltip.h
# End Source File
# Begin Source File

SOURCE=..\include\eztreeview.h
# End Source File
# Begin Source File

SOURCE=..\include\ezwin.h
# End Source File
# Begin Source File

SOURCE=..\include\ezwindow.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\src\example.ico
# End Source File
# End Group
# End Target
# End Project
