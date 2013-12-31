#ifndef CQ_DATACONTROL_H
#define CQ_DATACONTROL_H

#include "cqbind.h"
#include "cqwinbase.h"

namespace cppquery {

template<class TBase>
class DataControlPeer : public WindowPeer {
protected:
    template<class T>
    struct data_binder {
        virtual const T& get() = 0;
        virtual void set(T const& t) = 0;
    };

    template<class T>
    struct ptr_data_binder : public data_binder<T> {
        T *ptr_;
        ptr_data_binder(T *p) : ptr_(p) { }
        ptr_data_binder(const ptr_data_binder &p) : ptr_(p.ptr_) {}
        const T& get() { return *ptr_; }
        void set(T const& t) { *ptr_ = t; }
    };

    template<class T, class TAccess>
    struct access_data_binder : public data_binder<T> {
        TAccess data_;
        access_data_binder(TAccess const& a) : data_(a) {   };
        access_data_binder(access_data_binder const& a) : data_(a.data_){}
        const T& get() { return static_cast<T>(data_); }
        void set(T const& t) { data_ = t; }
    };

    data_binder<TBase> * binder_;

    //change listener
    template<class T>
    struct listener  {
        virtual void onChanged(T const& t) = 0;
        listener *next;
    };

    template<class T, class TListener>
    struct listener_impl : public listener<T>
    {
        TListener listener_;
        listener_impl(TListener const& l) : listener_(l) {}
        listener_impl(listener_impl const& l) : listener_(l.listener_) {}

        void onChanged(T const& t) {
            listener_(t);
        }
    };

    listener<TBase> * listener_;

    void setbind(HWND hwnd, data_binder<TBase>* b){
        if(binder_)
            delete binder_;
        binder_ = b;
        if(binder_)
            setValue(hwnd, binder_->get());
    }

    void addListener(listener<TBase>* l) {
        if(l == NULL)
            return ;
        l->next = listener_;
        listener_ = l;
    }

    BOOL wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT& pret){
        if(message == WM_NOTIFY){
            onNotify(hwnd, (NMHDR*)lParam);
            pret = 0;
            return TRUE;
        }
        return FALSE;
    }

    virtual void onNotify(HWND hwnd, NMHDR *hdr) = 0;
    virtual void setValue(HWND hwnd, TBase const&) = 0;

    void onChanged(TBase const& t) {
        if(binder_)
            binder_->set(t);
        for(listener<TBase> *l = listener_; l; l = l->next)
            l->onChanged(t);
    }
public:
    DataControlPeer():binder_(NULL), listener_(NULL){}
    DataControlPeer(DataControlPeer & p): WindowPeer(p), binder_(NULL), listener_(NULL){}
    ~DataControlPeer(){
        if(binder_)
            delete binder_;
        for(listener<TBase> *l = listener_; l ; l = l->next){
            delete l;
        }
    }

    void bind(HWND hwnd, TBase* ptr){
        if(ptr == NULL)
            return ;
        setbind(hwnd, new ptr_data_binder<TBase>(ptr));
    }
    template<class TAccess>
    void bind(HWND hwnd, TAccess const& a){
        setbind(hwnd, new access_data_binder<TBase, TAccess>(a));
    }
    template<class TListener>
    void onChanged(TListener const& l){
        addListener(new listener_impl<TListener>(l));
    }
};

class DataControl {
protected:
    HWND hwnd_;
public:
    DataControl(): hwnd_(0) {}
    DataControl(HWND hwnd) : hwnd_(hwnd) {}
    DataControl(const DataControl& d): hwnd_(d.hwnd_){}

    HWND hwnd()const { return hwnd_; }
};

///////////////////////////////////////////////////////////////////////////
//for Number

template<class NumberData> //Number
class NumberPeer : public DataControlPeer<typename NumberData::DataType>
{
protected:
    typedef typename NumberData::DataTranslator DataTranslator;
    RefPtr<DataTranslator> translator_;
public:
    static NumberPeer<NumberData>* GetPeer(HWND hwnd);
    static NumberPeer<NumberData>* GetWritePeer(HWND hwnd);

    NumberPeer():translator_(NumberData::GetDefault()){}
    NumberPeer(NumberPeer & p) : DataControlPeer<typename NumberData::DataType>(p), translator_(p.translator_) {}

    void setDataTranslator(DataTranslator* t) {
        translator_ = t;
    }
};


template<class NumberData>
class NumberTextPeer : public NumberPeer<NumberData>
{
public:
    static void init() {
        static NumberTextPeer * peer = NULL;
        if(peer == NULL)
        {
            peer = new NumberTextPeer();
            AddWindowPeer(L"Edit", peer);
            AddWindowPeer(L"Static", peer);
        }
    }

    NumberTextPeer() { }
    NumberTextPeer(NumberTextPeer & p): NumberPeer<NumberData>(p) {}
protected:
    void onNotify(HWND hwnd, NMHDR* hdr) {
        if(hdr->code == EN_CHANGE){
            wchar_t text[1024];
            GetWindowText(hwnd, text, sizeof(text)/sizeof(text[0]));
            onChanged(translator_->fromString(text));
        }
    }
    void setValue(HWND hwnd, typename NumberData::DataType const& n) {
        wchar_t text[1024];
        translator_->toString(n, text);
        SetWindowText(hwnd, text);
    }

    Prototype* clone() {
        return new NumberTextPeer(*this);
    }
};

template<class NumberData>
inline NumberPeer<NumberData>* NumberPeer<NumberData>::GetPeer(HWND hwnd)
{
    NumberTextPeer<NumberData>::init();
    return static_cast<NumberPeer<NumberData>*>(WindowPeer::AutoGet(hwnd));
}

template<class NumberData>
inline NumberPeer<NumberData>* NumberPeer<NumberData>::GetWritePeer(HWND hwnd){
    NumberTextPeer<NumberData>::init();
    return static_cast<NumberPeer<NumberData>*>(WindowPeer::AutoGetWriteable(hwnd));
}

/////////////////////////////
//NumberData

template<class TBaseData>
class NumberDataTranslator : public RefCnt<NumberDataTranslator<TBaseData> > {
public:
    virtual TBaseData fromString(wchar_t const*) = 0;
    virtual void toString(TBaseData const&, wchar_t*) = 0;
};

template<class TBaseData, class DefaultTranslator>
struct NumberData{
    typedef TBaseData DataType;
    typedef NumberDataTranslator<TBaseData> DataTranslator;

    static DataTranslator* GetDefault(){
        static DefaultTranslator translator;
        if(translator.refcount() == 0) translator.ref();
        return &translator;
    }
};

class IntNumberDataTranslator : public NumberDataTranslator<int>
{
public:
    int fromString(wchar_t const* str){
        return str ? _wtoi(str) : 0;
    }
    void toString(int const& i, wchar_t* str) {
        wsprintf(str, L"%d",i);
    }
};

typedef NumberData<int, IntNumberDataTranslator> IntNumberData;
typedef NumberPeer<IntNumberData> IntNumberPeer;

//////////////////////////////


template<class NumberData>
class Number : public DataControl{
    NumberPeer<NumberData>* getPeer(){
        return NumberPeer<NumberData>::GetPeer(hwnd_);
    }
    NumberPeer<NumberData>* getWritePeer() {
        return NumberPeer<NumberData>::GetWritePeer(hwnd_);
    }
public:
    Number(){}
    Number(HWND hwnd):DataControl(hwnd) {}
    Number(Number const& n) : DataControl(n) {}

    Number& bind(int *p){
        getWritePeer()->bind(hwnd_, p);
        return *this;
    }
    template<class TAccess>
    Number& bind(TAccess const& a){
        getWritePeer()->bind(a);
        return *this;
    }

    template<class TL>
    Number& onChanged(TL const& l){
        getPeer()->addListener(l);
        return *this;
    }
};

typedef Number<IntNumberData> IntNumber;

}

#endif
