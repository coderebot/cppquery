#ifndef MGQUERY_placeholder_h
#define MGQUERY_placeholder_h
#include <string>
#include <typeinfo>
#include <string.h>

namespace cppquery{
	
#define _W(...) __VA_ARGS__
#define DEF_OP_CALL_8MORE(def_func) \
	def_func(8, \
			_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8), \
			_W(A1,A2,A3, A4, A5, A6, A7, A8), \
			_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8), \
			_W(a1, a2, a3, a4, a5, a6, a7, a8)) \
	def_func(9, \
			_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9), \
			_W(A1,A2,A3, A4, A5, A6, A7, A8, A9), \
			_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9), \
			_W(a1, a2, a3, a4, a5, a6, a7, a8, a9))

#define DEF_OP_CALL_7MORE(def_func) \
	def_func(7, \
			_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7), \
			_W(A1,A2,A3, A4, A5, A6, A7), \
			_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7), \
			_W(a1, a2, a3, a4, a5, a6, a7)) \
	DEF_OP_CALL_8MORE(def_func)

#define DEF_OP_CALL_6MORE(def_func) \
	def_func(6, \
			_W(class A1, class A2, class A3, class A4, class A5, class A6), \
			_W(A1,A2,A3, A4, A5, A6), \
			_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6), \
			_W(a1, a2, a3, a4, a5, a6)) \
	DEF_OP_CALL_7MORE(def_func)

#define DEF_OP_CALL_5MORE(def_func) \
	def_func(5, \
			_W(class A1, class A2, class A3, class A4, class A5), \
			_W(A1,A2,A3, A4, A5), \
			_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), \
			_W(a1, a2, a3, a4, a5)) \
	DEF_OP_CALL_6MORE(def_func)

#define DEF_OP_CALL_4MORE(def_func) \
	def_func(4, \
			_W(class A1, class A2, class A3, class A4), \
			_W(A1,A2,A3, A4), \
			_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4), \
			_W(a1, a2, a3, a4)) \
	DEF_OP_CALL_5MORE(def_func)

#define DEF_OP_CALL_3MORE(def_func) \
	def_func(3, \
			_W(class A1, class A2, class A3), \
			_W(A1,A2,A3), \
			_W(A1 const& a1, A2 const& a2, A3 const& a3), \
			_W(a1, a2, a3)) \
	DEF_OP_CALL_4MORE(def_func)

#define DEF_OP_CALL_2MORE(def_func) \
	def_func(2,\
			_W(class A1, class A2), \
		   	_W(A1,A2), \
			_W(A1 const& a1, A2 const& a2), \
			_W(a1, a2)) \
	DEF_OP_CALL_3MORE(def_func)

#define DEF_OP_CALL_ALL_EX(def_func) \
	def_func(1, \
			class A1, \
			A1, \
			A1 const& a1, \
			a1) \
	DEF_OP_CALL_2MORE(def_func)

template<typename T1, typename T2>
struct ArgCast {
	T1 operator()(T2 & t) const {
		return static_cast<T1>(t);
	}
};

template<>
struct ArgCast<const char*, std::string>
{
	const char* operator()(std::string const& str) const {
		return str.c_str();
	}
};

template<typename T1, typename T2>
struct ArgCast<T1*, T2*> {
	T1 * operator()(T2 *t) const {
		return dynamic_cast<T1*>(t);
	}
};

template<typename T1, typename T2>
static inline T1 arg_cast(T2 & t)
{
	ArgCast<T1,T2> cast;
	return cast(t);
}

template<typename T>
static inline T arg_cast(T const &t) { return t; }

//////////////////////////////////////////////
//Null T
template<typename T>
struct Null {
	static T null() { return T(); } //null t
};
template<>
struct Null<void> { static void null() { }; };

#define DEF_BASIC_NULL(T, ZERO) \
	template<> \
	struct Null<T> { static T null() { return ZERO; } };
DEF_BASIC_NULL(int, 0)
DEF_BASIC_NULL(unsigned int, 0)
DEF_BASIC_NULL(long, 0)
DEF_BASIC_NULL(unsigned long, 0)
DEF_BASIC_NULL(long long, 0l)
DEF_BASIC_NULL(unsigned long long, 0u)
DEF_BASIC_NULL(float, 0.0)
DEF_BASIC_NULL(double, 0.0)
DEF_BASIC_NULL(long double, 0.0)
DEF_BASIC_NULL(char, '\0')
DEF_BASIC_NULL(unsigned char, '\0')
DEF_BASIC_NULL(short, 0)
DEF_BASIC_NULL(unsigned short, 0)

#undef DEF_BASIC_NULL
#define T_NULL(T)  Null<T>::null()

////////////////////////////////////////////////////////////

template<class F, class L> struct function_t;


template<int const INDEX, typename T>
struct ArgWrapper
{
	enum { Index = INDEX };
	T value_;
	typedef T value_type;

	ArgWrapper(T const& v) :value_(v) { }
	ArgWrapper(ArgWrapper const& a) : value_(a.value_) { }

	template<class A> //conversion
	ArgWrapper(ArgWrapper<INDEX, A> const& a) : value_(a.value_) { }

	T& value() { return value_; }
	const T& value() const{ return value_; }

	operator T& () { return value(); }
	operator T const& () const { return value(); }
};

template<int const INDEX, typename T, class F>
struct ArgWrapperBinder
{
	F f_;
	ArgWrapperBinder(F const& f) : f_(f) { }
	ArgWrapperBinder(const ArgWrapperBinder& b) : f_(b.f_){ }

	ArgWrapper<INDEX, T> operator()() const {
		return ArgWrapper<INDEX, T>(f_());
	}

#define DEF_ARG_BINDER_FUNC(N, temp_def_arg_list, temp_arg_list, arg_list, arg_call_list) \
	template<temp_def_arg_list> \
	ArgWrapper<INDEX, T> operator()(arg_list) const { \
		return ArgWrapper<INDEX, T>(f_(arg_call_list)); \
	}

	DEF_OP_CALL_ALL_EX(DEF_ARG_BINDER_FUNC)

#undef DEF_ARG_BINDER_FUNC
};

template<int const INDEX, typename T>
struct ArgHolder
{
	enum { Index = INDEX };
	typedef T value_type;
	typedef ArgWrapper<INDEX,T> wrapper_type;

	ArgWrapper<INDEX, T> operator=(T const& v) const
	{
		return ArgWrapper<INDEX, T>(v);
	}

	ArgWrapper<INDEX,T> operator()(T const& t) const {
		return ArgWrapper<INDEX, T>(t);
	}
	
	//return the reference
	ArgWrapper<INDEX,T*> operator()(T *pt) const {
		return ArgWrapper<INDEX,T*>(pt);
	}

	template<class F>
	ArgWrapperBinder<INDEX, T, F> bind(F const& f) const {
		return ArgWrapperBinder<INDEX, T, F>(f);
	}
	

	template<class A1>
	ArgWrapper<INDEX, T> operator = (A1 const& a1) const {
		return ArgWrapper<INDEX, T>(T(a1));
	}
 
	template<class A1>
	ArgWrapper<INDEX, T> operator()(A1 const& a1) const {
		return ArgWrapper<INDEX, T>(T(a1));
	}

	template<class A1, class A2>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2) const {
		return ArgWrapper<INDEX, T>(T(a1, a2));
	}

	template<class A1, class A2, class A3>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2, A3 const& a3) const {
		return ArgWrapper<INDEX, T>(T(a1, a2));
	}
	
	//TODO .... More


	template<typename UserT>
	bool checkAndGet(UserT const &v, T & t) const {
		return false;
	}

	template<typename AWT>
	bool checkAndGet(ArgWrapper<INDEX, AWT> const &aw, T &t) const
	{
		t = arg_cast<T>(aw.value());
		return true;
	}

	template<typename UserT>
	bool checkArg(UserT const& v) const {
		return false;
	}
	template<typename AWT>
	bool checkArg(ArgWrapper<INDEX, AWT> const& ) const {
		return true;
	}
};

template<int const INDEX, int const SUBINDEX, typename T>
struct ArgHolderWrapper
{
	enum {Index = INDEX} ;
	typedef ArgHolder<SUBINDEX, T>  sub_holder;

	typename sub_holder::wrapper_type operator=(T const& t) const {
		return sub_holder (t);
	}

	typename sub_holder::wrapper_type operator()(T const& t) const {
		return sub_holder (t);
	}

	operator sub_holder() const {
		return sub_holder();
	}
};

template<int const INDEX>
struct ArgIndexHolder
{
	enum { Index = INDEX };

	//prent the char[] to generate templates, because the ArgWrapper cannot copy each other
	ArgWrapper<INDEX, std::string> operator=(const char* v) const {
		return ArgWrapper<INDEX, std::string>(std::string(v));
	}
	ArgWrapper<INDEX, std::string> operator()(const char* v) const {
		return ArgWrapper<INDEX, std::string>(std::string(v));
	}

	template<typename T>
	ArgHolder<INDEX, T> as() const {
		return ArgHolder<INDEX, T>();
	}

	
	template<typename T>
	ArgWrapper<INDEX, T> operator=(T const &v) const {
		return ArgWrapper<INDEX, T>(v);
	}

	template<typename T>
	ArgWrapper<INDEX, T> operator()(T const &v) const {
		return ArgWrapper<INDEX, T>(v);
	}

	template<typename T>
	ArgWrapper<INDEX, T*> operator()(T *pt) const {
		return ArgWrapper<Index, T*>(pt);
	}

	template<typename T>
	operator ArgHolder<INDEX, T> () const {
		return ArgHolder<INDEX, T>();
	}

	template<class F>
	ArgWrapperBinder<INDEX, typename F::result_type, F> bind(F const& f) const {
		return ArgWrapperBinder<INDEX, typename F::result_type, F>(f);
	}
	

	template<int const WRAP_INDEX, typename T>
	ArgWrapper<WRAP_INDEX, T>  operator()(ArgWrapper<WRAP_INDEX, T>const & w) const {
		return ArgWrapper<WRAP_INDEX, T>(w);
	}

	template<int const WRAP_INDEX, typename T>
	ArgHolder<WRAP_INDEX, T> operator()(ArgHolder<WRAP_INDEX, T> const& ) const {
		return ArgHolder<WRAP_INDEX, T> ();
	}

	template<int const WRAP_INDEX, typename T>
	ArgHolder<WRAP_INDEX, T> operator=(ArgHolder<WRAP_INDEX, T> const& ) const {
		return ArgHolder<WRAP_INDEX, T> ();
	}

	template<int const WRAP_INDEX, typename T>
	ArgHolderWrapper<INDEX, WRAP_INDEX, T > operator()(ArgHolder<WRAP_INDEX, T> const & ) const {
		return ArgHolderWrapper<INDEX, WRAP_INDEX, T>();
	}

	///////////////////////////////
	//get index of value 
	template<int const WRAP_INDEX, typename T>
	int index(const ArgWrapper<WRAP_INDEX, T>&) const {
		return WRAP_INDEX;
	}
	template<typename T>
	int index(const T& ) const {
		return INDEX;
	}


	template<typename UserT>
	bool checkArg(UserT const& v) const {
		return false;
	}
	template<typename AWT>
	bool checkArg(ArgWrapper<INDEX, AWT> const& ) const {
		return true;
	}

};
template<typename T, int const IDX>
static inline ArgHolder<IDX, T> as(const ArgIndexHolder<IDX>&) {
	return ArgHolder<IDX, T>();
}


static const ArgIndexHolder<1> _1;
static const ArgIndexHolder<2> _2;
static const ArgIndexHolder<3> _3;
static const ArgIndexHolder<4> _4;
static const ArgIndexHolder<5> _5;
static const ArgIndexHolder<6> _6;
static const ArgIndexHolder<7> _7;
static const ArgIndexHolder<8> _8;
static const ArgIndexHolder<9> _9;

////////////////////////////////////////////////////////////

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

	template<typename T>
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



template<typename T1>
struct list1 : public list_t<list1<T1> >
{
	T1 t1;

	list1(T1 const &t1) :t1(t1) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }

	FUNCTION_NEST_CALL

	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, typename T>
	T operator[] (ArgHolder<INDEX, T> const &holder) const {
		T t;
		if(holder.checkAndGet(t1, t))
			return t;
		return T_NULL(T);
	}

	template<int const IDX, typename T>
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

template<typename T1, typename T2>
struct list2 : public list_t<list2<T1,T2> >
{
	T1 t1;
	T2 t2;
	list2(T1 const& t1, T2 const& t2) : t1(t1), t2(t2) { }

	T1 operator[] (ArgIndexHolder<1> const&) const { return t1; }
	T2 operator[] (ArgIndexHolder<2> const&) const { return t2; }

	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, typename T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t))
			return t;
		return T_NULL(T);
	}

	template<int const IDX, typename T>
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

template<typename T1, typename T2, typename T3>
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

	template<int const INDEX, typename T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, typename T>
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
	
	
	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<class F, class L>
	typename F::result_type operator()(F const & f, L const& l) const {
		return f(l[t1], l[t2], l[t3]);
	}

	template<class F>
	void for_each(F & f) {  f(t1); f(t2); f(t3); }

};

template<typename T1, typename T2, typename T3, typename T4>
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

	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, typename T>
	T operator[] (ArgHolder<INDEX, T>const & holder) const {
		T t;
		if(holder.checkAndGet(t1, t)
			|| holder.checkAndGet(t2, t)
			|| holder.checkAndGet(t3, t)
			|| holder.checkAndGet(t4, t))
			return t;
		return T_NULL(T);
	}
	template<int const IDX, typename T>
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

template<typename T1, typename T2, typename T3, typename T4, typename T5>
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

	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, typename T>
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
	template<int const IDX, typename T>
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

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
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

	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, typename T>
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
	template<int const IDX, typename T>
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

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
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

	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, typename T>
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
	template<int const IDX, typename T>
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


template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
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

	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, typename T>
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
	template<int const IDX, typename T>
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

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
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

	template<typename T>
	T operator[] (T const &t) const { return t; }

	template<int const INDEX, typename T>
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
	template<int const IDX, typename T>
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

template<typename T1>
list1<T1> make_list(T1 const &t1) {
	return list1<T1>(t1);
}

template<typename T1, typename T2>
list2<T1, T2> make_list(T1 const &t1, T2 const &t2) {
	return list2<T1,T2>(t1, t2);
}

template<typename T1, typename T2, typename T3>
list3<T1, T2, T3> make_list(T1 const &t1, T2 const &t2, T3 const &t3) {
	return list3<T1,T2,T3>(t1, t2, t3);
}

template<typename T1, typename T2, typename T3, typename T4>
list4<T1, T2, T3, T4> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4) {
	return list4<T1,T2,T3, T4>(t1, t2, t3, t4);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5>
list5<T1, T2, T3, T4, T5> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5) {
	return list5<T1,T2,T3, T4, T5>(t1, t2, t3, t4, t5);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
list6<T1, T2, T3, T4, T5, T6> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5, T6 const& t6) {
	return list6<T1,T2,T3, T4, T5, T6>(t1, t2, t3, t4, t5, t6);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
list7<T1, T2, T3, T4, T5, T6, T7> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7) {
	return list7<T1,T2,T3, T4, T5, T6, T7>(t1, t2, t3, t4, t5, t6, t7);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
list8<T1, T2, T3, T4, T5, T6, T7, T8> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8) {
	return list8<T1,T2,T3, T4, T5, T6, T7, T8>(t1, t2, t3, t4, t5, t6, t7, t8);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
list9<T1, T2, T3, T4, T5, T6, T7, T8, T9> make_list(T1 const &t1, T2 const &t2, T3 const &t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9) {
	return list9<T1,T2,T3, T4, T5, T6, T7, T8, T9>(t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

//// for call
template<typename T>
struct type {
	typedef T inner_type;
};

template<typename T, T const TDefualt>
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

////////////////////////////////////////
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

#define DYNAMIC_LIST(N, temp_def_arg_list, temp_arg_list, arg_list, arg_call_list) \
	template<temp_def_arg_list> \
	dynamic_list(list##N<temp_arg_list> const& l) { \
		init(N); \
		set(l); \
	} \
	template<temp_def_arg_list> \
	dynamic_list(arg_list) { \
		init(N); \
		set(arg_call_list); \
	}
DYNAMIC_LIST(1, \
		_W(class A1), \
		_W(A1), \
		_W(A1 const& a1), \
		_W(a1))
DYNAMIC_LIST(2, \
		_W(class A1, class A2), \
		_W(A1,A2), \
		_W(A1 const& a1, A2 const& a2), \
		_W(a1, a2))
DYNAMIC_LIST(3, \
		_W(class A1, class A2, class A3), \
		_W(A1,A2, A3), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3), \
		_W(a1, a2, a3))
DYNAMIC_LIST(4, \
		_W(class A1, class A2, class A3, class A4), \
		_W(A1,A2, A3, A4), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4), \
		_W(a1, a2, a3, a4))
DYNAMIC_LIST(5, \
		_W(class A1, class A2, class A3, class A4, class A5), \
		_W(A1,A2, A3, A4, A5), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), \
		_W(a1, a2, a3, a4, a5))
DYNAMIC_LIST(6, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6), \
		_W(A1,A2, A3, A4, A5, A6), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6), \
		_W(a1, a2, a3, a4, a5, a6))
DYNAMIC_LIST(7, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7), \
		_W(A1,A2, A3, A4, A5, A6, A7), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7), \
		_W(a1, a2, a3, a4, a5, a6, a7))
DYNAMIC_LIST(8, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8), \
		_W(A1,A2, A3, A4, A5, A6, A7, A8), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8), \
		_W(a1, a2, a3, a4, a5, a6, a7, a8))
DYNAMIC_LIST(9, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9), \
		_W(A1,A2, A3, A4, A5, A6, A7, A8, A9), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9), \
		_W(a1, a2, a3, a4, a5, a6, a7, a8, a9))

#undef DYNAMIC_LIST

#define DYNAMIC_SET_ITEM(I) \
	if((I-1) >= size_) return false; \
	if(items_[(I-1)]) delete items_[(I-1)]; \
	items_[(I-1)] = make_value(a##I);
#define DYNAMIC_SET_LIST(I) l[_##I]

#define DYNAMIC_SET(N, temp_def_arg_list, temp_arg_list, arg_list, arg_call_list) \
   template<temp_def_arg_list> \
	bool set(arg_list) { \
		if(!items_) return false; \
		SETS(DYNAMIC_SET_ITEM, _W()) \
		return true; \
	} \
	template<temp_def_arg_list> \
	bool set(list##N<temp_arg_list> const& l) { \
		if(!items_) return false; \
		return set(SETS(DYNAMIC_SET_LIST, _W(,))); \
	}

#define SETS(X, dot) X(1) 
DYNAMIC_SET(1, \
		_W(class A1), \
		_W(A1), \
		_W(A1 const& a1), \
		_W(a1))
#undef SETS
#define SETS(X, dot) X(1) dot X(2)
DYNAMIC_SET(2, \
		_W(class A1, class A2), \
		_W(A1,A2), \
		_W(A1 const& a1, A2 const& a2), \
		_W(a1, a2))
#undef SETS
#define SETS(X, dot) X(1) dot X(2) dot X(3)
DYNAMIC_SET(3, \
		_W(class A1, class A2, class A3), \
		_W(A1,A2, A3), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3), \
		_W(a1, a2, a3))
#undef SETS
#define SETS(X, dot) X(1) dot X(2) dot X(3) dot X(4)
DYNAMIC_SET(4, \
		_W(class A1, class A2, class A3, class A4), \
		_W(A1,A2, A3, A4), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4), \
		_W(a1, a2, a3, a4))
#undef SETS
#define SETS(X, dot) X(1) dot X(2) dot X(3) dot X(4) dot X(5)
DYNAMIC_SET(5, \
		_W(class A1, class A2, class A3, class A4, class A5), \
		_W(A1,A2, A3, A4, A5), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), \
		_W(a1, a2, a3, a4, a5))
#undef SETS
#define SETS(X, dot) X(1) dot X(2) dot X(3) dot X(4) dot X(5) dot X(6)
DYNAMIC_SET(6, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6), \
		_W(A1,A2, A3, A4, A5, A6), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6), \
		_W(a1, a2, a3, a4, a5, a6))
#undef SETS
#define SETS(X, dot) X(1) dot X(2) dot X(3) dot X(4) dot X(5) dot X(6) dot X(7)
DYNAMIC_SET(7, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7), \
		_W(A1,A2, A3, A4, A5, A6, A7), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7), \
		_W(a1, a2, a3, a4, a5, a6, a7))
#undef SETS
#define SETS(X, dot) X(1) dot X(2) dot X(3) dot X(4) dot X(5) dot X(6) dot X(7) dot X(8)
DYNAMIC_SET(8, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8), \
		_W(A1,A2, A3, A4, A5, A6, A7, A8), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8), \
		_W(a1, a2, a3, a4, a5, a6, a7, a8))
#undef SETS
#define SETS(X, dot) X(1) dot X(2) dot X(3) dot X(4) dot X(5) dot X(6) dot X(7) dot X(8) dot X(9)
DYNAMIC_SET(9, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9), \
		_W(A1,A2, A3, A4, A5, A6, A7, A8, A9), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9), \
		_W(a1, a2, a3, a4, a5, a6, a7, a8, a9))
#undef SETS


#undef DYNAMIC_SET
	
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

#define DEFINE_OPERATOR_CALL(N) \
	template<TEMPL_DEFINE> \
	result_type operator()(CALL_ARG_DEFIN) const { \
		list##N<TEMPL_ARG> l(CALL_ARG); \
		return l_(f_, l); \
	} \
	template<class R, TEMPL_DEFINE> \
	R operator()(type<R> const& r, CALL_ARG_DEFIN) const { \
		list##N<TEMPL_ARG> l(CALL_ARG); \
		return call(r, type<result_type>(), l_, f_, l); \
	} \
	template<class R, R const RDef, TEMPL_DEFINE> \
	R operator()(type_default<R,RDef> const& rd, CALL_ARG_DEFIN) const { \
		list##N<TEMPL_ARG> l(CALL_ARG); \
		return call(rd, type<result_type>(), l_, f_, l); \
	} \
	/* list call */ \
	template<TEMPL_DEFINE> \
	result_type operator()(list##N<TEMPL_ARG> const& l) const { \
		return l_(f_, l.driver()); \
	} \
	template<class R, TEMPL_DEFINE> \
	R operator()(type<R> const& r, list##N<TEMPL_ARG> const& l) const { \
		return call(r, type<result_type>(), l_, f_, l.driver()); \
	} \
	template<class R, R const RDef, TEMPL_DEFINE> \
	R operator()(type_default<R, RDef> const& rd, list##N<TEMPL_ARG> const& l) const { \
		return call(rd, type<result_type>(), l_, f_, l.driver()); \
	}
	

#define TEMPL_DEFINE class T1
#define TEMPL_ARG T1
#define CALL_ARG_DEFIN T1 t1
#define CALL_ARG t1
DEFINE_OPERATOR_CALL(1)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2
#define TEMPL_ARG T1,T2
#define CALL_ARG_DEFIN T1 t1,T2 t2
#define CALL_ARG t1,t2
DEFINE_OPERATOR_CALL(2)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3
#define TEMPL_ARG T1,T2,T3
#define CALL_ARG_DEFIN T1 t1,T2 t2,T3 t3
#define CALL_ARG t1,t2,t3
DEFINE_OPERATOR_CALL(3)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4
#define TEMPL_ARG T1,T2,T3,T4
#define CALL_ARG_DEFIN T1 t1,T2 t2,T3 t3, T4 t4
#define CALL_ARG t1,t2,t3,t4
DEFINE_OPERATOR_CALL(4)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5
#define TEMPL_ARG T1,T2,T3,T4,T5
#define CALL_ARG_DEFIN T1 t1,T2 t2,T3 t3, T4 t4,T5 t5
#define CALL_ARG t1,t2,t3,t4,t5
DEFINE_OPERATOR_CALL(5)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6
#define TEMPL_ARG T1,T2,T3,T4,T5,T6
#define CALL_ARG_DEFIN T1 t1,T2 t2,T3 t3, T4 t4,T5 t5,T6 t6
#define CALL_ARG t1,t2,t3,t4,t5,t6
DEFINE_OPERATOR_CALL(6)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7
#define CALL_ARG_DEFIN T1 t1,T2 t2,T3 t3, T4 t4,T5 t5,T6 t6,T7 t7
#define CALL_ARG t1,t2,t3,t4,t5,t6,t7
DEFINE_OPERATOR_CALL(7)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7, class T8
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7,T8
#define CALL_ARG_DEFIN T1 t1,T2 t2,T3 t3, T4 t4,T5 t5,T6 t6,T7 t7,T8 t8
#define CALL_ARG t1,t2,t3,t4,t5,t6,t7,t8
DEFINE_OPERATOR_CALL(8)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7, class T8,class T9
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7,T8,T9
#define CALL_ARG_DEFIN T1 t1,T2 t2,T3 t3, T4 t4,T5 t5,T6 t6,T7 t7,T8 t8, T9 t9
#define CALL_ARG t1,t2,t3,t4,t5,t6,t7,t8,t9
DEFINE_OPERATOR_CALL(9)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG


#undef DEFINE_OPERATOR_CALL
};


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

#define DEF_FUNC_PTR_CALL(N, temp_def_arg_list, temp_arg_list, arg_list, arg_call_list) \
	template<temp_def_arg_list> \
	result_type operator()(arg_list) const { \
		return f_(arg_call_list) ; \
	}


#define FUNCTION_PTR_DEFINE(N) \
	template<class R, TEMPL_DEFINE> \
	struct function_ptr##N{ \
		typedef R result_type; \
		typedef R (*Func)(TEMPL_ARG); \
		Func f_; \
		function_ptr##N(Func const& f) : f_(f) { } \
		function_ptr##N(const function_ptr##N& f):f_(f.f_) { } \
		template<CALL_TEMPL_ARG_DEFIN> \
		result_type operator()(CALL_ARG_DEFIN) const { \
			return f_(CALL_ARG); \
		} \
	}; \
	template<class R, TEMPL_DEFINE > \
	function_ptr##N<R, TEMPL_ARG> func_ptr(R(*f)(TEMPL_ARG)) { \
		return function_ptr##N<R, TEMPL_ARG>(f);\
	} 

#define TEMPL_DEFINE class T1
#define TEMPL_ARG T1
#define CALL_TEMPL_ARG_DEFIN class A1
#define CALL_ARG_DEFIN A1 a1
#define CALL_ARG arg_cast<T1>(a1)
FUNCTION_PTR_DEFINE(1)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2
#define TEMPL_ARG T1,T2
#define CALL_TEMPL_ARG_DEFIN class A1,class A2
#define CALL_ARG_DEFIN A1 a1,A2 a2
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2)
FUNCTION_PTR_DEFINE(2)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3
#define TEMPL_ARG T1,T2,T3
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3)
FUNCTION_PTR_DEFINE(3)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4
#define TEMPL_ARG T1,T2,T3,T4
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4)
FUNCTION_PTR_DEFINE(4)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5
#define TEMPL_ARG T1,T2,T3,T4,T5
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5)
FUNCTION_PTR_DEFINE(5)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6
#define TEMPL_ARG T1,T2,T3,T4,T5,T6
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5,class A6
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5,A6 a6
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5),arg_cast<T6>(a6)
FUNCTION_PTR_DEFINE(6)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5,class A6, class A7
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5,A6 a6,A7 a7
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5),arg_cast<T6>(a6),arg_cast<T7>(a7)
FUNCTION_PTR_DEFINE(7)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7,T8
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5,class A6, class A7,class A8
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5,A6 a6,A7 a7,A8 a8
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5),arg_cast<T6>(a6),arg_cast<T7>(a7),arg_cast<T8>(a8)
FUNCTION_PTR_DEFINE(8)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG


#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7,T8,T9
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5,class A6, class A7,class A8,class A9
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5,A6 a6,A7 a7,A8 a8,A9 a9
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5),arg_cast<T6>(a6),arg_cast<T7>(a7),arg_cast<T8>(a8), arg_cast<T9>(a9)
FUNCTION_PTR_DEFINE(9)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#undef FUNCTION_PTR_DEFINE
#undef DEF_FUNC_PTR_CALL

//member function ptr
template<typename R, typename X>
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
template<typename R, typename X>
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

#define METHOD_PTR_DEFINE(N) \
	template<class R, class X, TEMPL_DEFINE> \
	struct method_function##N { \
		typedef R (X::*method)(TEMPL_ARG); \
		typedef R result_type; \
		method method_; \
		method_function##N(method const& m) : method_(m) { } \
		method_function##N(const method_function##N& m) : method_(m.method_) { } \
		template<CALL_TEMPL_ARG_DEFIN> \
		R operator()(X *x, CALL_ARG_DEFIN) const{ \
			return (x->*method_)(CALL_ARG); \
		} \
		template<CALL_TEMPL_ARG_DEFIN> \
		R operator()(X& x, CALL_ARG_DEFIN) const{ \
			return (x.*method_)(CALL_ARG); \
		} \
	}; \
	template<class R, class X, TEMPL_DEFINE> \
	struct method_const_function##N { \
		typedef R (X::*method)(TEMPL_ARG) const; \
		typedef R result_type; \
		method method_; \
		method_const_function##N(method const& m) : method_(m) { } \
		method_const_function##N(const method_const_function##N& m) : method_(m.method_) { } \
		template<CALL_TEMPL_ARG_DEFIN> \
		R operator()(X const*x, CALL_ARG_DEFIN) const{ \
			return (x->*method_)(CALL_ARG); \
		} \
		template<CALL_TEMPL_ARG_DEFIN> \
		R operator()(X const& x, CALL_ARG_DEFIN) const{ \
			return (x.*method_)(CALL_ARG); \
		} \
	}; \
	template<class R, class X, TEMPL_DEFINE> \
	method_function##N<R,X,TEMPL_ARG> method_ptr(R(X::*f)(TEMPL_ARG)) { \
		return method_function##N<R,X,TEMPL_ARG>(f); \
	} \
	template<class R, class X, TEMPL_DEFINE> \
	method_const_function##N<R,X,TEMPL_ARG> method_ptr(R(X::*f)(TEMPL_ARG) const) { \
		return method_const_function##N<R,X,TEMPL_ARG>(f); \
	}

#define TEMPL_DEFINE class T1
#define TEMPL_ARG T1
#define CALL_TEMPL_ARG_DEFIN class A1
#define CALL_ARG_DEFIN A1 a1
#define CALL_ARG arg_cast<T1>(a1)
METHOD_PTR_DEFINE(1)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2
#define TEMPL_ARG T1,T2
#define CALL_TEMPL_ARG_DEFIN class A1,class A2
#define CALL_ARG_DEFIN A1 a1,A2 a2
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2)
METHOD_PTR_DEFINE(2)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3
#define TEMPL_ARG T1,T2,T3
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3)
METHOD_PTR_DEFINE(3)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4
#define TEMPL_ARG T1,T2,T3,T4
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4)
METHOD_PTR_DEFINE(4)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5
#define TEMPL_ARG T1,T2,T3,T4,T5
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5)
METHOD_PTR_DEFINE(5)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6
#define TEMPL_ARG T1,T2,T3,T4,T5,T6
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5,class A6
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5,A6 a6
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5),arg_cast<T6>(a6)
METHOD_PTR_DEFINE(6)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5,class A6, class A7
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5,A6 a6,A7 a7
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5),arg_cast<T6>(a6),arg_cast<T7>(a7)
METHOD_PTR_DEFINE(7)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7,T8
#define CALL_TEMPL_ARG_DEFIN class A1,class A2,class A3,class A4,class A5,class A6, class A7,class A8
#define CALL_ARG_DEFIN A1 a1,A2 a2,A3 a3, A4 a4, A5 a5,A6 a6,A7 a7,A8 a8
#define CALL_ARG arg_cast<T1>(a1),arg_cast<T2>(a2),arg_cast<T3>(a3),arg_cast<T4>(a4), arg_cast<T5>(a5),arg_cast<T6>(a6),arg_cast<T7>(a7),arg_cast<T8>(a8)
METHOD_PTR_DEFINE(8)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_TEMPL_ARG_DEFIN
#undef CALL_ARG_DEFIN
#undef CALL_ARG



#undef METHOD_PTR_DEFINE


template<class F>
function_t<F, list0> make_function(F const &f){
	return function_t<F, list0>(f, list0());
}

#define MAKE_FUNCTION(N) \
	template<class F, TEMPL_DEFINE> \
	function_t<F, list##N<TEMPL_ARG> > make_function(F const& f, CALL_ARG_DEFIN) { \
		return function_t<F, list##N<TEMPL_ARG> >(f, list##N<TEMPL_ARG>(CALL_ARG)); \
	}

#define TEMPL_DEFINE class T1
#define TEMPL_ARG T1
#define CALL_ARG_DEFIN T1 t1
#define CALL_ARG (t1)
MAKE_FUNCTION(1)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2
#define TEMPL_ARG T1,T2
#define CALL_ARG_DEFIN T1 t1,T2 t2
#define CALL_ARG (t1),(t2)
MAKE_FUNCTION(2)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3
#define TEMPL_ARG T1,T2,T3
#define CALL_ARG_DEFIN T1 t1,T2 t2, T3 t3
#define CALL_ARG (t1),(t2),(t3)
MAKE_FUNCTION(3)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4
#define TEMPL_ARG T1,T2,T3,T4
#define CALL_ARG_DEFIN T1 t1,T2 t2, T3 t3, T4 t4
#define CALL_ARG (t1),(t2),(t3),(t4)
MAKE_FUNCTION(4)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5
#define TEMPL_ARG T1,T2,T3,T4,T5
#define CALL_ARG_DEFIN T1 t1,T2 t2, T3 t3, T4 t4, T5 t5
#define CALL_ARG (t1),(t2),(t3),(t4), (t5)
MAKE_FUNCTION(5)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6
#define TEMPL_ARG T1,T2,T3,T4,T5,T6
#define CALL_ARG_DEFIN T1 t1,T2 t2, T3 t3, T4 t4, T5 t5, T6 t6
#define CALL_ARG (t1),(t2),(t3),(t4), (t5), (t6)
MAKE_FUNCTION(6)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7
#define CALL_ARG_DEFIN T1 t1,T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7
#define CALL_ARG (t1),(t2),(t3),(t4), (t5), (t6), (t7)
MAKE_FUNCTION(7)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG

#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7,T8
#define CALL_ARG_DEFIN T1 t1,T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8
#define CALL_ARG (t1),(t2),(t3),(t4), (t5), (t6), (t7), (t8)
MAKE_FUNCTION(8)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG


#define TEMPL_DEFINE class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9
#define TEMPL_ARG T1,T2,T3,T4,T5,T6,T7,T8,T9
#define CALL_ARG_DEFIN T1 t1,T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9
#define CALL_ARG (t1),(t2),(t3),(t4), (t5), (t6), (t7), (t8), (t9)
MAKE_FUNCTION(9)
#undef TEMPL_DEFINE
#undef TEMPL_ARG
#undef CALL_ARG_DEFIN
#undef CALL_ARG


#undef MAKE_FUNCTION

/////////////////////////////////////////////
//for char[]
static inline const char* _sq(char const str[])
{
	return (const char*)str;
}

/////////////////////////////////////////////////////////////////////
//transform

//accessor
template<typename T>
static inline int member_offset(T  t)  
{
	    return reinterpret_cast<int>(*(void**)&t);
}

//fetch_member
template<class TMember>
struct FetchMember
{
	typedef TMember result_type;
	int offset_;
	FetchMember(int offset) : offset_(offset) { }
	FetchMember(const FetchMember& f) : offset_(f.offset_) { }

	template<class Klass>
	TMember operator() (Klass const& k) const {
		return *(TMember*)(((unsigned char*)(&k)) + offset_);
	}

	template<class Klass>
	TMember operator()(Klass const* pk) const {
		if(!pk) return TMember(0);
		return *(TMember*)(((unsigned char*)pk) + offset_);
	}
};

template<class TMember, class TOffset, class KlassHolder>
function_t<FetchMember<TMember>, list1<KlassHolder> > fetch_member(TOffset toff, KlassHolder holder)
{
	return make_function(FetchMember<TMember>(member_offset(toff)), holder);
}

template<class TMember, class KlassHolder>
function_t<FetchMember<TMember>, list1<KlassHolder> > fetch_member(int offset, KlassHolder holder)
{
	return make_function(FetchMember<TMember>(offset), holder);
}


//the operator for dynamic
template<typename R = void>
struct dynamic_func_wrapper {
	struct func_wrapper {
		virtual R operator()(const dynamic_list& list) = 0;
		virtual bool checkArg(const dynamic_list& list) = 0;
		virtual func_wrapper* clone() const = 0;
	};

	func_wrapper *func_;

	template<class F, class TR>
	struct func_wrapper_impl : public func_wrapper {
		typedef typename F::result_type result_type;
		F f_;
		func_wrapper_impl(F const& f) : f_(f) { }

		TR operator()(const dynamic_list& list) {
			return call(type<TR>(), type<result_type>(), f_, list);
		}

		bool checkArg(const dynamic_list& list) {
			return f_.checkArg(list);
		}

		func_wrapper* clone() const {
			return new func_wrapper_impl(f_);
		}

	};

	dynamic_func_wrapper() : func_(NULL) { }

	template<class F>
	dynamic_func_wrapper(F const& f) 
	:func_(new func_wrapper_impl<F, R>(f)){ }

	dynamic_func_wrapper(const dynamic_func_wrapper& d) 
	:func_(d.cloneFunc()) { }

	func_wrapper* cloneFunc() const {
		return func_ ? func_->clone() : NULL;
	}

	template<class F>
	void setFunc(F const& f){
		if(func_)delete func_;
		func_ = new func_wrapper_impl<F, R>(f);
	}

	~dynamic_func_wrapper() {
		if(func_)
			delete func_;
	}

	bool checkArg(const dynamic_list &l) const {
		return func_ && func_->checkArg(l);
	}

	//call
	R operator()() const {
		if(!func_) return T_NULL(R);
		dynamic_list l(0);
		return (*func_)(l);
	}

	R operator()(const dynamic_list& l) const {
		if(!func_) return T_NULL(R);
		return (*func_)(l);
	}

#define DYNAMIC_FUNC_CALL(N, temp_def_arg_list, temp_arg_list, arg_list, arg_call_list) \
	template<temp_def_arg_list> \
	R operator()(arg_list) const { \
		if(!func_) return T_NULL(R); \
		dynamic_list dl(arg_call_list); \
		return (*func_)(dl); \
	} \
	template<temp_def_arg_list> \
	R operator()(list##N<temp_arg_list> const& l) const { \
		if(!func_) return T_NULL(R) ; \
		dynamic_list dl(l); \
		return (*func_)(dl); \
	}

DYNAMIC_FUNC_CALL(1, \
		_W(class A1), \
		_W(A1), \
		_W(A1 const& a1), \
		_W(a1))
DYNAMIC_FUNC_CALL(2, \
		_W(class A1, class A2), \
		_W(A1,A2), \
		_W(A1 const& a1, A2 const& a2), \
		_W(a1, a2))
DYNAMIC_FUNC_CALL(3, \
		_W(class A1, class A2, class A3), \
		_W(A1,A2, A3), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3), \
		_W(a1, a2, a3))
DYNAMIC_FUNC_CALL(4, \
		_W(class A1, class A2, class A3, class A4), \
		_W(A1,A2, A3, A4), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4), \
		_W(a1, a2, a3, a4))
DYNAMIC_FUNC_CALL(5, \
		_W(class A1, class A2, class A3, class A4, class A5), \
		_W(A1,A2, A3, A4, A5), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), \
		_W(a1, a2, a3, a4, a5))
DYNAMIC_FUNC_CALL(6, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6), \
		_W(A1,A2, A3, A4, A5, A6), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6), \
		_W(a1, a2, a3, a4, a5, a6))
DYNAMIC_FUNC_CALL(7, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7), \
		_W(A1,A2, A3, A4, A5, A6, A7), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7), \
		_W(a1, a2, a3, a4, a5, a6, a7))
DYNAMIC_FUNC_CALL(8, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8), \
		_W(A1,A2, A3, A4, A5, A6, A7, A8), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8), \
		_W(a1, a2, a3, a4, a5, a6, a7, a8))
DYNAMIC_FUNC_CALL(9, \
		_W(class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9), \
		_W(A1,A2, A3, A4, A5, A6, A7, A8, A9), \
		_W(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9), \
		_W(a1, a2, a3, a4, a5, a6, a7, a8, a9))

#undef DYNAMIC_FUNC_CALL
};

#undef _W
}

#endif

