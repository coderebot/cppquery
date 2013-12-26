#ifndef CQ_FUNCTION_H
#define CQ_FUNCTION_H

#include "cqlist.h"

namespace cppquery{

//// for call
template<class T>
struct type {
	typedef T inner_type;
};

template<class T, T const TDefualt>
struct type_default {
	typedef T inner_type;
	static const T DefValue() { return TDefualt; }
};

template<class R1, class R2, class F, class A1>
R1 call(type<R1>, type<R2>, F const &f, A1 const& a1)
{
	return arg_cast<R1>(f(a1));
}

template<class R1, class F, class A1>
R1 call(type<R1>, type<void>, F const& f, A1 const& a1)
{
	f(a1);
	return T_NULL(R1);
}

template<class R1, R1 const R1Default, class F, class A1>
R1 call(type_default<R1, R1Default>, type<void>, F const& f, A1 const& a1)
{
	f(a1);
	return type_default<R1,R1Default>::DefValue();
}


template<class R1, class R2, class F, class A1, class A2>
R1 call(type<R1>, type<R2>, F const &f, A1 const& a1, A2 const& a2)
{
	return arg_cast<R1>(f(a1, a2));
}

template<class R1, class F, class A1, class A2>
R1 call(type<R1>, type<void>, F const& f, A1 const& a1, A2 const& a2)
{
	f(a1, a2);
	return T_NULL(R1);
}

template<class R1, R1 const R1Default, class F, class A1, class A2>
R1 call(type_default<R1, R1Default>, type<void>, F const& f, A1 const& a1, A2 const& a2)
{
	f(a1, a2);
	return type_default<R1,R1Default>::DefValue();
}


template<class T>
struct func_base_t { 
	typedef T driver_type;
	driver_type& driver() { return *(static_cast<driver_type*>(this)); }
	driver_type const& driver() const {
		return *(static_cast<driver_type const*>(this));
	}
};

template<class F, class L>
struct function_t : public func_base_t<function_t<F, L> >{
	typedef typename F::result_type result_type;
	F f_;
	L l_;

	function_t(F const& f, L const &l) : f_(f), l_(l) { }
	function_t(const function_t & f)  : f_(f.f_), l_(f.l_){ }

	
	result_type operator()() const {
		list0 l;
		return l_(f_, l);
	}

	template<class R>
	R operator()(type<R>) const {
		list0 l;
		return call(type<R>(), type<result_type>(), l_, f_, l);
	}
	template<class R, R const RDef>
	R operator()(type_default<R, RDef>) const {
		list0 l;
		return call(type_default<R, RDef>(), type<result_type>(), l_, f_,l);
	}

	/* dynamic_list call */ 
	result_type operator()(dynamic_list const& l) const { 
		return l_(f_, l.driver()); 
	} 
	template<class R> 
	R operator()(type<R> const& r, dynamic_list const& l) const {
		return call(r, type<result_type>(), l_, f_, l.driver());
	}
	template<class R, R const RDef>
	R operator()(type_default<R, RDef> const& rd, dynamic_list const& l) const {
		return call(rd, type<result_type>(), l_, f_, l.driver());
	}
	
	template<class TList>
	bool checkArg(const list_t<TList>& l) const {
		return l_.isElementHolderInList(l);
	}


	template<class A1> result_type operator()(list1<A1> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1> R operator()(type<R> const& r, list1<A1> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1> R operator()(type_default<R, RDef> const& rd, list1<A1> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1> result_type operator()(A1 a1) const 
	{ return (*this)(list1<A1>(a1)); }
	template<class R, class A1> R operator()(type<R> const& r, A1 a1) const 
	{ return (*this)(r, list1<A1>(a1)); }
	template<class R, R const RDef, class A1> R operator()(type_default<R, RDef> const& rd, A1 a1) const 
	{ return (*this)(rd, list1<A1>(a1)); }

	template<class A1, class A2> result_type operator()(list2<A1, A2> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1, class A2> R operator()(type<R> const& r, list2<A1, A2> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1, class A2> R operator()(type_default<R, RDef> const& rd, list2<A1, A2> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1, class A2> result_type operator()(A1 a1, A2 a2) const 
	{ return (*this)(list2<A1, A2>(a1, a2)); }
	template<class R, class A1, class A2> R operator()(type<R> const& r, A1 a1, A2 a2) const 
	{ return (*this)(r, list2<A1, A2>(a1, a2)); }
	template<class R, R const RDef, class A1, class A2> R operator()(type_default<R, RDef> const& rd, A1 a1, A2 a2) const 
	{ return (*this)(rd, list2<A1, A2>(a1, a2)); }

	template<class A1, class A2, class A3> result_type operator()(list3<A1, A2, A3> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1, class A2, class A3> R operator()(type<R> const& r, list3<A1, A2, A3> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1, class A2, class A3> R operator()(type_default<R, RDef> const& rd, list3<A1, A2, A3> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1, class A2, class A3> result_type operator()(A1 a1, A2 a2, A3 a3) const 
	{ return (*this)(list3<A1, A2, A3>(a1, a2, a3)); }
	template<class R, class A1, class A2, class A3> R operator()(type<R> const& r, A1 a1, A2 a2, A3 a3) const 
	{ return (*this)(r, list3<A1, A2, A3>(a1, a2, a3)); }
	template<class R, R const RDef, class A1, class A2, class A3> R operator()(type_default<R, RDef> const& rd, A1 a1, A2 a2, A3 a3) const 
	{ return (*this)(rd, list3<A1, A2, A3>(a1, a2, a3)); }

	template<class A1, class A2, class A3, class A4> result_type operator()(list4<A1, A2, A3, A4> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1, class A2, class A3, class A4> R operator()(type<R> const& r, list4<A1, A2, A3, A4> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4> R operator()(type_default<R, RDef> const& rd, list4<A1, A2, A3, A4> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1, class A2, class A3, class A4> result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4) const 
	{ return (*this)(list4<A1, A2, A3, A4>(a1, a2, a3, a4)); }
	template<class R, class A1, class A2, class A3, class A4> R operator()(type<R> const& r, A1 a1, A2 a2, A3 a3, A4 a4) const 
	{ return (*this)(r, list4<A1, A2, A3, A4>(a1, a2, a3, a4)); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4> R operator()(type_default<R, RDef> const& rd, A1 a1, A2 a2, A3 a3, A4 a4) const 
	{ return (*this)(rd, list4<A1, A2, A3, A4>(a1, a2, a3, a4)); }

	template<class A1, class A2, class A3, class A4, class A5> result_type operator()(list5<A1, A2, A3, A4, A5> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1, class A2, class A3, class A4, class A5> R operator()(type<R> const& r, list5<A1, A2, A3, A4, A5> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5> R operator()(type_default<R, RDef> const& rd, list5<A1, A2, A3, A4, A5> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1, class A2, class A3, class A4,  class A5> result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const 
	{ return (*this)(list5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5)); }
	template<class R, class A1, class A2, class A3, class A4, class A5> R operator()(type<R> const& r, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const 
	{ return (*this)(r, list5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5)); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5> R operator()(type_default<R, RDef> const& rd, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const 
	{ return (*this)(rd, list5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5)); }

	template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(list6<A1, A2, A3, A4, A5, A6> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1, class A2, class A3, class A4, class A5, class A6> R operator()(type<R> const& r, list6<A1, A2, A3, A4, A5, A6> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5, class A6> R operator()(type_default<R, RDef> const& rd, list6<A1, A2, A3, A4, A5, A6> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1, class A2, class A3, class A4,  class A5, class A6> result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const 
	{ return (*this)(list6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6)); }
	template<class R, class A1, class A2, class A3, class A4, class A5, class A6> R operator()(type<R> const& r, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const 
	{ return (*this)(r, list6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6)); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5, class A6> R operator()(type_default<R, RDef> const& rd, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const 
	{ return (*this)(rd, list6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6)); }

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(list7<A1, A2, A3, A4, A5, A6, A7> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7> R operator()(type<R> const& r, list7<A1, A2, A3, A4, A5, A6, A7> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5, class A6, class A7> R operator()(type_default<R, RDef> const& rd, list7<A1, A2, A3, A4, A5, A6, A7> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1, class A2, class A3, class A4,  class A5, class A6, class A7> result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const 
	{ return (*this)(list7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7)); }
	template<class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7> R operator()(type<R> const& r, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const 
	{ return (*this)(r, list7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7)); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5, class A6, class A7> R operator()(type_default<R, RDef> const& rd, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const 
	{ return (*this)(rd, list7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7)); }

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(list8<A1, A2, A3, A4, A5, A6, A7, A8> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> R operator()(type<R> const& r, list8<A1, A2, A3, A4, A5, A6, A7, A8> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> R operator()(type_default<R, RDef> const& rd, list8<A1, A2, A3, A4, A5, A6, A7, A8> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1, class A2, class A3, class A4,  class A5, class A6, class A7, class A8> result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const 
	{ return (*this)(list8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8)); }
	template<class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> R operator()(type<R> const& r, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const 
	{ return (*this)(r, list8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8)); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> R operator()(type_default<R, RDef> const& rd, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const 
	{ return (*this)(rd, list8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8)); }

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> const& l) const
	{ return l_(f_, l); }
	template<class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> R operator()(type<R> const& r, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> const& l) const 
	{ return call(r, type<result_type>(), l_, f_, l); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> R operator()(type_default<R, RDef> const& rd, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> const& l) const 
	{ return call(rd, type<result_type>(), l_, f_, l); }
	template<class A1, class A2, class A3, class A4,  class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const 
	{ return (*this)(list9<A1, A2, A3, A4, A5, A6, A7, A8, A9>(a1, a2, a3, a4, a5, a6, a7, a8, a9)); }
	template<class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> R operator()(type<R> const& r, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const 
	{ return (*this)(r, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9>(a1, a2, a3, a4, a5, a6, a7, a8, a9)); }
	template<class R, R const RDef, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> R operator()(type_default<R, RDef> const& rd, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const 
	{ return (*this)(rd, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9>(a1, a2, a3, a4, a5, a6, a7, a8, a9)); }

};


/////////////////////////////////////////////
template<class F>
function_t<F, list0> make_function(F const &f){
    return function_t<F, list0>(f, list0());
}

template<class F, class A1>
function_t<F, list1<A1> > make_function(F const& f, A1 a1)
{ return function_t<F, list1<A1> >(f, list1<A1>(a1)); }


template<class F, class A1, class A2>
function_t<F, list2<A1, A2> > make_function(F const& f, A1 a1, A2 a2)
{ return function_t<F, list2<A1, A2> >(f, list2<A1, A2>(a1, a2)); }


template<class F, class A1, class A2, class A3>
function_t<F, list3<A1, A2, A3> > make_function(F const& f, A1 a1, A2 a2, A3 a3)
{ return function_t<F, list3<A1, A2, A3> >(f, list3<A1, A2, A3>(a1, a2, a3)); }


template<class F, class A1, class A2, class A3, class A4>
function_t<F, list4<A1, A2, A3, A4> > make_function(F const& f, A1 a1, A2 a2, A3 a3, A4 a4)
{ return function_t<F, list4<A1, A2, A3, A4> >(f, list4<A1, A2, A3, A4>(a1, a2, a3, a4)); }


template<class F, class A1, class A2, class A3, class A4, class A5>
function_t<F, list5<A1, A2, A3, A4, A5> > make_function(F const& f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{ return function_t<F, list5<A1, A2, A3, A4, A5> >(f, list5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5)); }


template<class F, class A1, class A2, class A3, class A4, class A5, class A6>
function_t<F, list6<A1, A2, A3, A4, A5, A6> > make_function(F const& f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{ return function_t<F, list6<A1, A2, A3, A4, A5, A6> >(f, list6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6)); }


template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
function_t<F, list7<A1, A2, A3, A4, A5, A6, A7> > make_function(F const& f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{ return function_t<F, list7<A1, A2, A3, A4, A5, A6, A7> >(f, list7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7)); }


template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
function_t<F, list8<A1, A2, A3, A4, A5, A6, A7, A8> > make_function(F const& f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{ return function_t<F, list8<A1, A2, A3, A4, A5, A6, A7, A8> >(f, list8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8)); }


template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
function_t<F, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> > make_function(F const& f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{ return function_t<F, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> >(f, list9<A1, A2, A3, A4, A5, A6, A7, A8, A9>(a1, a2, a3, a4, a5, a6, a7, a8, a9)); }

/////////////////////////////////////////////////////////////////
///function Ptr
template<class R>
struct function_ptr0{
    typedef R result_type;
    typedef R (*Func)(void);
    Func f_;

    function_ptr0(Func const &f) : f_(f) { }
    function_ptr0(const function_ptr0& f) : f_(f.f_) {} 

    result_type operator()() const {
        return f_();
    }
};
template<class R>
function_ptr0<R> func_ptr(R(*f)(void)) {
    return function_ptr0<R>(f);
}

template<class R, class T1> struct function_ptr1 {
    typedef R result_type;
    typedef R (*Func)(T1); 
    Func f_;
    function_ptr1(Func const& f) : f_(f) {}
    function_ptr1(const function_ptr1& f) : f_(f.f_) {}
    template<class A1>
    result_type operator()(A1 a1) const 
    { return f_(arg_cast<T1>(a1)) ; }
    result_type operator()(T1 t1) const 
    { return f_(t1); }
};
template<class R, class T1>
function_ptr1<R, T1> func_ptr(R (*f)(T1) ) 
{ return function_ptr1<R, T1>(f); }

template<class R, class T1, class T2> struct function_ptr2 {
    typedef R result_type;
    typedef R (*Func)(T1,T2); 
    Func f_;
    function_ptr2(Func const& f) : f_(f) {}
    function_ptr2(const function_ptr2& f) : f_(f.f_) {}
    template<class A1, class A2>
    result_type operator()(A1 a1, A2 a2) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2)) ; }
    result_type operator()(T1 t1, T2 t2) const 
    { return f_(t1, t2); }
};
template<class R, class T1, class T2>
function_ptr2<R, T1, T2> func_ptr(R (*f)(T1,T2) ) 
{ return function_ptr2<R, T1,T2>(f); }

template<class R, class T1, class T2, class T3> struct function_ptr3 {
    typedef R result_type;
    typedef R (*Func)(T1,T2,T3); 
    Func f_;
    function_ptr3(Func const& f) : f_(f) {}
    function_ptr3(const function_ptr3& f) : f_(f.f_) {}
    template<class A1, class A2, class A3>
    result_type operator()(A1 a1, A2 a2, A3 a3) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3) const 
    { return f_(t1, t2, t3); }
};
template<class R, class T1, class T2, class T3>
function_ptr3<R, T1, T2, T3> func_ptr(R (*f)(T1,T2,T3) ) 
{ return function_ptr3<R,T1,T2,T3>(f); }

template<class R, class T1, class T2, class T3, class T4> struct function_ptr4 {
    typedef R result_type;
    typedef R (*Func)(T1, T2, T3, T4); 
    Func f_;
    function_ptr4(Func const& f) : f_(f) {}
    function_ptr4(const function_ptr4& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4) const 
    { return f_(t1, t2, t3, t4); }
};
template<class R, class T1, class T2, class T3, class T4>
function_ptr4<R, T1, T2, T3, T4> func_ptr(R (*f)(T1,T2,T3,T4) ) 
{ return function_ptr4<R,T1,T2,T3, T4>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5> struct function_ptr5 {
    typedef R result_type;
    typedef R (*Func)(T1, T2, T3, T4, T5); 
    Func f_;
    function_ptr5(Func const& f) : f_(f) {}
    function_ptr5(const function_ptr5& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) const 
    { return f_(t1, t2, t3, t4, t5); }
};
template<class R, class T1, class T2, class T3, class T4, class T5>
function_ptr5<R, T1, T2, T3, T4, T5> func_ptr(R (*f)(T1,T2,T3,T4,T5) ) 
{ return function_ptr5<R,T1,T2,T3, T4,T5>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5, class T6> struct function_ptr6 {
    typedef R result_type;
    typedef R (*Func)(T1, T2, T3, T4, T5, T6); 
    Func f_;
    function_ptr6(Func const& f) : f_(f) {}
    function_ptr6(const function_ptr6& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5, class A6>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5), arg_cast<T6>(a6)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) const 
    { return f_(t1, t2, t3, t4, t5, t6); }
};
template<class R, class T1, class T2, class T3, class T4, class T5, class T6>
function_ptr6<R, T1, T2, T3, T4, T5, T6> func_ptr(R (*f)(T1,T2,T3,T4,T5,T6) ) 
{ return function_ptr6<R,T1,T2,T3, T4,T5,T6>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7> struct function_ptr7 {
    typedef R result_type;
    typedef R (*Func)(T1, T2, T3, T4, T5, T6, T7); 
    Func f_;
    function_ptr7(Func const& f) : f_(f) {}
    function_ptr7(const function_ptr7& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5), arg_cast<T6>(a6), arg_cast<T7>(a7)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7) const 
    { return f_(t1, t2, t3, t4, t5, t6, t7); }
};
template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
function_ptr7<R, T1, T2, T3, T4, T5, T6, T7> func_ptr(R (*f)(T1,T2,T3,T4,T5,T6,T7) ) 
{ return function_ptr7<R,T1,T2,T3, T4,T5,T6, T7>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8> struct function_ptr8 {
    typedef R result_type;
    typedef R (*Func)(T1, T2, T3, T4, T5, T6, T7, T8); 
    Func f_;
    function_ptr8(Func const& f) : f_(f) {}
    function_ptr8(const function_ptr8& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5), arg_cast<T6>(a6), arg_cast<T7>(a7), arg_cast<T8>(a8)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8) const 
    { return f_(t1, t2, t3, t4, t5, t6, t7, t8); }
};
template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
function_ptr8<R, T1, T2, T3, T4, T5, T6, T7, T8> func_ptr(R (*f)(T1,T2,T3,T4,T5,T6,T7,T8) ) 
{ return function_ptr8<R,T1,T2,T3, T4,T5,T6, T7, T8>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9> struct function_ptr9 {
    typedef R result_type;
    typedef R (*Func)(T1, T2, T3, T4, T5, T6, T7, T8, T9); 
    Func f_;
    function_ptr9(Func const& f) : f_(f) {}
    function_ptr9(const function_ptr9& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5), arg_cast<T6>(a6), arg_cast<T7>(a7), arg_cast<T8>(a8), arg_cast<T9>(a9)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9) const 
    { return f_(t1, t2, t3, t4, t5, t6, t7, t8, t9); }
};
template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
function_ptr9<R, T1, T2, T3, T4, T5, T6, T7, T8, T9> func_ptr(R (*f)(T1,T2,T3,T4,T5,T6,T7,T8,T9) ) 
{ return function_ptr9<R,T1,T2,T3, T4,T5,T6, T7, T8, T9>(f); }

/////////////////////////////////////////////////////////////////////////////
//std call
#ifdef WIN32
#define CBAPI __stdcall

template<class R>
struct function_ptr_cbapi0{
    typedef R result_type;
    typedef R (CBAPI *Func)(void);
    Func f_;

    function_ptr_cbapi0(Func const &f) : f_(f) { }
    function_ptr_cbapi0(const function_ptr0& f) : f_(f.f_) {} 

    result_type operator()() const {
        return f_();
    }
};
template<class R>
function_ptr_cbapi0<R> func_ptr(R(CBAPI *f)(void)) {
    return function_ptr_cbapi0<R>(f);
}

template<class R, class T1> struct function_ptr_cbapi1 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1); 
    Func f_;
    function_ptr_cbapi1(Func const& f) : f_(f) {}
    function_ptr_cbapi1(const function_ptr_cbapi1& f) : f_(f.f_) {}
    template<class A1>
    result_type operator()(A1 a1) const 
    { return f_(arg_cast<T1>(a1)) ; }
    result_type operator()(T1 t1) const 
    { return f_(t1); }
};
template<class R, class T1>
function_ptr_cbapi1<R, T1> func_ptr(R (CBAPI *f)(T1) ) 
{ return function_ptr_cbapi1<R, T1>(f); }

template<class R, class T1, class T2> struct function_ptr_cbapi2 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1,T2); 
    Func f_;
    function_ptr_cbapi2(Func const& f) : f_(f) {}
    function_ptr_cbapi2(const function_ptr_cbapi2& f) : f_(f.f_) {}
    template<class A1, class A2>
    result_type operator()(A1 a1, A2 a2) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2)) ; }
    result_type operator()(T1 t1, T2 t2) const
    { return f_(t1, t2); }
};
template<class R, class T1, class T2>
function_ptr_cbapi2<R, T1, T2> func_ptr(R (CBAPI *f)(T1,T2) ) 
{ return function_ptr_cbapi2<R, T1,T2>(f); }

template<class R, class T1, class T2, class T3> struct function_ptr_cbapi3 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1,T2,T3); 
    Func f_;
    function_ptr_cbapi3(Func const& f) : f_(f) {}
    function_ptr_cbapi3(const function_ptr_cbapi3& f) : f_(f.f_) {}
    template<class A1, class A2, class A3>
    result_type operator()(A1 a1, A2 a2, A3 a3) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3) const 
    { return f_(t1, t2, t3); }
};
template<class R, class T1, class T2, class T3>
function_ptr_cbapi3<R, T1, T2, T3> func_ptr(R (CBAPI *f)(T1,T2,T3) ) 
{ return function_ptr_cbapi3<R,T1,T2,T3>(f); }

template<class R, class T1, class T2, class T3, class T4> struct function_ptr_cbapi4 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1, T2, T3, T4); 
    Func f_;
    function_ptr_cbapi4(Func const& f) : f_(f) {}
    function_ptr_cbapi4(const function_ptr_cbapi4& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4) const 
    { return f_(t1, t2, t3, t4); }
};
template<class R, class T1, class T2, class T3, class T4>
function_ptr_cbapi4<R, T1, T2, T3, T4> func_ptr(R (CBAPI *f)(T1,T2,T3,T4) ) 
{ return function_ptr_cbapi4<R,T1,T2,T3, T4>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5> struct function_ptr_cbapi5 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1, T2, T3, T4, T5); 
    Func f_;
    function_ptr_cbapi5(Func const& f) : f_(f) {}
    function_ptr_cbapi5(const function_ptr_cbapi5& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) const 
    { return f_(t1, t2, t3, t4, t5); }
};
template<class R, class T1, class T2, class T3, class T4, class T5>
function_ptr_cbapi5<R, T1, T2, T3, T4, T5> func_ptr(R (CBAPI *f)(T1,T2,T3,T4,T5) ) 
{ return function_ptr_cbapi5<R,T1,T2,T3, T4,T5>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5, class T6> struct function_ptr_cbapi6 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1, T2, T3, T4, T5, T6); 
    Func f_;
    function_ptr_cbapi6(Func const& f) : f_(f) {}
    function_ptr_cbapi6(const function_ptr_cbapi6& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5, class A6>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5), arg_cast<T6>(a6)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) const 
    { return f_(t1, t2, t3, t4, t5, t6); }
};
template<class R, class T1, class T2, class T3, class T4, class T5, class T6>
function_ptr_cbapi6<R, T1, T2, T3, T4, T5, T6> func_ptr(R (CBAPI *f)(T1,T2,T3,T4,T5,T6) ) 
{ return function_ptr_cbapi6<R,T1,T2,T3, T4,T5,T6>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7> struct function_ptr_cbapi7 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1, T2, T3, T4, T5, T6, T7); 
    Func f_;
    function_ptr_cbapi7(Func const& f) : f_(f) {}
    function_ptr_cbapi7(const function_ptr_cbapi7& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5), arg_cast<T6>(a6), arg_cast<T7>(a7)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7) const 
    { return f_(t1, t2, t3, t4, t5, t6, t7); }
};
template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
function_ptr_cbapi7<R, T1, T2, T3, T4, T5, T6, T7> func_ptr(R (CBAPI *f)(T1,T2,T3,T4,T5,T6,T7) ) 
{ return function_ptr_cbapi7<R,T1,T2,T3, T4,T5,T6, T7>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8> struct function_ptr_cbapi8 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1, T2, T3, T4, T5, T6, T7, T8); 
    Func f_;
    function_ptr_cbapi8(Func const& f) : f_(f) {}
    function_ptr_cbapi8(const function_ptr_cbapi8& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5), arg_cast<T6>(a6), arg_cast<T7>(a7), arg_cast<T8>(a8)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8) const 
    { return f_(t1, t2, t3, t4, t5, t6, t7, t8); }
};
template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
function_ptr_cbapi8<R, T1, T2, T3, T4, T5, T6, T7, T8> func_ptr(R (CBAPI *f)(T1,T2,T3,T4,T5,T6,T7,T8) ) 
{ return function_ptr_cbapi8<R,T1,T2,T3, T4,T5,T6, T7, T8>(f); }

template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9> struct function_ptr_cbapi9 {
    typedef R result_type;
    typedef R (CBAPI *Func)(T1, T2, T3, T4, T5, T6, T7, T8, T9); 
    Func f_;
    function_ptr_cbapi9(Func const& f) : f_(f) {}
    function_ptr_cbapi9(const function_ptr_cbapi9& f) : f_(f.f_) {}
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const 
    { return f_(arg_cast<T1>(a1), arg_cast<T2>(a2), arg_cast<T3>(a3), arg_cast<T4>(a4), arg_cast<T5>(a5), arg_cast<T6>(a6), arg_cast<T7>(a7), arg_cast<T8>(a8), arg_cast<T9>(a9)) ; }
    result_type operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9) const 
    { return f_(t1, t2, t3, t4, t5, t6, t7, t8, t9); }
};
template<class R, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
function_ptr_cbapi9<R, T1, T2, T3, T4, T5, T6, T7, T8, T9> func_ptr(R (CBAPI *f)(T1,T2,T3,T4,T5,T6,T7,T8,T9) ) 
{ return function_ptr_cbapi9<R,T1,T2,T3, T4,T5,T6, T7, T8, T9>(f); }
#endif
///////////////////////////////////////////////////////////////

//member function ptr
template<class R, class X>
struct method_function0 {
    typedef R(X::*method)(void);
    typedef R result_type;
    method method_;
    method_function0(method const& m) : method_(m) { }
    method_function0(method_function0 const& t) : method_(t.method_) { }
    R operator()(X *x)const {
        return (x->*method_)();
    }
    R operator()(X & x) const {
        return (x.*method_)();
    }
};
template<class R, class X>
struct method_const_function0 {
    typedef R (X::*method)(void) const;
    typedef R result_type;
    method method_;
    method_const_function0(method const& m) : method_(m) { }
    method_const_function0(method_const_function0 const& m) : method_(m.method_) { }
    R operator()(X const *x)const {
        return (x->*method_)();
    }
    R operator()(X const & x) const {
        return (x.*method_)();
    }
};
template<class R, class X>
method_function0<R,X> method_ptr(R(X::*f)()) {
    return method_function0<R,X>(f);
}
template<class R, class X>
method_const_function0<R,X> method_ptr(R(X::*f)() const) {
    return method_const_function0<R,X>(f);
}
template<class R, class X, class T1> struct method_function1 {
    typedef R(X::*method)(T1);
    typedef R result_type;
    method method_;
    method_function1(method const& m) : method_(m) { }
    method_function1(method_function1 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1> struct method_const_function1 {
    typedef R(X::*method)(T1) const;
    typedef R result_type;
    method method_;
    method_const_function1(method const& m) : method_(m) { }
    method_const_function1(method_const_function1 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1> method_function1<R,X,T1> method_ptr(R(X::*f)(T1))
{ return method_function1<R,X,T1>(f); }
template<class R, class X, class T1> method_const_function1<R,X,T1> method_ptr(R(X::*f)(T1)const)
{ return method_const_function1<R,X,T1>(f); }


template<class R, class X, class T1, class T2> struct method_function2 {
    typedef R(X::*method)(T1, T2);
    typedef R result_type;
    method method_;
    method_function2(method const& m) : method_(m) { }
    method_function2(method_function2 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2> struct method_const_function2 {
    typedef R(X::*method)(T1, T2) const;
    typedef R result_type;
    method method_;
    method_const_function2(method const& m) : method_(m) { }
    method_const_function2(method_const_function2 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2> method_function2<R,X,T1, T2> method_ptr(R(X::*f)(T1, T2))
{ return method_function2<R,X,T1, T2>(f); }
template<class R, class X, class T1, class T2> method_const_function2<R,X,T1, T2> method_ptr(R(X::*f)(T1, T2)const)
{ return method_const_function2<R,X,T1, T2>(f); }


template<class R, class X, class T1, class T2, class T3> struct method_function3 {
    typedef R(X::*method)(T1, T2, T3);
    typedef R result_type;
    method method_;
    method_function3(method const& m) : method_(m) { }
    method_function3(method_function3 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3> struct method_const_function3 {
    typedef R(X::*method)(T1, T2, T3) const;
    typedef R result_type;
    method method_;
    method_const_function3(method const& m) : method_(m) { }
    method_const_function3(method_const_function3 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3> method_function3<R,X,T1, T2, T3> method_ptr(R(X::*f)(T1, T2, T3))
{ return method_function3<R,X,T1, T2, T3>(f); }
template<class R, class X, class T1, class T2, class T3> method_const_function3<R,X,T1, T2, T3> method_ptr(R(X::*f)(T1, T2, T3)const)
{ return method_const_function3<R,X,T1, T2, T3>(f); }


template<class R, class X, class T1, class T2, class T3, class T4> struct method_function4 {
    typedef R(X::*method)(T1, T2, T3, T4);
    typedef R result_type;
    method method_;
    method_function4(method const& m) : method_(m) { }
    method_function4(method_function4 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4> struct method_const_function4 {
    typedef R(X::*method)(T1, T2, T3, T4) const;
    typedef R result_type;
    method method_;
    method_const_function4(method const& m) : method_(m) { }
    method_const_function4(method_const_function4 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4> method_function4<R,X,T1, T2, T3, T4> method_ptr(R(X::*f)(T1, T2, T3, T4))
{ return method_function4<R,X,T1, T2, T3, T4>(f); }
template<class R, class X, class T1, class T2, class T3, class T4> method_const_function4<R,X,T1, T2, T3, T4> method_ptr(R(X::*f)(T1, T2, T3, T4)const)
{ return method_const_function4<R,X,T1, T2, T3, T4>(f); }


template<class R, class X, class T1, class T2, class T3, class T4, class T5> struct method_function5 {
    typedef R(X::*method)(T1, T2, T3, T4, T5);
    typedef R result_type;
    method method_;
    method_function5(method const& m) : method_(m) { }
    method_function5(method_function5 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5> struct method_const_function5 {
    typedef R(X::*method)(T1, T2, T3, T4, T5) const;
    typedef R result_type;
    method method_;
    method_const_function5(method const& m) : method_(m) { }
    method_const_function5(method_const_function5 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5> method_function5<R,X,T1, T2, T3, T4, T5> method_ptr(R(X::*f)(T1, T2, T3, T4, T5))
{ return method_function5<R,X,T1, T2, T3, T4, T5>(f); }
template<class R, class X, class T1, class T2, class T3, class T4, class T5> method_const_function5<R,X,T1, T2, T3, T4, T5> method_ptr(R(X::*f)(T1, T2, T3, T4, T5)const)
{ return method_const_function5<R,X,T1, T2, T3, T4, T5>(f); }


template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6> struct method_function6 {
    typedef R(X::*method)(T1, T2, T3, T4, T5, T6);
    typedef R result_type;
    method method_;
    method_function6(method const& m) : method_(m) { }
    method_function6(method_function6 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6> struct method_const_function6 {
    typedef R(X::*method)(T1, T2, T3, T4, T5, T6) const;
    typedef R result_type;
    method method_;
    method_const_function6(method const& m) : method_(m) { }
    method_const_function6(method_const_function6 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6> method_function6<R,X,T1, T2, T3, T4, T5, T6> method_ptr(R(X::*f)(T1, T2, T3, T4, T5, T6))
{ return method_function6<R,X,T1, T2, T3, T4, T5, T6>(f); }
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6> method_const_function6<R,X,T1, T2, T3, T4, T5, T6> method_ptr(R(X::*f)(T1, T2, T3, T4, T5, T6)const)
{ return method_const_function6<R,X,T1, T2, T3, T4, T5, T6>(f); }


template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7> struct method_function7 {
    typedef R(X::*method)(T1, T2, T3, T4, T5, T6, T7);
    typedef R result_type;
    method method_;
    method_function7(method const& m) : method_(m) { }
    method_function7(method_function7 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7> struct method_const_function7 {
    typedef R(X::*method)(T1, T2, T3, T4, T5, T6, T7) const;
    typedef R result_type;
    method method_;
    method_const_function7(method const& m) : method_(m) { }
    method_const_function7(method_const_function7 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7> method_function7<R,X,T1, T2, T3, T4, T5, T6, T7> method_ptr(R(X::*f)(T1, T2, T3, T4, T5, T6, T7))
{ return method_function7<R,X,T1, T2, T3, T4, T5, T6, T7>(f); }
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7> method_const_function7<R,X,T1, T2, T3, T4, T5, T6, T7> method_ptr(R(X::*f)(T1, T2, T3, T4, T5, T6, T7)const)
{ return method_const_function7<R,X,T1, T2, T3, T4, T5, T6, T7>(f); }


template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8> struct method_function8 {
    typedef R(X::*method)(T1, T2, T3, T4, T5, T6, T7, T8);
    typedef R result_type;
    method method_;
    method_function8(method const& m) : method_(m) { }
    method_function8(method_function8 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8> struct method_const_function8 {
    typedef R(X::*method)(T1, T2, T3, T4, T5, T6, T7, T8) const;
    typedef R result_type;
    method method_;
    method_const_function8(method const& m) : method_(m) { }
    method_const_function8(method_const_function8 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8> method_function8<R,X,T1, T2, T3, T4, T5, T6, T7, T8> method_ptr(R(X::*f)(T1, T2, T3, T4, T5, T6, T7, T8))
{ return method_function8<R,X,T1, T2, T3, T4, T5, T6, T7, T8>(f); }
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8> method_const_function8<R,X,T1, T2, T3, T4, T5, T6, T7, T8> method_ptr(R(X::*f)(T1, T2, T3, T4, T5, T6, T7, T8)const)
{ return method_const_function8<R,X,T1, T2, T3, T4, T5, T6, T7, T8>(f); }


template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9> struct method_function9 {
    typedef R(X::*method)(T1, T2, T3, T4, T5, T6, T7, T8, T9);
    typedef R result_type;
    method method_;
    method_function9(method const& m) : method_(m) { }
    method_function9(method_function9 const& m): method_(m.method_) { }
    R operator()(X* x) const
    { return (x->*method_)(); }
    R operator()(X& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9> struct method_const_function9 {
    typedef R(X::*method)(T1, T2, T3, T4, T5, T6, T7, T8, T9) const;
    typedef R result_type;
    method method_;
    method_const_function9(method const& m) : method_(m) { }
    method_const_function9(method_const_function9 const& m): method_(m.method_) { }
    R operator()(X const* x) const
    { return (x->*method_)(); }
    R operator()(X const& x) const
    { return (x.*method_)(); }
};
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9> method_function9<R,X,T1, T2, T3, T4, T5, T6, T7, T8, T9> method_ptr(R(X::*f)(T1, T2, T3, T4, T5, T6, T7, T8, T9))
{ return method_function9<R,X,T1, T2, T3, T4, T5, T6, T7, T8, T9>(f); }
template<class R, class X, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9> method_const_function9<R,X,T1, T2, T3, T4, T5, T6, T7, T8, T9> method_ptr(R(X::*f)(T1, T2, T3, T4, T5, T6, T7, T8, T9)const)
{ return method_const_function9<R,X,T1, T2, T3, T4, T5, T6, T7, T8, T9>(f); }


}

#endif