#ifndef CP_BIND_H
#define CP_BIND_H

#include "cqfunction.h"

namespace cppquery {


template<class R>
function_t<function_ptr0<R>, list0> bind(R (*f) (void) )
{ return function_t<function_ptr0<R>, list0>(function_ptr0<R>(f), list0()); }


template<class R, class T1, class A1>
function_t<function_ptr1<R,T1>, list1<A1> > bind(R (*f)(T1), A1 a1)
{ return function_t<function_ptr1<R,T1>, list1<A1> >(function_ptr1<R,T1>(f), list1<A1>(a1)); }


template<class R, class T1, class T2, class A1, class A2>
function_t<function_ptr2<R,T1, T2>, list2<A1, A2> > bind(R (*f)(T1, T2), A1 a1, A2 a2)
{ return function_t<function_ptr2<R,T1, T2>, list2<A1, A2> >(function_ptr2<R,T1, T2>(f), list2<A1, A2>(a1, a2)); }


template<class R, class T1, class T2, class T3, class A1, class A2, class A3>
function_t<function_ptr3<R,T1, T2, T3>, list3<A1, A2, A3> > bind(R (*f)(T1, T2, T3), A1 a1, A2 a2, A3 a3)
{ return function_t<function_ptr3<R,T1, T2, T3>, list3<A1, A2, A3> >(function_ptr3<R,T1, T2, T3>(f), list3<A1, A2, A3>(a1, a2, a3)); }


template<class R, class T1, class T2, class T3, class T4, class A1, class A2, class A3, class A4>
function_t<function_ptr4<R,T1, T2, T3, T4>, list4<A1, A2, A3, A4> > bind(R (*f)(T1, T2, T3, T4), A1 a1, A2 a2, A3 a3, A4 a4)
{ return function_t<function_ptr4<R,T1, T2, T3, T4>, list4<A1, A2, A3, A4> >(function_ptr4<R,T1, T2, T3, T4>(f), list4<A1, A2, A3, A4>(a1, a2, a3, a4)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class A1, class A2, class A3, class A4, class A5>
function_t<function_ptr5<R,T1, T2, T3, T4, T5>, list5<A1, A2, A3, A4, A5> > bind(R (*f)(T1, T2, T3, T4, T5), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{ return function_t<function_ptr5<R,T1, T2, T3, T4, T5>, list5<A1, A2, A3, A4, A5> >(function_ptr5<R,T1, T2, T3, T4, T5>(f), list5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class A1, class A2, class A3, class A4, class A5, class A6>
function_t<function_ptr6<R,T1, T2, T3, T4, T5, T6>, list6<A1, A2, A3, A4, A5, A6> > bind(R (*f)(T1, T2, T3, T4, T5, T6), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{ return function_t<function_ptr6<R,T1, T2, T3, T4, T5, T6>, list6<A1, A2, A3, A4, A5, A6> >(function_ptr6<R,T1, T2, T3, T4, T5, T6>(f), list6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
function_t<function_ptr7<R,T1, T2, T3, T4, T5, T6, T7>, list7<A1, A2, A3, A4, A5, A6, A7> > bind(R (*f)(T1, T2, T3, T4, T5, T6, T7), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{ return function_t<function_ptr7<R,T1, T2, T3, T4, T5, T6, T7>, list7<A1, A2, A3, A4, A5, A6, A7> >(function_ptr7<R,T1, T2, T3, T4, T5, T6, T7>(f), list7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
function_t<function_ptr8<R,T1, T2, T3, T4, T5, T6, T7, T8>, list8<A1, A2, A3, A4, A5, A6, A7, A8> > bind(R (*f)(T1, T2, T3, T4, T5, T6, T7, T8), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{ return function_t<function_ptr8<R,T1, T2, T3, T4, T5, T6, T7, T8>, list8<A1, A2, A3, A4, A5, A6, A7, A8> >(function_ptr8<R,T1, T2, T3, T4, T5, T6, T7, T8>(f), list8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
function_t<function_ptr9<R,T1, T2, T3, T4, T5, T6, T7, T8, T9>, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> > bind(R (*f)(T1, T2, T3, T4, T5, T6, T7, T8, T9), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{ return function_t<function_ptr9<R,T1, T2, T3, T4, T5, T6, T7, T8, T9>, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> >(function_ptr9<R,T1, T2, T3, T4, T5, T6, T7, T8, T9>(f), list9<A1, A2, A3, A4, A5, A6, A7, A8, A9>(a1, a2, a3, a4, a5, a6, a7, a8, a9)); }

//wind3 bind
#ifdef WIN32
template<class R>
function_t<function_ptr_cbapi0<R>, list0> bind(R (CBAPI *f) (void) )
{ return function_t<function_ptr_cbapi0<R>, list0>(function_ptr_cbapi0<R>(f), list0()); }


template<class R, class T1, class A1>
function_t<function_ptr_cbapi1<R,T1>, list1<A1> > bind(R (CBAPI *f)(T1), A1 a1)
{ return function_t<function_ptr_cbapi1<R,T1>, list1<A1> >(function_ptr_cbapi1<R,T1>(f), list1<A1>(a1)); }


template<class R, class T1, class T2, class A1, class A2>
function_t<function_ptr_cbapi2<R,T1, T2>, list2<A1, A2> > bind(R (CBAPI *f)(T1, T2), A1 a1, A2 a2)
{ return function_t<function_ptr_cbapi2<R,T1, T2>, list2<A1, A2> >(function_ptr_cbapi2<R,T1, T2>(f), list2<A1, A2>(a1, a2)); }


template<class R, class T1, class T2, class T3, class A1, class A2, class A3>
function_t<function_ptr_cbapi3<R,T1, T2, T3>, list3<A1, A2, A3> > bind(R (CBAPI *f)(T1, T2, T3), A1 a1, A2 a2, A3 a3)
{ return function_t<function_ptr_cbapi3<R,T1, T2, T3>, list3<A1, A2, A3> >(function_ptr_cbapi3<R,T1, T2, T3>(f), list3<A1, A2, A3>(a1, a2, a3)); }


template<class R, class T1, class T2, class T3, class T4, class A1, class A2, class A3, class A4>
function_t<function_ptr_cbapi4<R,T1, T2, T3, T4>, list4<A1, A2, A3, A4> > bind(R (CBAPI *f)(T1, T2, T3, T4), A1 a1, A2 a2, A3 a3, A4 a4)
{ return function_t<function_ptr_cbapi4<R,T1, T2, T3, T4>, list4<A1, A2, A3, A4> >(function_ptr_cbapi4<R,T1, T2, T3, T4>(f), list4<A1, A2, A3, A4>(a1, a2, a3, a4)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class A1, class A2, class A3, class A4, class A5>
function_t<function_ptr_cbapi5<R,T1, T2, T3, T4, T5>, list5<A1, A2, A3, A4, A5> > bind(R (CBAPI *f)(T1, T2, T3, T4, T5), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{ return function_t<function_ptr_cbapi5<R,T1, T2, T3, T4, T5>, list5<A1, A2, A3, A4, A5> >(function_ptr_cbapi5<R,T1, T2, T3, T4, T5>(f), list5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class A1, class A2, class A3, class A4, class A5, class A6>
function_t<function_ptr_cbapi6<R,T1, T2, T3, T4, T5, T6>, list6<A1, A2, A3, A4, A5, A6> > bind(R (CBAPI *f)(T1, T2, T3, T4, T5, T6), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{ return function_t<function_ptr_cbapi6<R,T1, T2, T3, T4, T5, T6>, list6<A1, A2, A3, A4, A5, A6> >(function_ptr_cbapi6<R,T1, T2, T3, T4, T5, T6>(f), list6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
function_t<function_ptr_cbapi7<R,T1, T2, T3, T4, T5, T6, T7>, list7<A1, A2, A3, A4, A5, A6, A7> > bind(R (CBAPI *f)(T1, T2, T3, T4, T5, T6, T7), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{ return function_t<function_ptr_cbapi7<R,T1, T2, T3, T4, T5, T6, T7>, list7<A1, A2, A3, A4, A5, A6, A7> >(function_ptr_cbapi7<R,T1, T2, T3, T4, T5, T6, T7>(f), list7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
function_t<function_ptr_cbapi8<R,T1, T2, T3, T4, T5, T6, T7, T8>, list8<A1, A2, A3, A4, A5, A6, A7, A8> > bind(R (CBAPI *f)(T1, T2, T3, T4, T5, T6, T7, T8), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{ return function_t<function_ptr_cbapi8<R,T1, T2, T3, T4, T5, T6, T7, T8>, list8<A1, A2, A3, A4, A5, A6, A7, A8> >(function_ptr_cbapi8<R,T1, T2, T3, T4, T5, T6, T7, T8>(f), list8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8)); }


template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
function_t<function_ptr_cbapi9<R,T1, T2, T3, T4, T5, T6, T7, T8, T9>, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> > bind(R (CBAPI *f)(T1, T2, T3, T4, T5, T6, T7, T8, T9), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{ return function_t<function_ptr_cbapi9<R,T1, T2, T3, T4, T5, T6, T7, T8, T9>, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> >(function_ptr_cbapi9<R,T1, T2, T3, T4, T5, T6, T7, T8, T9>(f), list9<A1, A2, A3, A4, A5, A6, A7, A8, A9>(a1, a2, a3, a4, a5, a6, a7, a8, a9)); }

#endif //WIN32


template<class R, class X, class XRef>
function_t<method_function0<R,X>, list1<XRef> > bind(R (X::*f)(), XRef self)
{ return function_t<method_function0<R, X>, list1<XRef> >(method_function0<R, X>(f), list1<XRef>(self)); }
template<class R, class X, class XRef>
function_t<method_const_function0<R,X>, list1<XRef> > bind(R (X::*f)() const, XRef self)
{ return function_t<method_const_function0<R, X>, list1<XRef> >(method_function0<R, X>(f), list1<XRef>(self)); }


template<class R, class X, class XRef, class T1, class A1>
function_t<method_function1<R, X, T1>, list2<XRef, A1> > bind(R (*f)(T1), XRef self, A1 a1)
{ return function_t<method_function1<R,T1>, list2<XRef, A1> >(method_function1<R, X, T1>(f), list2<XRef, A1>(self, a1)); }
template<class R, class X, class XRef, class T1, class A1>
function_t<method_const_function1<R, X, T1>, list2<XRef, A1> > bind(R (*f)(T1), XRef self, A1 a1)
{ return function_t<method_const_function1<R,T1>, list1<XRef, A1> >(method_const_function1<R, X, T1>(f), list2<XRef, A1>(self, a1)); }


template<class R, class X, class XRef, class T1, class T2, class A1, class A2>
function_t<method_function2<R, X, T1, T2>, list3<XRef, A1, A2> > bind(R (*f)(T1, T2), XRef self, A1 a1, A2 a2)
{ return function_t<method_function2<R,T1, T2>, list3<XRef, A1, A2> >(method_function2<R, X, T1, T2>(f), list3<XRef, A1, A2>(self, a1, a2)); }
template<class R, class X, class XRef, class T1, class T2, class A1, class A2>
function_t<method_const_function2<R, X, T1, T2>, list3<XRef, A1, A2> > bind(R (*f)(T1, T2), XRef self, A1 a1, A2 a2)
{ return function_t<method_const_function2<R,T1, T2>, list2<XRef, A1, A2> >(method_const_function2<R, X, T1, T2>(f), list3<XRef, A1, A2>(self, a1, a2)); }


template<class R, class X, class XRef, class T1, class T2, class T3, class A1, class A2, class A3>
function_t<method_function3<R, X, T1, T2, T3>, list4<XRef, A1, A2, A3> > bind(R (*f)(T1, T2, T3), XRef self, A1 a1, A2 a2, A3 a3)
{ return function_t<method_function3<R,T1, T2, T3>, list4<XRef, A1, A2, A3> >(method_function3<R, X, T1, T2, T3>(f), list4<XRef, A1, A2, A3>(self, a1, a2, a3)); }
template<class R, class X, class XRef, class T1, class T2, class T3, class A1, class A2, class A3>
function_t<method_const_function3<R, X, T1, T2, T3>, list4<XRef, A1, A2, A3> > bind(R (*f)(T1, T2, T3), XRef self, A1 a1, A2 a2, A3 a3)
{ return function_t<method_const_function3<R,T1, T2, T3>, list3<XRef, A1, A2, A3> >(method_const_function3<R, X, T1, T2, T3>(f), list4<XRef, A1, A2, A3>(self, a1, a2, a3)); }


template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class A1, class A2, class A3, class A4>
function_t<method_function4<R, X, T1, T2, T3, T4>, list5<XRef, A1, A2, A3, A4> > bind(R (*f)(T1, T2, T3, T4), XRef self, A1 a1, A2 a2, A3 a3, A4 a4)
{ return function_t<method_function4<R,T1, T2, T3, T4>, list5<XRef, A1, A2, A3, A4> >(method_function4<R, X, T1, T2, T3, T4>(f), list5<XRef, A1, A2, A3, A4>(self, a1, a2, a3, a4)); }
template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class A1, class A2, class A3, class A4>
function_t<method_const_function4<R, X, T1, T2, T3, T4>, list5<XRef, A1, A2, A3, A4> > bind(R (*f)(T1, T2, T3, T4), XRef self, A1 a1, A2 a2, A3 a3, A4 a4)
{ return function_t<method_const_function4<R,T1, T2, T3, T4>, list4<XRef, A1, A2, A3, A4> >(method_const_function4<R, X, T1, T2, T3, T4>(f), list5<XRef, A1, A2, A3, A4>(self, a1, a2, a3, a4)); }


template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class T5, class A1, class A2, class A3, class A4, class A5>
function_t<method_function5<R, X, T1, T2, T3, T4, T5>, list6<XRef, A1, A2, A3, A4, A5> > bind(R (*f)(T1, T2, T3, T4, T5), XRef self, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{ return function_t<method_function5<R,T1, T2, T3, T4, T5>, list6<XRef, A1, A2, A3, A4, A5> >(method_function5<R, X, T1, T2, T3, T4, T5>(f), list6<XRef, A1, A2, A3, A4, A5>(self, a1, a2, a3, a4, a5)); }
template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class T5, class A1, class A2, class A3, class A4, class A5>
function_t<method_const_function5<R, X, T1, T2, T3, T4, T5>, list6<XRef, A1, A2, A3, A4, A5> > bind(R (*f)(T1, T2, T3, T4, T5), XRef self, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{ return function_t<method_const_function5<R,T1, T2, T3, T4, T5>, list5<XRef, A1, A2, A3, A4, A5> >(method_const_function5<R, X, T1, T2, T3, T4, T5>(f), list6<XRef, A1, A2, A3, A4, A5>(self, a1, a2, a3, a4, a5)); }


template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class T5, class T6, class A1, class A2, class A3, class A4, class A5, class A6>
function_t<method_function6<R, X, T1, T2, T3, T4, T5, T6>, list7<XRef, A1, A2, A3, A4, A5, A6> > bind(R (*f)(T1, T2, T3, T4, T5, T6), XRef self, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{ return function_t<method_function6<R,T1, T2, T3, T4, T5, T6>, list7<XRef, A1, A2, A3, A4, A5, A6> >(method_function6<R, X, T1, T2, T3, T4, T5, T6>(f), list7<XRef, A1, A2, A3, A4, A5, A6>(self, a1, a2, a3, a4, a5, a6)); }
template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class T5, class T6, class A1, class A2, class A3, class A4, class A5, class A6>
function_t<method_const_function6<R, X, T1, T2, T3, T4, T5, T6>, list7<XRef, A1, A2, A3, A4, A5, A6> > bind(R (*f)(T1, T2, T3, T4, T5, T6), XRef self, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{ return function_t<method_const_function6<R,T1, T2, T3, T4, T5, T6>, list6<XRef, A1, A2, A3, A4, A5, A6> >(method_const_function6<R, X, T1, T2, T3, T4, T5, T6>(f), list7<XRef, A1, A2, A3, A4, A5, A6>(self, a1, a2, a3, a4, a5, a6)); }


template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
function_t<method_function7<R, X, T1, T2, T3, T4, T5, T6, T7>, list8<XRef, A1, A2, A3, A4, A5, A6, A7> > bind(R (*f)(T1, T2, T3, T4, T5, T6, T7), XRef self, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{ return function_t<method_function7<R,T1, T2, T3, T4, T5, T6, T7>, list8<XRef, A1, A2, A3, A4, A5, A6, A7> >(method_function7<R, X, T1, T2, T3, T4, T5, T6, T7>(f), list8<XRef, A1, A2, A3, A4, A5, A6, A7>(self, a1, a2, a3, a4, a5, a6, a7)); }
template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
function_t<method_const_function7<R, X, T1, T2, T3, T4, T5, T6, T7>, list8<XRef, A1, A2, A3, A4, A5, A6, A7> > bind(R (*f)(T1, T2, T3, T4, T5, T6, T7), XRef self, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{ return function_t<method_const_function7<R,T1, T2, T3, T4, T5, T6, T7>, list7<XRef, A1, A2, A3, A4, A5, A6, A7> >(method_const_function7<R, X, T1, T2, T3, T4, T5, T6, T7>(f), list8<XRef, A1, A2, A3, A4, A5, A6, A7>(self, a1, a2, a3, a4, a5, a6, a7)); }


template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
function_t<method_function8<R, X, T1, T2, T3, T4, T5, T6, T7, T8>, list9<XRef, A1, A2, A3, A4, A5, A6, A7, A8> > bind(R (*f)(T1, T2, T3, T4, T5, T6, T7, T8), XRef self, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{ return function_t<method_function8<R,T1, T2, T3, T4, T5, T6, T7, T8>, list9<XRef, A1, A2, A3, A4, A5, A6, A7, A8> >(method_function8<R, X, T1, T2, T3, T4, T5, T6, T7, T8>(f), list9<XRef, A1, A2, A3, A4, A5, A6, A7, A8>(self, a1, a2, a3, a4, a5, a6, a7, a8)); }
template<class R, class X, class XRef, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
function_t<method_const_function8<R, X, T1, T2, T3, T4, T5, T6, T7, T8>, list9<XRef, A1, A2, A3, A4, A5, A6, A7, A8> > bind(R (*f)(T1, T2, T3, T4, T5, T6, T7, T8), XRef self, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{ return function_t<method_const_function8<R,T1, T2, T3, T4, T5, T6, T7, T8>, list8<XRef, A1, A2, A3, A4, A5, A6, A7, A8> >(method_const_function8<R, X, T1, T2, T3, T4, T5, T6, T7, T8>(f), list9<XRef, A1, A2, A3, A4, A5, A6, A7, A8>(self, a1, a2, a3, a4, a5, a6, a7, a8)); }

}

#endif