#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__

#include <stdint.h>

/*
================================================================================

	Reference counter

================================================================================
*/
class xiRefCounter {
public:
			xiRefCounter();
	virtual	~xiRefCounter();
	void	Grab() const;
	void	Drop() const;
protected:
	virtual void	Delete() const;
private:
	mutable int64_t	referenceCount;
};

/*
================================================================================

	Reference counter for arrays

================================================================================
*/
class xiArrayRefCounter : public xiRefCounter {
protected:
	virtual void	Delete() const;
};

/*
================================================================================

	Smart pointer for automatic reference counting

================================================================================
*/
template<class T> class xiPtr {
public:
	// Smart pointer construct with pointer
	xiPtr( T* ptr = nullptr ) : pointer( ptr ) {
		if ( ptr != nullptr ) {
			ptr->Grab();
		}
	}
	
	// Smart pointer copy constructor, will call ::Grab()
	xiPtr( const xiPtr &ptr ) : pointer( ptr.pointer ) {
		if( pointer != nullptr ) {
			pointer->Grab();
		}
	}

	// Smart pointer destructor, calls ::Drop() on xiPtr
	~xiPtr() {
		if( pointer != nullptr ) {
			pointer->Drop();
		}
	}
	
	// Smart pointer assignment, will call ::Grab()
	xiPtr &operator=( T* ptr ) {
		if ( ptr != nullptr ) {
			ptr->Grab();
		}

		if ( pointer != nullptr ) {
			pointer->Drop();
		}

		pointer = ptr;
		return ( *this );
	}
	
	// Smart pointer assignment, will call pointer assignment
	xiPtr &operator=( const xiPtr &ptr ) {
		return ( *this ) = ptr.pointer;
	}
	
	// Smart pointer access
	T* operator->() const {
		return pointer;
	}
	
	// Smart pointer dereference set
	T &operator*() const {
		return *pointer;
	}
	
	// Smart pointer dereference
	operator T*() const {
		return pointer;
	}
	
	// Smart pointer nullptr check
	operator bool() const {
		return pointer != nullptr;
	}
	
	// Smart pointer compare with other
	bool operator==(const xiPtr &ptr) {
		return pointer == ptr.pointer;
	}
	
	// Smart pointer compare with other pointer
	bool operator==(const T *ptr) {
		return pointer == ptr;
	}
	
	// Smart pointer array accessor
	T& operator[] ( int x ) {
		return pointer[x];
	}
private:
	T*	pointer;
};

#endif