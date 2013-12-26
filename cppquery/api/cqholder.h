#ifndef CQ_HOLDER_H
#define CQ_HOLDER_H

namespace cppquery{

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
		return static_cast<T1*>(t);
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
template<typename T>
static inline T* arg_cast(T *t){ return t;}
template<typename T>
static inline const T* arg_cast(const T* t) { return t; }

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

	template<class A1>
	ArgWrapper<INDEX, T> operator()(A1 const& a1) const {
		return ArgWrapper<INDEX, T>(f_(a1));
	}
	template<class A1, class A2>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2) const {
		return ArgWrapper<INDEX, T>(f_(a1, a2));
	}
	template<class A1, class A2, class A3>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2, A3 const& a3) const {
		return ArgWrapper<INDEX, T>(f_(a1, a2, a3));
	}
	template<class A1, class A2, class A3, class A4>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4) const {
		return ArgWrapper<INDEX, T>(f_(a1, a2, a3, a4));
	}
	template<class A1, class A2, class A3, class A4, class A5>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5) const {
		return ArgWrapper<INDEX, T>(f_(a1, a2, a3, a4, a5));
	}
	template<class A1, class A2, class A3, class A4, class A5, class A6>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6) const {
		return ArgWrapper<INDEX, T>(f_(a1, a2, a3, a4, a5, a6));
	}
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7) const {
		return ArgWrapper<INDEX, T>(f_(a1, a2, a3, a4, a5, a6, a7));
	}
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8) const {
		return ArgWrapper<INDEX, T>(f_(a1, a2, a3, a4, a5, a6, a7, a8));
	}
	template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	ArgWrapper<INDEX, T> operator()(A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9) const {
		return ArgWrapper<INDEX, T>(f_(a1, a2, a3, a4, a5, a6, a7, a8, a9));
	}

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

}

#endif
