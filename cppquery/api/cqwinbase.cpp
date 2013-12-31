#include <stdio.h>
#include "cqwinbase.h"

#include <string>
#include <map>

namespace cppquery{

WindowPeer* WindowPeer::FromHandle(HWND hwnd)
{
    if(!IsWindow(hwnd))
        return NULL;

    LONG l = GetWindowLong(hwnd, GWL_USERDATA);
    return reinterpret_cast<WindowPeer*>(l);
}


LRESULT WindowPeer::_wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowPeer* peer = WindowPeer::FromHandle(hwnd);

    ReflectMessage(hwnd, message, wParam, lParam);

    if(peer){
        LRESULT r = 0;
        if(peer->wndProc(hwnd, message, wParam, lParam, r) && message != WM_DESTROY)
            return r;
        WNDPROC proc = peer->oldProc_;
        if(message == WM_DESTROY){
            Dettach(hwnd);
            peer->release();
        }
        if(proc && proc != _wnd_proc)
            return proc(hwnd, message, wParam, lParam);
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

WindowPeer* WindowPeer::Attach(HWND hwnd, WindowPeer* peer)
{
    if(!IsWindow(hwnd) || peer == NULL)
        return peer;

    WindowPeer* oldpeer = (WindowPeer*)GetWindowLong(hwnd, GWL_USERDATA);
    if(oldpeer) {
        oldpeer->release();
        SetWindowLong(hwnd, GWL_USERDATA, (LONG)peer);
        return peer;
    }

    WNDPROC oldProc = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)_wnd_proc);
    if(oldProc != _wnd_proc)
    {
        if(peer->oldProc_ == NULL)
            peer->oldProc_ = oldProc;
        else if(oldProc != peer->oldProc_) {
            peer = (WindowPeer*)peer->clone();
            peer->oldProc_ = oldProc;
        }
    }
    SetWindowLong(hwnd, GWL_USERDATA, (LONG)peer);
    return peer;
}

void WindowPeer::Dettach(HWND hwnd)
{
    WindowPeer* peer = FromHandle(hwnd);
    if(peer)
    {
        SetWindowLong(hwnd, GWL_USERDATA, 0);
        SetWindowLong(hwnd, GWL_WNDPROC, (LONG)(peer->oldProc_));
    }
}

static WindowPeer* FindWindowPeer(HWND hwnd);

WindowPeer* WindowPeer::AutoGet(HWND hwnd)
{
    WindowPeer* peer = FromHandle(hwnd);
    if(!peer){
        peer = FindWindowPeer(hwnd);
        if(!peer) return NULL;
        return Attach(hwnd, peer);
    }
    return peer;
}

WindowPeer* WindowPeer::AutoGetWriteable(HWND hwnd)
{
    WindowPeer * peer = AutoGet(hwnd);
    if(peer) {
        if(peer->refcount() > 1) {
            return Attach(hwnd, (WindowPeer*)peer->clone());
        }
    }
    return peer;
}

///////////////////////////////////////////////////////////
//WindowPeer create table

class WindowPeerManager
{
    RefPtr<WindowPeer> defWindowPeer_;

    typedef std::map<std::wstring, RefPtr<WindowPeer> > ClassWindowPeerMap;
    typedef std::map<int, RefPtr<WindowPeer> > IdWindowPeerMap;

    ClassWindowPeerMap *classPeers_;
    IdWindowPeerMap    *idPeers_;

    ClassWindowPeerMap& classPeers() {
        if(classPeers_ == NULL)
            classPeers_ = new ClassWindowPeerMap();
        return *classPeers_;
    }

    IdWindowPeerMap& idPeers(){
        if(idPeers_ == NULL)
            idPeers_ = new IdWindowPeerMap();
        return *idPeers_;
    }

    template <class TId>
    WindowPeer* find(std::map<TId, RefPtr<WindowPeer> >* mps, TId const& id){
        if(mps == NULL)
            return NULL;
        std::map<TId, RefPtr<WindowPeer> >::iterator it = mps->find(id);
        if(it != mps->end())
            return it->second.ptr();
        return NULL;
    }

    static WindowPeerManager _windowPeerManager;
public:
    WindowPeerManager(){}
    ~WindowPeerManager(){
        delete idPeers_;
        delete classPeers_;
    }

    void setDefaultWindowPeer(WindowPeer* peer){
        defWindowPeer_ = peer;
    }

    void addPeer(LPCWSTR klass, WindowPeer* peer) {
        if(!klass || !peer)
            return ;
        classPeers()[klass] = peer;
    }
    void addPeer(int id, WindowPeer* peer) {
        if(!peer)
            return ;
        idPeers()[id] = peer;
    }

    WindowPeer* findPeer(HWND hwnd) {
        int id = (int)GetWindowLong(hwnd, GWL_ID);
        WindowPeer *peer = NULL;
        if(id != 0)
            peer = find<int>(idPeers_, id);
        if(peer) return peer;
        TCHAR szClassName[256];
        GetClassName(hwnd, szClassName, 256);
        peer = find<std::wstring>(classPeers_, szClassName);
        if(peer) return peer;

        return defWindowPeer_.ptr();
    }

    static WindowPeerManager& GetInstance() { return _windowPeerManager; }
};

WindowPeerManager WindowPeerManager::_windowPeerManager;

static WindowPeer* FindWindowPeer(HWND hwnd)
{
    return WindowPeerManager::GetInstance().findPeer(hwnd);
}

void AddWindowPeer(LPCWSTR str, WindowPeer* peer)
{
    WindowPeerManager::GetInstance().addPeer(str, peer);
}

void AddWindowPeer(int id, WindowPeer* peer)
{
    WindowPeerManager::GetInstance().addPeer(id, peer);
}

BOOL ReflectMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == WM_NOTIFY && lParam)
    {
        NMHDR *nmhdr = (NMHDR*)lParam;
        if(hwnd ==  nmhdr->hwndFrom) return FALSE;
        SendMessage(nmhdr->hwndFrom, message, wParam, lParam);
    }
    else if(message == WM_COMMAND && HIWORD(wParam) != 0 && IsWindow((HWND)lParam) && hwnd != (HWND)lParam)
    {
        NMHDR hdr;
        hdr.hwndFrom = (HWND)lParam;
        hdr.code = HIWORD(wParam);
        hdr.idFrom = LOWORD(wParam);
        SendMessage(hdr.hwndFrom, WM_NOTIFY, 0, (LPARAM)&hdr);
    }
    else {
        return  FALSE;
    }
    return TRUE;
}

}