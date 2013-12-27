#ifndef CPPQUERY_H
#define CPPQUERY_H

#include "cqwin.h"
#include "cqfunction.h"
#include "cqbind.h"

#define MK_FUNC make_function
#define FUNC func_ptr
#define METHOD method_ptr
#define BIND bind
#include <windows.h>

namespace cppquery {
class Window
{
    HWND hwnd_;
    WindowFrontPeer* getFrontPeer() {
        WinBackend* backend = WinBackend::Get(hwnd_);
        if(!backend)
            return NULL;
        if(backend->frontPeer.ptr() == NULL)
            backend->frontPeer.set(new WindowFrontPeer());
        return (WindowFrontPeer*)(backend->frontPeer.ptr());
    }
public:
    Window(HWND hwnd): hwnd_(hwnd){}
    Window(const Window& w) : hwnd_(w.hwnd_){}

    HWND hwnd() const { return hwnd_; }

    static Window Create(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, LPCTSTR caption, DWORD style, DWORD exstyle = 0);

    Window& show(int mode) {
        ShowWindow(hwnd_, mode);
        return *this;
    }
    Window& update(){
        UpdateWindow(hwnd_);
        return *this;
    }

    Window& loadMenu(HINSTANCE hInst, LPCTSTR menures){
        SetMenu(hwnd_, LoadMenu(hInst, menures));
        return *this;
    }

    int doModel();

    void setMessageHandle(WindowFrontPeer::MessageHandle* handles){
        getFrontPeer()->setMessageHandles(handles);
    }

    template<class F>
    Window& onCommand(int id, F const& f){
        getFrontPeer()->onCommand(id, f);
        return *this;
    }
    template<class F>
    Window& onCommand(int id_begin, int id_end, F const& f){
        getFrontPeer()->onCommand(id_begin, id_end, f);
        return *this;
    }
    
    template<class F>
    Window& onPaint(F const& f){
        getFrontPeer()->onPaint(f);
        return *this;
    }

    template<class F>
    Window& onDestroy(F const& f){
        getFrontPeer()->onDestroy(f);
        return *this;
    }
    
};


//////////////////////////////////////////////////////////////////////////
//DoDialogModel
LRESULT DoDialogModel(HINSTANCE hInst, HWND hParent, UINT res, WindowFrontPeer::MessageHandle* handles);

}
#endif
