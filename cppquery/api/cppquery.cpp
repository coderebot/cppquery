#include <stdio.h>
#include "cppquery.h"
#include <tchar.h>

namespace cppquery{

static LRESULT CALLBACK my_wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    ReflectMessage(hwnd, message, wParam, lParam);


    return DefWindowProc(hwnd, message, wParam, lParam);
}


static void _RegisterClass(HINSTANCE hInstance)
{
    static int _registed = 0;
    WNDCLASSEX wcex;

    if(_registed)
        return;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= my_wnd_proc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= 0;
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName	= NULL;
    wcex.lpszClassName	= CPPQUERY_WND_CLASS;
    wcex.hIconSm		= 0;

    RegisterClassEx(&wcex);

    _registed = 1;
}

Window Window::Create(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, LPCTSTR caption, DWORD style, DWORD exstyle /*= 0*/)
{
    _RegisterClass(hInst);
    HWND hWnd = CreateWindowEx(exstyle, CPPQUERY_WND_CLASS, caption, style,
        x,y, width, height, hParent, NULL, hInst, 0);
    return Window(hWnd);
}

#define WM_ENDDIALOG (WM_USER+1)
int Window::doModel()
{
    MSG msg;
    HWND hParent = ::GetParent(hwnd_);
    LONG ret = 0;
    if(IsWindow(hParent)) {
        EnableWindow(hParent, FALSE);
    }
    EnableWindow(hwnd_, TRUE);
    show(SW_SHOWDEFAULT);
    update();
    
    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if(msg.hwnd == hwnd_ && msg.message == WM_ENDDIALOG)
        {
            ret = msg.lParam;
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if(IsWindow(hParent)){
        EnableWindow(hParent, TRUE);
    }
    show(SW_HIDE);
    return ret;
}

void Window::endMode(LONG ret){
    PostMessage(hwnd_, WM_ENDDIALOG, 0, (LPARAM)ret);
}

HWND Window::get(int id)
{
    return GetDlgItem(hwnd_, id);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static INT_PTR CALLBACK _my_dlg_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

Dialog::Dialog(HINSTANCE hInst, UINT resId, HWND hParent)
{
    hwnd_ = CreateDialog(hInst, MAKEINTRESOURCE(resId), hParent, _my_dlg_proc);
    if(hwnd_ == 0) {
        int err = GetLastError();
        fprintf(stderr, "error:%d", err);
    }
}

Dialog::~Dialog()
{
    if(::IsWindow(hwnd_))
        DestroyWindow(hwnd_);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

INT_PTR CALLBACK _my_dlg_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    ReflectMessage(hDlg, message, wParam, lParam);
    if(message == WM_INITDIALOG){
        Window window(hDlg);
        if(lParam != 0)
            window.setMessageHandle((WindowFrontPeer::MessageHandle*)lParam);
        return (INT_PTR)TRUE;
    }
    else if(message == WM_COMMAND){
        int id = LOWORD(wParam);
        if(id == IDOK || id == IDCANCEL) {
            PostMessage(hDlg, WM_ENDDIALOG, 0, id == IDOK ? TRUE : FALSE);
        }
    }
    return (INT_PTR)FALSE;
}

LRESULT DoDialogModel(HINSTANCE hInst, HWND hParent, UINT res, WindowFrontPeer::MessageHandle* handles)
{
    return DialogBoxParam(hInst, MAKEINTRESOURCE(res), hParent, _my_dlg_proc, (LPARAM)handles);
}


}

