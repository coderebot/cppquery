#include <stdio.h>
#include "cqwinbase.h"

namespace cppquery{

WinBackend* WinBackend::FromHandle(HWND hwnd)
{
    if(!IsWindow(hwnd))
        return NULL;

    LONG l = GetWindowLong(hwnd, GWL_USERDATA);
    return reinterpret_cast<WinBackend*>(l);
}

WinBackend* WinBackend::Get(HWND hwnd)
{
    if(!IsWindow(hwnd))
        return NULL;

    LONG l = GetWindowLong(hwnd, GWL_USERDATA);
    if(l == 0)
    {
        //create one
        WinBackend *back = new WinBackend(hwnd);
        SetWindowLong(hwnd, GWL_USERDATA, (LONG)back);
        back->oldProc = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)WinBackend::_wnd_proc);
        return back;
    }
    return reinterpret_cast<WinBackend*>(l);
}

LRESULT WinBackend::_wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WinBackend* back = WinBackend::FromHandle(hwnd);
    if(back){
        LRESULT r = 0;
        if(back->frontPeer.ptr() && back->frontPeer->wndProc(hwnd, message, wParam, lParam, r))
            return r;
        if(back->oldProc)
            return back->oldProc(hwnd, message, wParam, lParam);
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
}