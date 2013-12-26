#ifndef CQ_WINBASE_H
#define CQ_WINBASE_H

#include "cqprototype.h"
#include <windows.h>

namespace cppquery {

class FrontPeer : public Prototype
{
protected:
    FrontPeer(FrontPeer* p) : Prototype(p){}
public:
    FrontPeer(){}
    
    virtual BOOL wndProc(HWND hwnd, UINT message, WPARAM, LPARAM, LRESULT& pret) = 0;
};

class BackPeer : public Prototype
{
protected:
    BackPeer(BackPeer* p) : Prototype(p){}
public:
    BackPeer() {}
};

struct WinBackend {
    HWND hwnd;
    WNDPROC oldProc;
    PrototypePtr<FrontPeer> frontPeer;
    PrototypePtr<BackPeer> backPeer;

    WinBackend(HWND hwnd) : hwnd(hwnd){}

    static WinBackend* FromHandle(HWND hwnd);
    static WinBackend* Get(HWND hwnd); //create if not exist;
private:
    static LRESULT WINAPI _wnd_proc(HWND hwnd, UINT, WPARAM,LPARAM);
};


}


#endif
