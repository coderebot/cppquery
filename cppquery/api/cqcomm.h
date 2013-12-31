#ifndef CQ_COMMON_H
#define CQ_COMMON_H
#include <stdio.h>


namespace cppquery {

template<class T>
class RefCnt
{
	mutable int ref_;
public:
	RefCnt() : ref_(0) { }
	const T * ref() const{ ++ref_; return static_cast<T*>(this); }
	T* ref() { ++ref_; return static_cast<T*>(this); }

	void release() const{ if(--ref_ <= 0) delete (T*)(this); }

	int refcount() const { return ref_; }
};

template <class T>
class RefPtr 
{
	T *ptr_;
public:
    RefPtr():ptr_(NULL) {}
	RefPtr(T *ptr) : ptr_(ptr? ptr->ref() : NULL) { }
	RefPtr(RefPtr const&p) : ptr_(p.ref()) { }

	T *ref() const{ return static_cast<T*>(ptr_ ? ptr_->ref() : NULL); }
	T *ptr() { return ptr_; }
	T const* ptr() const { return ptr_; }
	operator T *() { return ptr_; }
	operator T const*() const{ return ptr_; }

	T* operator->() { return ptr_; }
	T const* operator->() const { return ptr_; }

	T* drop() {
		if(ptr_)
			ptr_->release();
		T *ptr = ptr_;
		ptr_ = NULL;
		return ptr;
	}

	void set(T * p) {
		drop();
		ptr_ = static_cast<T*>(p ? p->ref() : NULL);
	}
	
	void operator = (T * ptr) {
		set(ptr);
	}

	operator bool() const{ return ptr_ != NULL; }
	bool operator !()const{ return ptr_ == NULL;}
};


template<typename T>
class LocalPtr
{
	T *ptr_;
public:
	LocalPtr() : ptr_(NULL) { }
	LocalPtr(T *ptr) : ptr_(ptr) { }
	~LocalPtr() {
		if(ptr_) delete ptr_;
	}

	void attach(T *ptr) { if(ptr_) delete ptr_; ptr_ = ptr; }

	operator T*() { return ptr(); }
	operator const T*() const { return ptr(); }
	T *ptr() { return ptr_; }
	const T* ptr() const { return ptr_; }

	T *operator->() { return ptr(); }
	const T* operator->() const { return ptr(); }
};


}
#endif

