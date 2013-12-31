#ifndef CPPQUERY_H
#define CPPQUERY_H

#include <windows.h>

#include "cqwin.h"
#include "cqfunction.h"
#include "cqbind.h"
#include "cqdatacontrol.h"

#define MK_FUNC make_function
#define FUNC func_ptr
#define METHOD method_ptr
#define BIND bind
namespace cppquery {
class Window
{
protected:
    HWND hwnd_;
    WindowFrontPeer* getFrontPeer() {
        return WindowFrontPeer::GetFrontPeer(hwnd_);
    }
    WindowFrontPeer* getWritePeer() {
        return WindowFrontPeer::GetWritePeer(hwnd_);
    }
public:
    Window():hwnd_(0){}
    Window(HWND hwnd): hwnd_(hwnd){}
    Window(const Window& w) : hwnd_(w.hwnd_){}

    HWND hwnd() const { return hwnd_; }

    HWND get(int id);

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

    void endMode(LONG value);

    int doModel();

    void setMessageHandle(WindowFrontPeer::MessageHandle* handles){
        getWritePeer()->setMessageHandles(handles);
    }

    template<class F>
    Window& onCommand(int id, F const& f){
        getWritePeer()->onCommand(id, f);
        return *this;
    }
    template<class F>
    Window& onCommand(int id_begin, int id_end, F const& f){
        getWritePeer()->onCommand(id_begin, id_end, f);
        return *this;
    }
    
    template<class F>
    Window& onPaint(F const& f){
        getWritePeer()->onPaint(f);
        return *this;
    }

    template<class F>
    Window& onDestroy(F const& f){
        getWritePeer()->onDestroy(f);
        return *this;
    }

    
    IntNumber intNumber(int id){
        return IntNumber(get(id));
    }
    
};

class Dialog : public Window {
public:
    Dialog(HINSTANCE hInst, UINT resId, HWND hParent);
    ~Dialog();

};



//////////////////////////////////////////////////////////////////////////
//DoDialogModel
LRESULT DoDialogModel(HINSTANCE hInst, HWND hParent, UINT res, WindowFrontPeer::MessageHandle* handles);

}
#endif
