#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__

#include <stdint.h>

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

class xiArrayRefCounter : public xiRefCounter {
protected:
	virtual void	Delete() const;
};

template<class T> class xiPtr {
public:
	xiPtr( T* ptr = nullptr ) : pointer( ptr ) {
		if ( ptr != nullptr ) {
			ptr->Grab();
		}
	}
	
	xiPtr( const xiPtr &ptr ) : pointer( ptr.pointer ) {
		if( pointer != nullptr ) {
			pointer->Grab();
		}
	}

	~xiPtr() {
		if( pointer != nullptr ) {
			pointer->Drop();
		}
	}

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

	xiPtr &operator=( const xiPtr &ptr ) {
		return ( *this ) = ptr.pointer;
	}

	T* operator->() const {
		return pointer;
	}

	T &operator*() const {
		return *pointer;
	}

	operator T*() const {
		return pointer;
	}

	operator bool() const {
		return pointer != nullptr;
	}

	bool operator==(const xiPtr &ptr) {
		return pointer == ptr.pointer;
	}

	bool operator==(const T *ptr) {
		return pointer == ptr;
	}

	T& operator[] ( int x ) {
		return pointer[x];
	}
private:
	T*	pointer;
};

#endif