#ifndef CQ_LIST_H
#define CQ_LIST_H

#include "cqholder.h"

namespace cppquery {

template<class F, class L> struct function_t;

template<class L>
struct list_t { 
	typedef L driver_type; 
	driver_type & driver() {
		return *(static_cast<driver_type*>(this));
	}
	driver_type const& driver() const {
		return *(static_cast<const driver_type*>(this));
	}
};

struct list0 : public list_t<list0>
{
	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f();
	}

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<class T>
	bool checkArg(const T& ) const { return true; }
	template<class T>
	bool isElementHolderInList(const list_t<T>& l) const { return true; }
};

#define FUNCTION_NEST_CALL \
	template<class F, class L> \
	typename function_t<F,L>::result_type operator[](const function_t<F, L> & f) const{ \
		return f.l_(f.f_, *this); \
	}  \
	template<int const INDEX, class T, class F> \
	ArgWrapper<INDEX, T> operator[](const ArgWrapperBinder<INDEX, T, F>&  f) const { \
		return ArgWrapper<INDEX,T>(T((*this)[f.f_])); \
	}



template<class T1>
struct list1 : public list_t<list1<T1> >
{
	T1 t1;

	list1(T1 const &t1) :t1(t1) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }

	FUNCTION_NEST_CALL

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T> const &holder) const {
		T t;
		if(holder.checkAndGet(t1, t))
			return t;
		return T_NULL(T);
	}

	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}
	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) ;
	}
	

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); }

};

template<class T1, class T2>
struct list2 : public list_t<list2<T1,T2> >
{
	T1 t1;
	T2 t2;
	list2(T1 const& t1, T2 const& t2) : t1(t1), t2(t2) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t))
			return t;
		return T_NULL(T);
	}

	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1) 
			|| holder.checkArg(t2);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1)
			|| holder.checkArg(t2);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}
	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) && l.driver().checkArg(t2);
	}
	

	FUNCTION_NEST_CALL

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); }
};

template<class T1, class T2, class T3>
struct list3 : public list_t<list3<T1,T2,T3> >
{
	T1 t1;
	T2 t2;
	T3 t3;
	list3(T1 const& t1, T2 const& t2, T3 const& t3) : t1(t1), t2(t2), t3(t3) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }
	T3 operator[] (ArgIndexHolder<3> const&) const { return t3; }

	FUNCTION_NEST_CALL

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1) 
			|| holder.checkArg(t2)
			|| holder.checkArg(t3);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1)
			|| holder.checkArg(t2)
			|| holder.checkArg(t3);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}

	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) 
			&& l.driver().checkArg(t2) 
			&& l.driver().checkArg(t3);
	}
	
	
	template<class T>
	T operator[] (T const &t) const { return t; }

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2], l[t3]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); f(t3); }

};

template<class T1, class T2, class T3, class T4>
struct list4 : public list_t<list4<T1, T2, T3, T4> >
{
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	list4(T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4) : t1(t1), t2(t2), t3(t3), t4(t4) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }
	T3 operator[] (ArgIndexHolder<3> const&) const { return t3; }
	T4 operator[] (ArgIndexHolder<4> const&) const { return t4; }

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t)
			|| holder.checkAndGet(t4, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1) 
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1)
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}

	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) 
			&& l.driver().checkArg(t2) 
			&& l.driver().checkArg(t3)
			&& l.driver().checkArg(t4);
	}
	
	
	FUNCTION_NEST_CALL

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2], l[t3], l[t4]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); f(t3); f(t4);}
};

template<class T1, class T2, class T3, class T4, class T5>
struct list5 : public list_t<list5<T1,T2,T3,T4,T5> >
{
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	list5(T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5) : t1(t1), t2(t2), t3(t3), t4(t4), t5(t5) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }
	T3 operator[] (ArgIndexHolder<3> const&) const { return t3; }
	T4 operator[] (ArgIndexHolder<4> const&) const { return t4; }
	T5 operator[] (ArgIndexHolder<5> const&) const { return t5; }

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t)
			|| holder.checkAndGet(t4, t)
			|| holder.checkAndGet(t5, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1) 
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1)
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}

	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) 
			&& l.driver().checkArg(t2) 
			&& l.driver().checkArg(t3)
			&& l.driver().checkArg(t4)
			&& l.driver().checkArg(t5);
	}
	
	FUNCTION_NEST_CALL

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2], l[t3], l[t4], l[t5]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); f(t3); f(t4); f(t5); }
};

template<class T1, class T2, class T3, class T4, class T5, class T6>
struct list6 : public list_t<list6<T1, T2, T3, T4, T5, T6> >
{
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	T6 t6;
	list6(T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6) : t1(t1), t2(t2), t3(t3), t4(t4), t5(t5), t6(t6) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }
	T3 operator[] (ArgIndexHolder<3> const&) const { return t3; }
	T4 operator[] (ArgIndexHolder<4> const&) const { return t4; }
	T5 operator[] (ArgIndexHolder<5> const&) const { return t5; }
	T6 operator[] (ArgIndexHolder<6> const&) const { return t6; }

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t)
			|| holder.checkAndGet(t4, t)
			|| holder.checkAndGet(t5, t)
			|| holder.checkAndGet(t6, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1) 
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5)
			|| holder.checkArg(t6);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1)
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5)
			|| holder.checkArg(t6);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}

	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) 
			&& l.driver().checkArg(t2) 
			&& l.driver().checkArg(t3)
			&& l.driver().checkArg(t4)
			&& l.driver().checkArg(t5)
			&& l.driver().checkArg(t6);
	}
	
	
	FUNCTION_NEST_CALL

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2], l[t3], l[t4], l[t5], l[t6]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); f(t3); f(t4); f(t5); f(t6);}
};

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
struct list7 : public list_t<list7<T1,T2,T3,T4,T5,T6,T7> >
{
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	T6 t6;
	T7 t7;
	list7(T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7) 
	: t1(t1), t2(t2), t3(t3), t4(t4), t5(t5), t6(t6) , t7(t7){ }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }
	T3 operator[] (ArgIndexHolder<3> const&) const { return t3; }
	T4 operator[] (ArgIndexHolder<4> const&) const { return t4; }
	T5 operator[] (ArgIndexHolder<5> const&) const { return t5; }
	T6 operator[] (ArgIndexHolder<6> const&) const { return t6; }
	T7 operator[] (ArgIndexHolder<7> const&) const { return t7; }

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t)
			|| holder.checkAndGet(t4, t)
			|| holder.checkAndGet(t5, t)
			|| holder.checkAndGet(t6, t)
			|| holder.checkAndGet(t7, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1) 
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5)
			|| holder.checkArg(t6)
			|| holder.checkArg(t7);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1)
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5)
			|| holder.checkArg(t6)
			|| holder.checkArg(t7);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}

	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) 
			&& l.driver().checkArg(t2) 
			&& l.driver().checkArg(t3)
			&& l.driver().checkArg(t4)
			&& l.driver().checkArg(t5)
			&& l.driver().checkArg(t6)
			&& l.driver().checkArg(t7);
	}
	
	
	FUNCTION_NEST_CALL

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2], l[t3], l[t4], l[t5], l[t6], l[t7]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); f(t3); f(t4); f(t5); f(t6); f(t7);}
};


template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
struct list8: public list_t<list8<T1,T2,T3,T4,T5,T6,T7,T8> >
{
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	T6 t6;
	T7 t7;
	T8 t8;
	list8(T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8 ) 
	: t1(t1), t2(t2), t3(t3), t4(t4), t5(t5), t6(t6) , t7(t7), t8(t8) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }
	T3 operator[] (ArgIndexHolder<3> const&) const { return t3; }
	T4 operator[] (ArgIndexHolder<4> const&) const { return t4; }
	T5 operator[] (ArgIndexHolder<5> const&) const { return t5; }
	T6 operator[] (ArgIndexHolder<6> const&) const { return t6; }
	T7 operator[] (ArgIndexHolder<7> const&) const { return t7; }
	T8 operator[] (ArgIndexHolder<8> const&) const { return t8; }

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t)
			|| holder.checkAndGet(t4, t)
			|| holder.checkAndGet(t5, t)
			|| holder.checkAndGet(t6, t)
			|| holder.checkAndGet(t7, t)
			|| holder.checkAndGet(t8, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1) 
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5)
			|| holder.checkArg(t6)
			|| holder.checkArg(t7)
			|| holder.checkArg(t8);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1)
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5)
			|| holder.checkArg(t6)
			|| holder.checkArg(t7)
			|| holder.checkArg(t8);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}

	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) 
			&& l.driver().checkArg(t2) 
			&& l.driver().checkArg(t3)
			&& l.driver().checkArg(t4)
			&& l.driver().checkArg(t5)
			&& l.driver().checkArg(t6)
			&& l.driver().checkArg(t7)
			&& l.driver().checkArg(t8);
	}
	
	
	FUNCTION_NEST_CALL

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2], l[t3], l[t4], l[t5], l[t6], l[t7], l[t8]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); f(t3); f(t4); f(t5); f(t6); f(t7); f(t8); }
};

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
struct list9 : public list_t<list9<T1,T2,T3,T4,T5,T6,T7,T8,T9> >
{
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	T6 t6;
	T7 t7;
	T8 t8;
	T9 t9;
	list9(T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8 , T9 const& t9) 
	: t1(t1), t2(t2), t3(t3), t4(t4), t5(t5), t6(t6) , t7(t7), t8(t8), t9(t9) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }
	T3 operator[] (ArgIndexHolder<3> const&) const { return t3; }
	T4 operator[] (ArgIndexHolder<4> const&) const { return t4; }
	T5 operator[] (ArgIndexHolder<5> const&) const { return t5; }
	T6 operator[] (ArgIndexHolder<6> const&) const { return t6; }
	T7 operator[] (ArgIndexHolder<7> const&) const { return t7; }
	T8 operator[] (ArgIndexHolder<8> const&) const { return t8; }
	T9 operator[] (ArgIndexHolder<9> const&) const { return t9; }

	template<class T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, class T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t)
			|| holder.checkAndGet(t4, t)
			|| holder.checkAndGet(t5, t)
			|| holder.checkAndGet(t6, t)
			|| holder.checkAndGet(t7, t)
			|| holder.checkAndGet(t8, t)
			|| holder.checkAndGet(t9, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& holder) const {
		return holder.checkArg(t1) 
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5)
			|| holder.checkArg(t6)
			|| holder.checkArg(t7)
			|| holder.checkArg(t8)
			|| holder.checkArg(t9);
	}
	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const& holder) const {
		return holder.checkArg(t1)
			|| holder.checkArg(t2)
			|| holder.checkArg(t3)
			|| holder.checkArg(t4)
			|| holder.checkArg(t5)
			|| holder.checkArg(t6)
			|| holder.checkArg(t7)
			|| holder.checkArg(t8)
			|| holder.checkArg(t9);
	}
	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}

	template<class TList>
	bool isElementHolderInList(const list_t<TList>& l) const {
		return l.driver().checkArg(t1) 
			&& l.driver().checkArg(t2) 
			&& l.driver().checkArg(t3)
			&& l.driver().checkArg(t4)
			&& l.driver().checkArg(t5)
			&& l.driver().checkArg(t6)
			&& l.driver().checkArg(t7)
			&& l.driver().checkArg(t8)
			&& l.driver().checkArg(t9);
	}
	
	
	FUNCTION_NEST_CALL

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2], l[t3], l[t4], l[t5], l[t6], l[t7], l[t8], l[t9]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); f(t3); f(t4); f(t5); f(t6); f(t7); f(t8); f(t9);}

};

template<class T1>
list1<T1> make_list(T1 const &t1) {
	return list1<T1>(t1);
}

template<class T1, class T2>
list2<T1, T2> make_list(T1 const &t1, T2 const &t2) {
	return list2<T1,T2>(t1, t2);
}

template<class T1, class T2, class T3>
list3<T1, T2, T3> make_list(T1 const &t1, T2 const &t2, T3 const &t3) {
	return list3<T1,T2,T3>(t1, t2, t3);
}

template<class T1, class T2, class T3, class T4>
list4<T1, T2, T3, T4> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4) {
	return list4<T1,T2,T3, T4>(t1, t2, t3, t4);
}

template<class T1, class T2, class T3, class T4, class T5>
list5<T1, T2, T3, T4, T5> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5) {
	return list5<T1,T2,T3, T4, T5>(t1, t2, t3, t4, t5);
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
list6<T1, T2, T3, T4, T5, T6> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5, T6 const& t6) {
	return list6<T1,T2,T3, T4, T5, T6>(t1, t2, t3, t4, t5, t6);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
list7<T1, T2, T3, T4, T5, T6, T7> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7) {
	return list7<T1,T2,T3, T4, T5, T6, T7>(t1, t2, t3, t4, t5, t6, t7);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
list8<T1, T2, T3, T4, T5, T6, T7, T8> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8) {
	return list8<T1,T2,T3, T4, T5, T6, T7, T8>(t1, t2, t3, t4, t5, t6, t7, t8);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
list9<T1, T2, T3, T4, T5, T6, T7, T8, T9> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9) {
	return list9<T1,T2,T3, T4, T5, T6, T7, T8, T9>(t1, t2, t3, t4, t5, t6, t7, t8, t9);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//Dynamic List Type, used for dynamic call
struct dynamic_list : public list_t<dynamic_list>{
	struct item {
		virtual int getId() const = 0;
		virtual const std::type_info& type() const = 0;
		virtual void* value()  = 0;
	};
	typedef item* p_item;
	int size_;

	template<int const IDX, class T>
	struct value_item : public item {
		T value_;
		value_item(const T& t) : value_(t) { }
		int getId() const { return IDX; }
		const std::type_info& type() const { return typeid(T); }
		void *value() { return &value_;}
	};

	struct item_wrapper {
		const item * pitem_;
		item_wrapper(const item* i) :pitem_(i){ }
		item_wrapper(const item_wrapper& i) : pitem_(i.pitem_){ }

		template<typename A>
		operator A () const {
			if(pitem_ && typeid(A) == pitem_->type()) {
				return *(A*)(const_cast<item*>(pitem_)->value());
			}
			return T_NULL(A);
		}
	};

	template<int const IDX, class T>
	static inline item* make_value(const ArgWrapper<IDX, T>& v) {
		return new value_item<IDX, T>(v.value());
	}
	template<class T>
	static inline item* make_value(const T& v) {
		return new value_item<-1, T>(v);
	}

	p_item *items_;

	dynamic_list() 
   	:size_(0)
	,items_(NULL){
	}
	void init(int size) {
		size_ = size;
		if(size > 0) {
			items_ = new p_item[size_];
			memset(items_, 0, sizeof(p_item)*size_);
		}
		else {
			items_ = NULL;
		}
	}

	template<class A1> dynamic_list(list1<A1> const& l)
	{ init(1); set(l);}
	template<class A1> dynamic_list(A1 const& a1)
	{ init(1); set(a1);}

	template<class A1, class A2> dynamic_list(list2<A1, A2> const& l)
	{ init(1); set(l);}
	template<class A1, class A2> dynamic_list(A1 const& a1, A2 const& a2)
	{ init(1); set(a1, a2);}

	template<class A1, class A2, class A3> dynamic_list(list3<A1, A2, A3> const& l)
	{ init(1); set(l);}
	template<class A1, class A2, class A3> dynamic_list(A1 const& a1, A2 const& a2, A3 const& a3)
	{ init(1); set(a1, a2, a3);}

	template<class A1, class A2, class A3, class A4> dynamic_list(list4<A1, A2, A3, A4> const& l)
	{ init(1); set(l);}
	template<class A1, class A2, class A3, class A4> dynamic_list(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
	{ init(1); set(a1, a2, a3, a4);}

	template<class A1, class A2, class A3, class A4, class A5> dynamic_list(list5<A1, A2, A3, A4, A5> const& l)
	{ init(1); set(l);}
	template<class A1, class A2, class A3, class A4, class A5> dynamic_list(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
	{ init(1); set(a1, a2, a3, a4, a5);}

	template<class A1, class A2, class A3, class A4, class A5, class A6> dynamic_list(list6<A1, A2, A3, A4, A5, A6> const& l)
	{ init(1); set(l);}
	template<class A1, class A2, class A3, class A4, class A5, class A6> dynamic_list(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
	{ init(1); set(a1, a2, a3, a4, a5, a6);}

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> dynamic_list(list7<A1, A2, A3, A4, A5, A6, A7> const& l)
	{ init(1); set(l);}
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> dynamic_list(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
	{ init(1); set(a1, a2, a3, a4, a5, a6, a7);}

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> dynamic_list(list8<A1, A2, A3, A4, A5, A6, A7, A8> const& l)
	{ init(1); set(l);}
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> dynamic_list(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
	{ init(1); set(a1, a2, a3, a4, a5, a6, a7, a8);}

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> dynamic_list(list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> const& l)
	{ init(1); set(l);}
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> dynamic_list(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
	{ init(1); set(a1, a2, a3, a4, a5, a6, a7, a8, a9);}


	bool tryClear(int n){
		if(!items_ || n >= size_) return false;
		if(items_[n]) delete items_[n];
		return true;
	}

	template<class A1> bool set(A1 const& a1) 
	{ if(tryClear(0))	items_[0] = make_value(a1);	return true; }
	template<class A1> bool set(list1<A1> const& l) 
	{ return set(l.a1); }

	template<class A1, class A2> bool set(A1 const& a1, A2 const& a2) 
	{ return set(a1) ? (tryClear(1) ? (items_[1] = make_value(a2), true) : false ) : false; }
	template<class A1, class A2> bool set(list2<A1, A2> const& l) 
	{ return set(l.a1, l.a2); }

	template<class A1, class A2, class A3> bool set(A1 const& a1, A2 const& a2, A3 const& a3) 
	{ return set(a1, a2) ? (tryClear(2) ? (items_[2] = make_value(a3), true) : false ) : false; }
	template<class A1, class A2, class A3> bool set(list3<A1, A2, A3> const& l) 
	{ return set(l.a1, l.a2, l.a3); }

	template<class A1, class A2, class A3, class A4> bool set(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4) 
	{ return set(a1, a2, a3) ? (tryClear(3) ? (items_[3] = make_value(a4), true) : false ) : false; }
	template<class A1, class A2, class A3, class A4> bool set(list4<A1, A2, A3, A4> const& l) 
	{ return set(l.a1, l.a2, l.a3, l.a4); }

	template<class A1, class A2, class A3, class A4, class A5> bool set(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5) 
	{ return set(a1, a2, a3, a4) ? (tryClear(4) ? (items_[4] = make_value(a5), true) : false ) : false; }
	template<class A1, class A2, class A3, class A4, class A5> bool set(list5<A1, A2, A3, A4, A5> const& l) 
	{ return set(l.a1, l.a2, l.a3, l.a4, l.a5); }

	template<class A1, class A2, class A3, class A4, class A5, class A6> bool set(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6) 
	{ return set(a1, a2, a3, a4, a5) ? (tryClear(5) ? (items_[5] = make_value(a6), true) : false ) : false; }
	template<class A1, class A2, class A3, class A4, class A5, class A6> bool set(list6<A1, A2, A3, A4, A5, A6> const& l) 
	{ return set(l.a1, l.a2, l.a3, l.a4, l.a5, l.a6); }

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> bool set(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7) 
	{ return set(a1, a2, a3, a4, a5, a6) ? (tryClear(6) ? (items_[6] = make_value(a7), true) : false ) : false; }
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> bool set(list7<A1, A2, A3, A4, A5, A6, A7> const& l) 
	{ return set(l.a1, l.a2, l.a3, l.a4, l.a5, l.a6, l.a7); }

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> bool set(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8) 
	{ return set(a1, a2, a3, a4, a5, a6, a7) ? (tryClear(7) ? (items_[7] = make_value(a8), true) : false ) : false; }
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> bool set(list8<A1, A2, A3, A4, A5, A6, A7, A8> const& l) 
	{ return set(l.a1, l.a2, l.a3, l.a4, l.a5, l.a6, l.a7, l.a8); }

	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> bool set(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9) 
	{ return set(a1, a2, a3, a4, a5, a6, a7, a9) ? (tryClear(8) ? (items_[8] = make_value(a9), true) : false ) : false; }
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> bool set(list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> const& l) 
	{ return set(l.a1, l.a2, l.a3, l.a4, l.a5, l.a6, l.a7, l.a8, l.a9); }
	
	~dynamic_list() {
		if(!items_) return ;
		for(int i = 0; i < size_; i++)
		{
			if(items_[i])
				delete items_[i];
		}
		delete[] items_;
	}

	template<class T>
	bool set(int idx, T const& t) {
		if(!items_ || idx < 0 || idx >= size_) {
			return false;
		}

		if(items_[idx]) delete items_[idx];
		items_[idx] = make_value(t);
		return true;
	}	

	item* get_item(int idx) const {
		if(!items_) return NULL;
		if(idx >= 0 && idx < size_) {
			if(items_[idx] != NULL)
			{
				return items_[idx];
			}
		}
		else {
			for(int i = 0; i < size_; i++)
			{
				if(items_[i] && items_[i]->getId() == idx)
				{
					return items_[i];
				}
			}
		}
		return NULL;
	}

	template<class T>
	T get(int idx) const{

		item *pi = get_item(idx);
		if(!pi)
			return T_NULL(T);

		if(typeid(T) != pi->type()) {
			//TODO throw
			return T_NULL(T);
		}
		return *(static_cast<T*>(const_cast<item*>(pi)->value()));
	}

	template<class T>
	T operator[](T const& t) const {
		return t; 
	}

	template<int const IDX>
	item_wrapper operator[](ArgIndexHolder<IDX> const&) const {
		return item_wrapper(get_item(IDX));
	}

	template<int const IDX, class T>
	T operator[](ArgHolder<IDX, T> const& ) const {
		return get<T>(IDX);
	}

	template<int const IDX>
	bool checkArg(ArgIndexHolder<IDX> const&) const {
		if(IDX >= 0 && IDX <= size_)
			return items_ && items_[IDX];
		for(int i = 0; i < size_; i++) {
			if(items_[i] && items_[i]->getId() == IDX)
				return true;
		}
		return false;
	}

	template<int const IDX, class T>
	bool checkArg(ArgHolder<IDX, T> const& ) const {
		return checkArg(ArgIndexHolder<IDX>());
	}

	template<class T>
	bool checkArg(T const& t) const {
		return true;
	}

};


}


#endif
