#ifndef CPPQUERY_H
#define CPPQUERY_H

#include "cqwin.h"
#include "cqfunction.h"

#define MK_FUNC make_function
#define FUNC func_ptr
#define METHOD method_ptr

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
