#include <eztaskbaricon.h>
#include <ezwindow.h>

int EZTaskbarIcon::uid_counter=0;

EZTaskbarIcon::EZTaskbarIcon(EZWindow *parent,DWORD resource,LPSTR tip,UINT messageID)
  : EZIcon(resource)
{
    nd.cbSize = sizeof(NOTIFYICONDATA);
    nd.hWnd = parent->getHandle();
    nd.uID = uid_counter++;

    nd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nd.uCallbackMessage = messageID;
    nd.hIcon = getHandle();

    if (tip)
        lstrcpyn(nd.szTip,tip, sizeof(nd.szTip));
    else
        nd.szTip[0] = '\0';

    Shell_NotifyIcon(NIM_ADD, &nd);
}
EZTaskbarIcon::~EZTaskbarIcon()
{
  Shell_NotifyIcon(NIM_DELETE, &nd);
}
