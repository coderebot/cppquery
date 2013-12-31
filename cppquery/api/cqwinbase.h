#ifndef CQ_WINBASE_H
#define CQ_WINBASE_H

#include "cqprototype.h"
#include <windows.h>

namespace cppquery {

class WindowPeer : public Prototype
{
protected:
    WNDPROC oldProc_;
    WindowPeer(WindowPeer& p) : Prototype(&p), oldProc_(p.oldProc_){}
public:
    WindowPeer():oldProc_(NULL){}
    
    virtual BOOL wndProc(HWND hwnd, UINT message, WPARAM, LPARAM, LRESULT& pret) = 0;

    static WindowPeer * FromHandle(HWND hwnd);
    static WindowPeer * AutoGet(HWND hwnd);
    static WindowPeer * AutoGetWriteable(HWND hwnd);

    static WindowPeer* Attach(HWND hwnd, WindowPeer* peer);
    static void Dettach(HWND hwnd);

private:
    static LRESULT WINAPI _wnd_proc(HWND hwnd, UINT, WPARAM,LPARAM);
};


void AddWindowPeer(LPCWSTR str, WindowPeer* peer);
void AddWindowPeer(int id, WindowPeer* peer);

BOOL ReflectMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

}


#endif
