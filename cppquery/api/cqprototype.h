#ifndef CQ_PROTOTYPE_H
#define CQ_PROTOTYPE_H

#include "cqcomm.h"

namespace cppquery
{

class Prototype : public RefCnt<Prototype>
{
protected:
    RefPtr<Prototype>  super_;

    Prototype(Prototype* super) : super_(super){}
public:
    Prototype(){}
    virtual ~Prototype(){}

    virtual Prototype* clone() = 0;

    Prototype* super(){ return super_.ptr(); }
    const Prototype *super() const { return super_.ptr(); }
    void setProperty(Prototype* p){ super_.set(p); }
};

template<class P>
class PrototypePtr : public RefPtr<P>
{
public:
    PrototypePtr(){}
    PrototypePtr(P* p):RefPtr<P>(p) {}
    PrototypePtr(const PrototypePtr& p) : RefPtr<P>(*((const RefPtr<P>*)&p)) {}

    PrototypePtr& writeable() {
        if(!ptr() || ptr()->refcount() == 1)
            return *this;
        
        P *p = ptr()->clone();
        set(p);

        return *this;
    }

    P* super() {
        return (P*)(ptr() ? ptr()->super());
    }

    const P* super() const {
        return (const P*)(ptr() ? ptr()->super());
    }
};

}


#endif
