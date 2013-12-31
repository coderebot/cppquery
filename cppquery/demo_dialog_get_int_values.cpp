#include <stdio.h>
#include "api/cppquery.h"
#include <tchar.h>
#include "resource.h"
using namespace cppquery;

int gWidth = 300;
int gHeight = 400;

void demo_dialog_get_int_values(HINSTANCE hInst, HWND hParent)
{
    //MessageBox(0, _T("Test Get Int Values"), _T("Get Int Value"), 0);

    Dialog dialog(hInst, IDD_DIALOG_GETINTVALUES, hParent);
    dialog.intNumber(IDC_EDIT_WIDTH).bind(&gWidth);
    dialog.intNumber(IDC_EDIT_HEIGHT).bind(&gHeight);

    wchar_t szText[100];
    if(dialog.doModel())
    {
        wsprintf(szText, L"Get New Width=%d, Height=%d", gWidth, gHeight);
        
    }
    else
    {
        wsprintf(szText, L"Error!");
    }
    MessageBox(0, szText, L"Result", 0);
}
