#include <stdio.h>
#include "cppquery.h"

namespace cppquery{


static INT_PTR CALLBACK _my_dlg_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == WM_INITDIALOG){
        Window window(hDlg);
        window.setMessageHandle((WindowFrontPeer::MessageHandle*)lParam);
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}

LRESULT DoDialogModel(HINSTANCE hInst, HWND hParent, UINT res, WindowFrontPeer::MessageHandle* handles)
{
    return DialogBoxParam(hInst, MAKEINTRESOURCE(res), hParent, _my_dlg_proc, (LPARAM)handles);
}


}

