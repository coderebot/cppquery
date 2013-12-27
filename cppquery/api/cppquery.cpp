#include <stdio.h>
#include "cppquery.h"
#include <tchar.h>

namespace cppquery{
#define CPPQUERY_WND_CLASS _T("cppquery_default_window")

static void _RegisterClass(HINSTANCE hInstance)
{
    static int _registed = 0;
    WNDCLASSEX wcex;

    if(_registed)
        return;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= DefWindowProc;
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

int Window::doModel()
{
    //TODO FIXEDME: 需要像DialogBox那样工作，目前还达不到
    MSG msg;
    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}


/////////////////////////////////////////////////////////////////////////////////////////////////

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

