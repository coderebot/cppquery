#include <stdio.h>
#include "api/cppquery.h"
#include <tchar.h>
#include "resource.h"

int gWidth = 300;
int gHeight = 400;

void demo_dialog_get_int_values()
{
    MessageBox(0, _T("Test Get Int Values"), _T("Get Int Value"), 0);

    /*Dialog dialog(hInst, ID_DIALOG_GETINTVALUES);
    dialog.number(IDC_EDIT_WIDTH).bind(&gWidth);
    dialog.number(IDC_EDIT_HEIGHT).bind(&gHeight);

    TCHAR szText[100];
    if(dialog.doMode())
    {
        _tsprintf(szText, _T("Get New Width=%d, Height=%d"), gWidth, gHeight);
    }
    else
    {
        _tsprintf(szText, _T("Error!"));
    }
    MessageBox(0, szText, _T("Result"), 0);*/
}
