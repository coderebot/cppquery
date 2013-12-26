#ifndef CQ_WIN_H
#define CQ_WIN_H

#include "cqwinbase.h"
#include <map>

namespace cppquery
{

////////////////////////////
//定义包装函数
template<class R>
struct message_callback0{ virtual R call() const =0;};
template<class R, class A>
struct message_callback1{ virtual R call(A const&) const = 0;};
template<class R, class A, class B>
struct message_callback2{ virtual R call(A const&, B const&) const = 0;};
template<class R, class A, class B, class C>
struct message_callback3{ virtual R call(A const&, B const&, C const&) const = 0;};
template<class R, class A, class B, class C, class D>
struct message_callback4{ virtual R call(A const&, B const&, C const&, D const&) const = 0;};
template<class R, class A, class B, class C, class D, class E>
struct message_callback5{ virtual R call(A const&, B const&, C const&, D const&, E const&) const = 0;};
template<class R, class A, class B, class C, class D, class E, class F>
struct message_callback6{ virtual R call(A const&, B const&, C const&, D const&, E const&, F const&) const = 0;};

template<class F, class R>
struct message_callback0_impl : public message_callback0<R> {
    F f_;
    message_callback0_impl(F const& f) : f_(f){}
    message_callback0_impl(const message_callback0_impl& i):f_(i.f_){}
    R call() const{ return (R)(f_()); }
};
template<class F, class R, class A>
struct message_callback1_impl : public message_callback1<R,A>  {
    F f_;
    message_callback1_impl(F const& f) : f_(f){}
    message_callback1_impl(const message_callback1_impl& i):f_(i.f_){}
    R call(A const& a) const{ return (R)(f_(a)); }
};
template<class F, class R, class A, class B>
struct message_callback2_impl : public message_callback2<R,A,B>  {
    F f_;
    message_callback2_impl(F const& f) : f_(f){}
    message_callback2_impl(const message_callback2_impl& i):f_(i.f_){}
    R call(A const& a, B const& b) const{ return (R)(f_(a, b)); }
};
template<class F, class R, class A, class B, class C>
struct message_callback3_impl : public message_callback3<R,A,B,C>  {
    F f_;
    message_callback3_impl(F const& f) : f_(f){}
    message_callback3_impl(const message_callback3_impl& i):f_(i.f_){}
    R call(A const& a, B const& b, C const& c) const{ return (R)(f_(a, b, c)); }
};
template<class F, class R, class A, class B, class C, class D>
struct message_callback4_impl : public message_callback4<R,A,B,C,D> {
    F f_;
    message_callback4_impl(F const& f) : f_(f){}
    message_callback4_impl(const message_callback4_impl& i):f_(i.f_){}
    R call(A const& a, B const& b, C const& c, D const& d) const{ return (R)(f_(a, b, c, d)); }
};
template<class F, class R, class A, class B, class C, class D, class E>
struct message_callback5_impl : public message_callback5<R,A,B,C,D,E> {
    F f_;
    message_callback5_impl(F const& f) : f_(f){}
    message_callback5_impl(const message_callback5_impl& i):f_(i.f_){}
    R call(A const& a, B const& b, C const& c, D const& d, E const& e) const{ return (R)(f_(a, b, c, d, e)); }
};
template<class Func, class R, class A, class B, class C, class D, class E, class F>
struct message_callback6_impl : public message_callback6<R,A,B,C,D,E,F> {
    Func f_;
    message_callback6_impl(Func const& f) : f_(f){}
    message_callback6_impl(const message_callback6_impl& i):f_(i.f_){}
    R call(A const& a, B const& b, C const& c, D const& d, E const& e, F const& f) const{ return (R)(f_(a, b, c, d, e, f)); }
};


class WindowFrontPeer : public FrontPeer
{
public:
    //define the message handle
    struct message_handle {
        virtual LRESULT call(HWND hwnd, UINT, WPARAM, LPARAM) = 0;
        virtual ~message_handle(){}
    };

    typedef message_handle* MessageHandle;

protected:
    WindowFrontPeer(WindowFrontPeer* p) : FrontPeer(p), entries_(p ? p->entries_: NULL){

    }
    MessageHandle * entries_;

    template<class MsgCB>
    struct simple_message_handle : public message_handle{
        MsgCB* cb_;
        simple_message_handle():cb_(NULL){ }
        simple_message_handle(MsgCB* cb) : cb_(cb){}
        ~simple_message_handle(){ if(cb_) delete cb_;}

        void set(MsgCB* cb) {
            if(cb_)
                delete cb_;
            cb_ = cb;
        }
    };

    typedef message_callback1<void, HWND>CBOnVoid;
    struct on_void_handle : public simple_message_handle<CBOnVoid>{
        on_void_handle() { }
        on_void_handle(CBOnVoid *onVoid): simple_message_handle<CBOnVoid>(onVoid){};
        LRESULT call(HWND hwnd, UINT, WPARAM, LPARAM){
            if(cb_)
                cb_->call(hwnd);
            return 0;
        }
    };

    typedef message_callback2<void, HWND, HDC> CBOnPaint;
    struct on_paint_handle : public simple_message_handle<CBOnPaint> {
        on_paint_handle() {}
        on_paint_handle(CBOnPaint* onPaint) : simple_message_handle<CBOnPaint>(onPaint){}
        LRESULT call(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd,&ps);
            if(cb_)
                cb_->call(hwnd, hdc);
            EndPaint(hwnd, &ps);
        }
    };

    typedef message_callback2<void, HWND, INT> CBOnCommand;
    struct command_sub_handle {
        command_sub_handle * next;
        CBOnCommand* command;
        command_sub_handle(CBOnCommand *cb): command(cb), next(NULL) {}
        virtual bool check(int id) = 0;
        virtual ~command_sub_handle(){}
    };
    struct command_sub_handle_id : public command_sub_handle{
        int id_;
        command_sub_handle_id(int id, CBOnCommand *cb): id_(id), command_sub_handle(cb){}
        bool check(int id){ return id_ == id; }
    };
    struct command_sub_handle_id_range : public command_sub_handle {
        int id_begin_, id_end_;
        command_sub_handle_id_range(int id_begin, int id_end, CBOnCommand *cb): id_begin_(id_begin), id_end_(id_end), command_sub_handle(cb){}
        bool check(int id){ return id >= id_begin_ && id <= id_end_; }
    };
    struct on_command_handle : public message_handle {
        command_sub_handle * head_;
        on_command_handle(): head_(NULL){}
        ~on_command_handle(){
            while(head_){
                command_sub_handle *h = head_;
                head_ = head_->next;
                delete h;
            }
            head_ = NULL;
        }
        LRESULT call(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
            int id = LOWORD(wParam);
            for(command_sub_handle* h = head_; h; h=h->next){
                if(h->check(id))
                    h->command->call(hwnd, id);
            }
            return 0;
        }
        void add(int id, CBOnCommand *command){
            add(new command_sub_handle_id(id, command));
        }
        void add(int id_begin, int id_end, CBOnCommand *command){
            add(new command_sub_handle_id_range(id_begin, id_end, command));
        }

        void add(command_sub_handle* h){
            h->next = head_;
            head_ = h;
        }
    };


    typedef message_callback2<void, HWND, NMHDR*> CBOnNotify;

    typedef std::map<UINT, message_handle*> MessageHandleMap;
    MessageHandleMap messageHandleMap_;

    virtual BOOL wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT& ret){
        ret = 0;

        if(entries_){
            for(int i = 0; entries_[i] && i < 200; i++)
                entries_[i]->call(hwnd, message, wParam, lParam);
        }

        MessageHandleMap::iterator it = messageHandleMap_.find(message);
        if(it == messageHandleMap_.end() || !(it->second))
            return FALSE;

        ret = it->second->call(hwnd, message, wParam, lParam);
        return TRUE;
    }

    template<class MsgHandle>
    MsgHandle* getMsgHandle(int msg){
        message_handle * & h = messageHandleMap_[msg];
        if(h == NULL)
            h = new MsgHandle();
        return (MsgHandle*)h;
    }

public:
    WindowFrontPeer() : entries_(NULL){ }

    void setMessageHandles(MessageHandle* handles){
        entries_ = handles;
    }

    WindowFrontPeer *clone() { return new WindowFrontPeer(this); }

    template<class F>
    void onPaint(F const& f){
      getMsgHandle<on_paint_handle>(WM_PAINT)->set(new message_callback2_impl<F, void, HWND, HDC>(f));
    }

    template<class F>
    void onCommand(int id, F const& f){
        getMsgHandle<on_command_handle>(WM_COMMAND)
               ->add(id, new message_callback2_impl<F, void, HWND, INT>(f));
    }
    template<class F>
    void onCommand(int id_begin, int id_end, F const& f){
        getMsgHandle<on_command_handle>(WM_COMMAND)
            ->add(id_begin,id_end, new message_callback2_impl<F, void, HWND, INT>(f));
    }
    template<class F>
    void onDestroy(F const& f){
        getMsgHandle<on_void_handle>(WM_DESTROY)
            ->set(new message_callback1_impl<F, void, HWND>(f));
    }

    //void onNotify(){
    //
    //}
protected:
    template<class BaseMsgHandle, const UINT Message>
    struct message_handle_wrapper : public BaseMsgHandle
    {
        message_handle_wrapper() {}
        LRESULT call(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
            if(Message == message)
                return BaseMsgHandle::call(hwnd, message, wParam, lParam);
            return 0;
        }
    };

    struct on_command_handle_id : public simple_message_handle<CBOnCommand> {
        int id_;
        on_command_handle_id(int id, CBOnCommand* onCommand): id_(id), simple_message_handle<CBOnCommand>(onCommand){ }
        LRESULT call(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
            if(message == WM_COMMAND && LOWORD(wParam) == id_ && cb_)
                cb_->call(hwnd, LOWORD(wParam));
            return 0;
        }
    };
    struct on_command_handle_id_range : public simple_message_handle<CBOnCommand> {
        int id_begin_, id_end_;
        on_command_handle_id_range(int id_begin, int id_end, CBOnCommand* onCommand): id_begin_(id_begin), id_end_(id_end), simple_message_handle<CBOnCommand>(onCommand){ }
        LRESULT call(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
            int id = LOWORD(wParam);
            if(message == WM_COMMAND && id >=id_begin_ && id <= id_end_ && cb_)
                cb_->call(hwnd, id);
            return 0;
        }
    };
public:
    ///static for entries
    template<class F>
    static MessageHandle Command(int id, F const& f){
        return new on_command_handle_id(id, new message_callback2_impl<F, void, HWND, INT>(f));
    }
    template<class F>
    static MessageHandle Command(int id_begin, int id_end, F const& f){
        return new on_command_handle_id_range(id_begin, id_end, new message_callback2_impl<F, void, HWND, INT>(f))
    }

    template<class F>
    static MessageHandle Destroy(F const& f){
        message_handle_wrapper<on_void_handle, WM_DESTROY> * handle 
            = new message_handle_wrapper<on_void_handle, WM_DESTROY>();
        handle->set(new message_callback1_impl<F, void, HWND>(f));
        return handle;
    }
};




}

#endif
